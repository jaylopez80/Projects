import mysql.connector

# Function to create a new rider account
def create_rider(cursor, cnx):
    # Get rider details from user
    username = input("Enter username: ")
    password = input("Enter password: ")
    name = input("Enter full name: ")
    contact_number = input("Enter contact number: ")
    email = input("Enter email: ")
    
    # Insert new rider into the Riders table
    query = "INSERT INTO Riders (username, password, name, contact_number, email) VALUES (%s, %s, %s, %s, %s)"
    cursor.execute(query, (username, password, name, contact_number, email))
    cnx.commit()
    print("Rider account created.")
    #print rider id 
    new_rider_id = cursor.lastrowid
    print(f"Your Rider ID is: {new_rider_id}")
    

# Function to create a new driver account
def create_driver(cursor, cnx):
    # Get driver details from user
    username = input("Enter username: ")
    password = input("Enter password: ")
    name = input("Enter full name: ")
    contact_number = input("Enter contact number: ")
    email = input("Enter email: ")
    active_status = input("Enter active status (1 for active, 0 for inactive): ")
    
    # Insert new driver into the Drivers table
    query = "INSERT INTO Drivers (username, password, name, contact_number, email, active_status) VALUES (%s, %s, %s, %s, %s, %s)"
    cursor.execute(query, (username, password, name, contact_number, email, active_status))
    cnx.commit()
    print("Driver account created.")
    #print driver id
    new_driver_id = cursor.lastrowid
    print(f"Your Driver ID is: {new_driver_id}")

# Menu and actions for a rider
def rider_menu(cursor):
    rider_id = input("Enter your Rider ID: ")

    while True:

        print("\nOptions:\n1: View Rides\n2: Find a Driver\n3: Rate My Driver\n4: Exit")
        option = input("Select an option: ")

        # View past rides for this rider
        if option == '1':
            query = "SELECT * FROM Rides WHERE rider_id = %s"
            cursor.execute(query, (rider_id,))
            rides = cursor.fetchall()
            print("Your Rides:")
            for ride in rides:
                print(ride)

        # Request a driver and create a new ride
        elif option == '2':
            pickup = input("Enter pick up location: ")
            dropoff = input("Enter drop off location: ")

            # Query for an active driver
            query = "SELECT driver_id, name FROM Drivers WHERE active_status = 1 LIMIT 1"
            cursor.execute(query)
            driver = cursor.fetchone()

            if driver:
                print(f"Driver {driver[1]} (ID: {driver[0]}) found!")
                
                # Insert a new ride into the Rides table
                query = """INSERT INTO Rides 
                        (rider_id, driver_id, pickup_location, dropoff_location, ride_status) 
                        VALUES (%s, %s, %s, %s, %s)"""
                cursor.execute(query, (rider_id, driver[0], pickup, dropoff, 'in-progress'))
                print("Ride created. Enjoy your trip!")
                print(f"Your Ride ID is: {cursor.lastrowid}")
            else:
                print("No active drivers available at the moment.")

       
        elif option == '3':
            #Find the most recent ride
            query = """
                SELECT * FROM Rides 
                WHERE rider_id = %s 
                ORDER BY ride_date DESC 
                LIMIT 1
            """
            cursor.execute(query, (rider_id,))
            recent_ride = cursor.fetchone()

            if not recent_ride:
                print("No rides found for this rider.")
                continue

            print("Most Recent Ride:")
            print(recent_ride)

            # Ask the user to confirm the ride
            confirm = input("Is this the ride you want to rate? (y/n): ").lower()

            # If no, let the user enter a ride ID manually
            if confirm != 'y':
                ride_id = input("Enter the Ride ID you want to rate: ")
                query = "SELECT * FROM Rides WHERE ride_id = %s AND rider_id = %s"
                cursor.execute(query, (ride_id, rider_id))
                chosen_ride = cursor.fetchone()

                if not chosen_ride:
                    print("Invalid Ride ID or this ride doesn't belong to you.")
                    continue

                print("Selected Ride:")
                print(chosen_ride)

                confirm = input("Confirm this ride? (y/n): ").lower()
                if confirm != 'y':
                    print("Rating cancelled.")
                    continue
            else:
                ride_id = recent_ride[0]  # ride_id is the first field

            # Submit rating
            rating = float(input("Enter your rating for this ride (e.g., 4.5): "))
            query = "UPDATE Rides SET rating = %s, ride_status = 'completed' WHERE ride_id = %s"
            cursor.execute(query, (rating, ride_id))
            print("Thank you! Your rating has been submitted.")
        
        elif option == '4':
            print("Exiting rider menu.")
            break

# Menu and actions for a driver
def driver_menu(cursor):
    driver_id = input("Enter your Driver ID: ")

    while True:
    
        print("\nOptions:\n1: View Rating\n2: View Rides\n3: Activate/Deactivate Driver Mode\n4: Exit")
        option = input("Select an option: ")

        # View the average rating for this driver
        if option == '1':
            query = "SELECT AVG(rating) FROM Rides WHERE driver_id = %s AND rating IS NOT NULL"
            cursor.execute(query, (driver_id,))
            avg_rating = cursor.fetchone()[0]
            print(f"Your average rating is: {avg_rating if avg_rating else 'No ratings yet'}")

        # View all rides associated with this driver
        elif option == '2':
            query = "SELECT * FROM Rides WHERE driver_id = %s"
            cursor.execute(query, (driver_id,))
            rides = cursor.fetchall()
            print("Your Rides:")
            for ride in rides:
                print(ride)

        # Toggle the driver's active status
        elif option == '3':
            # Check current active status
            query = "SELECT active_status FROM Drivers WHERE driver_id = %s"
            cursor.execute(query, (driver_id,))
            current_status = cursor.fetchone()[0]

            # Set to inactive if currently active, or active if currently inactive
            new_status = 0 if current_status else 1
            query = "UPDATE Drivers SET active_status = %s WHERE driver_id = %s"
            cursor.execute(query, (new_status, driver_id))
            print("Driver mode updated.")
        
        elif option == '4':
            print("Exiting driver menu.")
            break

# Main entry point for the application
def main():
    # Connect to the RideShareDB database
    cnx = mysql.connector.connect(user='root', password='raintree', host='127.0.0.1', database='RideShareDB')
    cursor = cnx.cursor()
    while True: 
        print("Welcome to the RideShare App!")
        print("1: New User\n2: Existing Rider\n3: Existing Driver\n4: Exit")
        user_type = input("Select your option (1-4): ")

        # New user account creation
        if user_type == '1':
            account_type = input("Create account as (r)ider or (d)river? ")
            if account_type.lower() == 'r':
                create_rider(cursor, cnx)
            elif account_type.lower() == 'd':
                create_driver(cursor, cnx)

        # Rider menu
        elif user_type == '2':
            rider_menu(cursor)

        # Driver menu
        elif user_type == '3':
            driver_menu(cursor)
        
        elif user_type == '4':
            print("Exiting the application.")
            break

        else:
            print("Invalid option.")

        # Finalize all changes and close the connection
        cnx.commit()
        cursor.close()
        cnx.close()

# Run the program
if __name__ == '__main__':
    main()