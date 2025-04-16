### Personal Info
* Andrew Reigle & Jonathan Lopez
* Student ID : 2455047 & 2436878
* Chapman email: areigle@chapman.edu & jonlopez@chapman.edu
* DataBase Management 
* Assignment 5

### A description of any known compile or runtime errors, code limitations, or deviations from the assignment specifications
None of our knowledge

### DataBase Schema & Python Code

For our database schema, we separated the core entities into Riders, Drivers and Rides assigning ids as the primary keys. The primary keys from Riders and Drivers tables were used as foreign keys in the Rides table to track assigned rides between riders and drivers. 

The Rides table acts as a bridge that connects a specific rider to a specific driver, capturing essential trip details like pickup/dropoff locations, ride status, timestamps, and rider-provided ratings.

For the menu driven interface, we implimented specific rider and driver menus, that allow the user to create an account, request ride, view and make ratings for the ride/driver. 


### A list of all references used to complete the assignment
https://stackoverflow.com/questions/168736/how-do-you-set-a-default-value-for-a-mysql-datetime-column

We used this to help assign a date and time for ride_date attribute in the rides table.
