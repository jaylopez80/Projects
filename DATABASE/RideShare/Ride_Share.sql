CREATE DATABASE RideShareDB;

USE RideShareDB;


-- Table for drivers
CREATE TABLE Drivers (
    driver_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    name VARCHAR(100) NOT NULL,
    contact_number VARCHAR(20),
    email VARCHAR(100),
    active_status BOOLEAN DEFAULT 0
);

-- Table for riders
CREATE TABLE Riders (
    rider_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    name VARCHAR(100) NOT NULL,
    contact_number VARCHAR(20),
    email VARCHAR(100)
);

-- Table for rides
CREATE TABLE Rides (
    ride_id INT AUTO_INCREMENT PRIMARY KEY,
    rider_id INT,
    driver_id INT,
    pickup_location VARCHAR(255),
    dropoff_location VARCHAR(255),
    ride_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    ride_status VARCHAR(50),
    rating DECIMAL(3,2),
    FOREIGN KEY (rider_id) REFERENCES Riders(rider_id),
    FOREIGN KEY (driver_id) REFERENCES Drivers(driver_id)
);

-- Insert sample driver
INSERT INTO Drivers (username, password, name, contact_number, email, active_status)
VALUES ('driver1', 'password1', 'John Doe', '555-1234', 'johndoe@example.com', 1);

-- Insert sample rider
INSERT INTO Riders (username, password, name, contact_number, email)
VALUES ('rider1', 'password2', 'Jane Smith', '555-5678', 'janesmith@example.com');

INSERT INTO Riders (username, password, name, contact_number, email)
VALUES ('rider2', 'password3', 'Mclovin', '555-5679', 'Mclovin@example.com');
-- Insert a sample ride linking the rider and the driver
INSERT INTO Rides (rider_id, driver_id, pickup_location, dropoff_location, ride_status, rating)
VALUES (1, 1, '123 Main St', '456 Elm St', 'completed', 4.5);
