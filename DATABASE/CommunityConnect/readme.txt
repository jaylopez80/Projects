1--Install dependencies on shell in VSCODE Once only

pip install sqlalchemy pymysql pandas streamlit cryptography

2--Run the schema setup in VSCODE terminal
python NMP_setup.py

ENSURE TO CHANGE DATBASE URL password to your credentials

--This will DROP/CREATE the community_connect database, define all tables (Users, Categories, Listings, Transactions, Reviews, Messages),
 set up PK/FK constraints, indexes, a view, and insert 3 sample rows each.

3--Start the front-end
python -m streamlit run NMP_app.py

--That launches a local Streamlit UI where you can sign up, view and filter listings, create/edit/delete records, send messages, checkout transactions, 
   leave reviews, run reports, etc.
