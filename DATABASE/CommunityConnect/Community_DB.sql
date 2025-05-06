
DROP DATABASE IF EXISTS community_connect;
CREATE DATABASE community_connect;
USE community_connect;

-- 1. Users table
CREATE TABLE Users (UserID INT AUTO_INCREMENT PRIMARY KEY,
  Username VARCHAR(50) NOT NULL UNIQUE,
  PasswordHash VARCHAR(255) NOT NULL,
  Name VARCHAR(100) NOT NULL,
  Email VARCHAR(100) NOT NULL UNIQUE,
  Phone VARCHAR(20),
  Address VARCHAR(255),
  Neighborhood VARCHAR(100),
  RegistrationDate DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
);

INSERT INTO Users (Username, PasswordHash, Name, Email, Phone, Address, Neighborhood)
VALUES
  ('jdoe','let123','John Doe','jdoe@aol.com','323-456-9132','123 Slay St','Downtown'),
  ('nightmare1','elmo!','Freddy Kru','fkru@aol.com','616-452-5874','456 Elm Ave','Midtown'),
  ('Bhana1','hello21!','Benny Hana','bhana@aol.com','818-458-3645','789 Habachi Rd','Uptown');
-- Test
SELECT *
FROM Users;

-- 2. Categories table
CREATE TABLE Categories (
  CategoryID INT AUTO_INCREMENT PRIMARY KEY,
  CategoryName VARCHAR(50) NOT NULL UNIQUE,
  Description TEXT
);

INSERT INTO Categories (CategoryName, Description)
VALUES
  ('Electronics','Phones, computers and consoles'),
  ('Furniture','Chairs and sofas'),
  ('Services','Home repair and pet walking');
-- Test
SELECT *
FROM Categories;

-- 3. Listings table
CREATE TABLE Listings (ListingID INT AUTO_INCREMENT PRIMARY KEY,
  UserID INT NOT NULL, CategoryID INT NOT NULL,
  Title VARCHAR(150) NOT NULL, Description TEXT,
  Price DECIMAL(10,2), ImageURL VARCHAR(255),
  ListingDate DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  Status ENUM('Active','Sold','Expired') NOT NULL DEFAULT 'Active',
  FOREIGN KEY (UserID) REFERENCES Users(UserID),
  FOREIGN KEY (CategoryID) REFERENCES Categories(CategoryID));

INSERT INTO Listings (UserID, CategoryID, Title, Description, Price, ImageURL, ListingDate, Status)
VALUES
  (1, 1, 'iPhone 13', 'Used iPhone 13, 128GB', 650.00, 'img/iphone13.jpg','2025-04-01 09:00:00','Active'),
  (2, 2, 'Vintage Oak Table', ' oak dining table seats 6', 300.00, 'img/oaktable.jpg','2025-04-02 14:30:00','Active'),
  (3, 3, 'Lawn Mowing Service', 'Weekly lawn mowing', 50.00, NULL,'2025-04-03 08:15:00','Active');
-- Test
SELECT *
FROM Listings;

-- 4. Transactions table
CREATE TABLE Transactions (TransactionID INT AUTO_INCREMENT PRIMARY KEY,
  ListingID INT NOT NULL, BuyerID INT NOT NULL,
  TransactionDate DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PaymentStatus ENUM('Pending','Completed','Refunded') NOT NULL DEFAULT 'Pending',
  TotalAmount DECIMAL(10,2) NOT NULL,
  FOREIGN KEY (ListingID) REFERENCES Listings(ListingID),
  FOREIGN KEY (BuyerID)   REFERENCES Users(UserID));

INSERT INTO Transactions (ListingID, BuyerID, TransactionDate, PaymentStatus, TotalAmount)
VALUES
  (1, 2, '2025-04-10 10:00:00','Completed',650.00),
  (2, 3, '2025-04-11 11:15:00','Pending',300.00),
  (3, 1, '2025-04-12 12:45:00','Completed',50.00);
-- Test
SELECT *
FROM Transactions;

-- 5. Reviews table
CREATE TABLE Reviews (ReviewID INT AUTO_INCREMENT PRIMARY KEY,
  TransactionID INT NOT NULL, ReviewerID INT NOT NULL,
  Rating INT NOT NULL CHECK (Rating BETWEEN 1 AND 5),
  Comment TEXT, ReviewDate DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY (TransactionID) REFERENCES Transactions(TransactionID),
  FOREIGN KEY (ReviewerID)    REFERENCES Users(UserID));

INSERT INTO Reviews (TransactionID, ReviewerID, Rating, Comment)
VALUES
  (1, 2, 5, 'Great phone, as described!'),
  (2, 3, 4, 'Table is sturdy, minor scratches.'),
  (3, 1, 5, 'Lawn looks great every week.');
-- TEST
SELECT *
FROM Reviews;

-- 6. Messages table
CREATE TABLE Messages (MessageID INT AUTO_INCREMENT PRIMARY KEY,
  SenderID INT NOT NULL, ReceiverID INT NOT NULL,
  Subject VARCHAR(150), Content TEXT,
  MessageDate DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY (SenderID)   REFERENCES Users(UserID),
  FOREIGN KEY (ReceiverID) REFERENCES Users(UserID));

INSERT INTO Messages (SenderID, ReceiverID, Subject, Content)
VALUES
  (1, 2, 'Interested in iPhone 13', 'Is the phone still available?'),
  (2, 1, 'Re: iPhone 13', 'Yes it is still available'),
  (3, 2, 'Service Pricing', 'Do you offer discounts for veterans?');

-- TEST
SELECT *
FROM Messages;