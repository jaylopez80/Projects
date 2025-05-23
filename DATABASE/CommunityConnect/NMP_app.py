"""
app.py

A Streamlit front-end for Community Connect that demonstrates:

1. Display records (read)
2. Filter/search with parameters
3. Create new records (signup, listings, messages, reviews)
4. Soft-delete (expire) listings
5. Update records (profile, listings, messages)
6. Transactions (checkout with commit/rollback)
7. Reports exportable to CSV (aggregations, joins, subqueries)
8. Aggregation example: Avg price per category
9. Subquery example: Users with >1 sale
10. Joins across 3 tables
11. Enforced PK/FK via SQLAlchemy
12. View `active_listings`
13. 6 entities: Users, Categories, Listings, Transactions, Reviews, Messages
"""

import streamlit as st
from sqlalchemy import create_engine, select, func, and_, desc
from sqlalchemy.orm import sessionmaker
import pandas as pd
from NMP_setup import User, Category, Listing, Transaction, Review, Message

# 1. Connect to DB
DATABASE_URL = "mysql+pymysql://root:CPSC408!@localhost:3306/community_connect"
engine = create_engine(DATABASE_URL, echo=False, future=True)
Session = sessionmaker(bind=engine)
session = Session()

# --- Helper functions ---
def to_df(query):
    """Convert SQLAlchemy Query to pandas DataFrame."""
    df = pd.read_sql(query, engine)
    return df

# --- Streamlit UI ---

st.title(" Welcome To Community Connect")

menu = ["Home","Sign Up","Login","Browse","My Listings","Checkout","Messages","Reviews","Reports"]
choice = st.sidebar.selectbox("Menu", menu)

if choice=="Home":
    st.header("Active Listings")
    df = to_df("SELECT * FROM active_listings")
    st.dataframe(df)

# 2. Sign-Up
elif choice=="Sign Up":
    st.subheader("Create a New Account")
    with st.form("signup"):
        user = st.text_input("Username")
        pwd  = st.text_input("Password", type="password")
        name = st.text_input("Full name")
        email= st.text_input("Email")
        nbr  = st.text_input("Neighborhood")
        submitted = st.form_submit_button("Sign Up")
        if submitted:
            new = User(Username=user, PasswordHash=pwd, Name=name, Email=email, Neighborhood=nbr)
            session.add(new)
            session.commit()
            st.success("Account created!")

# 3. Login & store in session_state
elif choice=="Login":
    st.subheader("Login")
    uid = st.text_input("Username")
    pwd = st.text_input("Password", type="password")
    if st.button("Login"):
        user = session.query(User).filter_by(Username=uid, PasswordHash=pwd).first()
        if user:
            st.session_state.user_id = user.UserID
            st.success(f"Welcome {user.Name}")
        else:
            st.error("Invalid credentials")

# 4. Browse / Filter
elif choice=="Browse":
    st.subheader("Search Listings")
    cat = st.selectbox("Category", [c.CategoryName for c in session.query(Category).all()])
    keyword = st.text_input("Keyword")
    q = select(Listing, User.Name.label("Seller"), Category.CategoryName).\
        join(User).join(Category).\
        where(Listing.Status=="Active",
              Category.CategoryName==cat,
              Listing.Title.ilike(f"%{keyword}%"))
    df = to_df(q)
    st.dataframe(df)

# 5. My Listings (CRUD + Soft-delete + Update)
elif choice=="My Listings":
    st.subheader("Manage My Listings")
    if "user_id" not in st.session_state:
        st.warning("Log in first!")
    else:
        user_id = st.session_state.user_id

        # --- Add New Listing Form ---
        st.markdown("### Add New Listing")
        with st.form("add_listing"):
            title = st.text_input("Title")
            desc = st.text_area("Description")
            price = st.number_input("Price", min_value=0.0, step=1.0)
            cat_names = [c.CategoryName for c in session.query(Category).all()]
            cat_name = st.selectbox("Category", cat_names)
            img_url = st.text_input("Image URL (optional)")
            submitted = st.form_submit_button("Add Listing")
            if submitted:
                cat = session.query(Category).filter_by(CategoryName=cat_name).first()
                new_listing = Listing(
                    UserID=user_id,
                    CategoryID=cat.CategoryID,
                    Title=title,
                    Description=desc,
                    Price=price,
                    ImageURL=img_url,
                    Status="Active"
                )
                session.add(new_listing)
                session.commit()
                st.success("Listing added!")

        # --- Show Existing Listings ---
        listings = session.query(Listing).filter_by(UserID=user_id).all()
        if not listings:
            st.info("You have no listings yet.")
        for l in listings:
            st.write(f"**{l.Title}** — {l.Status}")
            if l.ImageURL:
                st.image(l.ImageURL, width=200, caption=l.Title)
            cols = st.columns(3)
            if cols[0].button("Expire", key=f"e{l.ListingID}"):
                l.Status = "Expired"
                session.commit()
                st.success("Listing expired")
            if cols[1].button("Edit", key=f"u{l.ListingID}"):
                new_price = st.number_input("New price", value=float(l.Price), key=f"np{l.ListingID}")
                l.Price = new_price
                session.commit()
                st.success("Price updated")
            if cols[2].button("Delete", key=f"d{l.ListingID}"):
                session.delete(l)
                session.commit()
                st.success("Listing deleted")

# 6. Checkout (Transaction example with rollback)
elif choice=="Checkout":
    st.subheader("Buy an Item")
    if "user_id" not in st.session_state:
        st.warning("Log in first!")
    else:
        # list active listings
        df = to_df("SELECT ListingID, Title, Price FROM active_listings")
        st.dataframe(df)
        lid = st.number_input("Enter ListingID to buy", min_value=1)
        if st.button("Buy"):
            try:
                # Check if already sold
                existing_txn = session.query(Transaction).filter_by(ListingID=lid).first()
                if existing_txn:
                    st.error("This item has already been purchased.")
                else:
                    session.begin()  # start transaction
                    listing = session.get(Listing, lid)
                    txn = Transaction(ListingID=lid,
                                      BuyerID=st.session_state.user_id,
                                      TotalAmount=listing.Price,
                                      PaymentStatus="Completed")
                    listing.Status = "Sold"
                    session.add(txn)
                    session.commit()
                    st.success("Purchase complete!")
            except Exception as e:
                session.rollback()
                st.error(f"Transaction failed: {e}")

# 7. Messages
elif choice=="Messages":
    st.subheader("Inbox")
    if "user_id" not in st.session_state:
        st.warning("Log in first!")
    else:
        df_in = to_df(select(Message, User.Name.label("From"))
                      .join(User, Message.SenderID==User.UserID)
                      .where(Message.ReceiverID==st.session_state.user_id))
        st.dataframe(df_in)
        st.subheader("Send a Message")
        to_user = st.number_input("To (UserID)", min_value=1)
        about_listing = st.text_input("About ListingID (optional)")
        subj = st.text_input("Subject")
        body = st.text_area("Content")
        if st.button("Send"):
            # Add the listing info to the subject if provided
            full_subject = f"[ListingID: {about_listing}] {subj}" if about_listing else subj
            msg = Message(SenderID=st.session_state.user_id,
                          ReceiverID=to_user,
                          Subject=full_subject,
                          Content=body)
            session.add(msg)
            session.commit()
            st.success("Sent!")

# 8. Reviews
elif choice=="Reviews":
    st.subheader("Leave a Review")
    if "user_id" not in st.session_state:
        st.warning("Log in first!")
    else:
        # --- Review a Transaction (existing code) ---
        txns = session.query(Transaction).filter_by(BuyerID=st.session_state.user_id).all()
        for t in txns:
            if not t.review:
                stars = st.slider(f"Rating for txn {t.TransactionID}", 1,5)
                txt   = st.text_input(f"Comment for txn {t.TransactionID}")
                if st.button(f"Review {t.TransactionID}"):
                    r = Review(TransactionID=t.TransactionID,
                               ReviewerID=st.session_state.user_id,
                               Rating=stars, Comment=txt)
                    session.add(r); session.commit()
                    st.success("Thanks for your review!")

        # --- Review a User (new feature) ---
        st.markdown("### Leave a Review About a User")
        users = session.query(User).filter(User.UserID != st.session_state.user_id).all()
        user_options = {f"{u.Name} (UserID: {u.UserID})": u.UserID for u in users}
        if user_options:
            selected_user = st.selectbox("Select a user to review", list(user_options.keys()))
            user_id_to_review = user_options[selected_user]
            stars_user = st.slider("Rating for user", 1, 5, key="user_review_stars")
            txt_user = st.text_area("Comment about this user", key="user_review_comment")
            if st.button("Submit User Review"):
                r = Review(TransactionID=None,
                           ReviewerID=st.session_state.user_id,
                           RevieweeID=user_id_to_review if hasattr(Review, "RevieweeID") else None,
                           Rating=stars_user, Comment=txt_user)
                session.add(r)
                session.commit()
                st.success("Thanks for reviewing this user!")
        else:
            st.info("No other users to review.")

# 9. Reports
elif choice=="Reports":
    st.subheader("Reports & Export")
    # 8. aggregation example: avg price per category
    rpt1 = pd.read_sql(
      "SELECT CategoryName, AVG(Price) AS AvgPrice "
      "FROM Listings l JOIN Categories c USING(CategoryID) "
      "GROUP BY CategoryName", engine)
    st.write("Average Price per Category") 
    st.dataframe(rpt1)
    st.download_button("Download CSV", rpt1.to_csv(index=False), "avg_price.csv")

    # 9. subquery: users who sold >1 item
    rpt2 = pd.read_sql(
      "SELECT Username FROM Users WHERE UserID IN ("
      "  SELECT UserID FROM Listings WHERE Status='Sold' GROUP BY UserID HAVING COUNT(*)>1"
      ")", engine)
    st.write("Users with >1 sale")
    st.dataframe(rpt2)

    # 10. join across 3 tables: listing + user + category
    rpt3 = pd.read_sql(
      "SELECT l.Title, u.Username, c.CategoryName "
      "FROM Listings l "
      "JOIN Users u ON l.UserID=u.UserID "
      "JOIN Categories c ON l.CategoryID=c.CategoryID "
      "WHERE l.Status='Active'", engine)
    st.write("Active Listings + Seller + Category")
    st.dataframe(rpt3)

st.sidebar.write("CPSC 408 Team Community Connect ")
