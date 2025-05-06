#install dependencies in shelll
#pip install sqlalchemy pymysql pandas streamlit cryptography


from sqlalchemy import (
    create_engine, Column, Integer, String, Text, DECIMAL,
    DateTime, Enum, ForeignKey, Boolean, Index, func, text
)
from sqlalchemy.orm import declarative_base, relationship, sessionmaker
import datetime

# 1. Change this to your MySQL credentials
DATABASE_URL = "mysql+pymysql://root:Student123!@localhost:3306/community_connect"

# Create engine & metadata
# echo=True will show all SQL statements for debugging
engine = create_engine(DATABASE_URL.replace("/community_connect",""),
                       echo=True, future=True)
conn = engine.connect()
conn.execute(text("DROP DATABASE IF EXISTS community_connect;"))
conn.execute(text("CREATE DATABASE community_connect;"))
conn.execute(text("USE community_connect;"))
conn.close()

# Recreate engine bound to community_connect
engine = create_engine(DATABASE_URL, echo=True, future=True)
Base = declarative_base()
Session = sessionmaker(bind=engine)

# 2. Define models

class User(Base):
    __tablename__ = "Users"
    UserID          = Column(Integer, primary_key=True, autoincrement=True)
    Username        = Column(String(50), nullable=False, unique=True, index=True)
    PasswordHash    = Column(String(255), nullable=False)
    Name            = Column(String(100), nullable=False)
    Email           = Column(String(100), nullable=False, unique=True)
    Phone           = Column(String(20))
    Address         = Column(String(255))
    Neighborhood    = Column(String(100))
    RegistrationDate= Column(DateTime, default=func.now())
    # relationships:
    listings        = relationship("Listing", back_populates="seller")
    sent_messages   = relationship("Message", back_populates="sender",
                                   foreign_keys="Message.SenderID")
    recv_messages   = relationship("Message", back_populates="receiver",
                                   foreign_keys="Message.ReceiverID")
    reviews_written = relationship("Review", back_populates="reviewer",
                                   foreign_keys="Review.ReviewerID")
    purchases       = relationship("Transaction", back_populates="buyer")

class Category(Base):
    __tablename__ = "Categories"
    CategoryID   = Column(Integer, primary_key=True, autoincrement=True)
    CategoryName = Column(String(50), nullable=False, unique=True)
    Description  = Column(Text)
    listings     = relationship("Listing", back_populates="category")

class Listing(Base):
    __tablename__ = "Listings"
    ListingID    = Column(Integer, primary_key=True, autoincrement=True)
    UserID       = Column(Integer, ForeignKey("Users.UserID"), nullable=False, index=True)
    CategoryID   = Column(Integer, ForeignKey("Categories.CategoryID"), nullable=False)
    Title        = Column(String(150), nullable=False, index=True)
    Description  = Column(Text)
    Price        = Column(DECIMAL(10,2))
    ImageURL     = Column(String(255))
    ListingDate  = Column(DateTime, default=func.now())
    Status       = Column(Enum("Active","Sold","Expired"), default="Active", index=True)
    seller       = relationship("User", back_populates="listings")
    category     = relationship("Category", back_populates="listings")
    transaction  = relationship("Transaction", back_populates="listing",
                                uselist=False)

class Transaction(Base):
    __tablename__ = "Transactions"
    TransactionID   = Column(Integer, primary_key=True, autoincrement=True)
    ListingID       = Column(Integer, ForeignKey("Listings.ListingID"), nullable=False, unique=True)
    BuyerID         = Column(Integer, ForeignKey("Users.UserID"), nullable=False)
    TransactionDate = Column(DateTime, default=func.now())
    PaymentStatus   = Column(Enum("Pending","Completed","Refunded"), default="Pending", index=True)
    TotalAmount     = Column(DECIMAL(10,2), nullable=False)
    listing         = relationship("Listing", back_populates="transaction")
    buyer           = relationship("User", back_populates="purchases")
    review          = relationship("Review", back_populates="transaction",
                                   uselist=False)

class Review(Base):
    __tablename__ = "Reviews"
    ReviewID       = Column(Integer, primary_key=True, autoincrement=True)
    TransactionID  = Column(Integer, ForeignKey("Transactions.TransactionID"), nullable=False, unique=True)
    ReviewerID     = Column(Integer, ForeignKey("Users.UserID"), nullable=False)
    Rating         = Column(Integer, nullable=False)  # should be 1–5
    Comment        = Column(Text)
    ReviewDate     = Column(DateTime, default=func.now())
    transaction    = relationship("Transaction", back_populates="review")
    reviewer       = relationship("User", back_populates="reviews_written")

class Message(Base):
    __tablename__ = "Messages"
    MessageID    = Column(Integer, primary_key=True, autoincrement=True)
    SenderID     = Column(Integer, ForeignKey("Users.UserID"), nullable=False)
    ReceiverID   = Column(Integer, ForeignKey("Users.UserID"), nullable=False)
    Subject      = Column(String(150))
    Content      = Column(Text)
    MessageDate  = Column(DateTime, default=func.now())
    sender       = relationship("User", foreign_keys=[SenderID],
                                back_populates="sent_messages")
    receiver     = relationship("User", foreign_keys=[ReceiverID],
                                back_populates="recv_messages")

# 3. Create tables and indexes
Base.metadata.create_all(engine)

# Add a view: active_listings_view
with engine.begin() as conn:
    conn.exec_driver_sql("""
      CREATE OR REPLACE VIEW active_listings AS
      SELECT l.ListingID, l.Title, l.Price, u.Username AS Seller, c.CategoryName
      FROM Listings l
      JOIN Users u      ON l.UserID=u.UserID
      JOIN Categories c ON l.CategoryID=c.CategoryID
      WHERE l.Status='Active';
    """)
# Create an index on Transactions.PaymentStatus for faster reporting
with engine.begin() as conn:
    conn.exec_driver_sql("CREATE INDEX idx_txn_status ON Transactions(PaymentStatus);")

# 4. Insert 3 sample rows per table
session = Session()
# Users already auto-sampled above; skip if duplication
if session.query(User).count()==0:
    session.add_all([
      User(Username="alice", PasswordHash="h1", Name="Alice A", Email="alice@example.com"),
      User(Username="bob",   PasswordHash="h2", Name="Bob B",   Email="bob@example.com"),
      User(Username="carol", PasswordHash="h3", Name="Carol C", Email="carol@example.com")
    ])
# Categories
if session.query(Category).count()==0:
    session.add_all([
      Category(CategoryName="Electronics", Description="Gadgets & devices"),
      Category(CategoryName="Furniture",   Description="Home & office furniture"),
      Category(CategoryName="Services",    Description="Local service listings")
    ])
session.commit()

# Listings
if session.query(Listing).count()==0:
    session.add_all([
      Listing(UserID=1, CategoryID=1, Title="iPhone 14", Description="Mint condition", Price=700),
      Listing(UserID=2, CategoryID=2, Title="Office Chair",Description ="Ergonomic, black", Price=120),
      Listing(UserID=3, CategoryID=3, Title="Dog Walking",Description ="30 min walk", Price=20)
    ])
session.commit()

# Transactions
if session.query(Transaction).count()==0:
    session.add_all([
      Transaction(ListingID=1, BuyerID=2, TotalAmount=700, PaymentStatus="Completed"),
      Transaction(ListingID=2, BuyerID=3, TotalAmount=120, PaymentStatus="Pending"),
      Transaction(ListingID=3, BuyerID=1, TotalAmount=20,  PaymentStatus="Completed")
    ])
session.commit()

# Reviews
if session.query(Review).count()==0:
    session.add_all([
      Review(TransactionID=1, ReviewerID=2, Rating=5, Comment="Works great!"),
      Review(TransactionID=2, ReviewerID=3, Rating=4, Comment="Pretty good."),
      Review(TransactionID=3, ReviewerID=1, Rating=5, Comment="Excellent service.")
    ])
session.commit()

# Messages
if session.query(Message).count()==0:
    session.add_all([
      Message(SenderID=1, ReceiverID=2, Subject="Interested?", Content="Is this available?"),
      Message(SenderID=2, ReceiverID=1, Subject="Re: Interested", Content="Yes, it is!"),
      Message(SenderID=3, ReceiverID=1, Subject="Question", Content="Can you deliver?")
    ])
session.commit()

print(" Database schema and sample data ready!")
