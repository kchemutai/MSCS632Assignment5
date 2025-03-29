# MSCS632Assignment5

1	Overview

You will apply concepts from object-oriented programming by developing a class-based Ride Sharing System in two different languages, Smalltalk and C++, demonstrating correct usage of at least three OOP principles: encapsulation, inheritance, and polymorphism.


2	Application Requirements

The Ride Sharing System must include the following components at a minimum. You should add additional functionality and feel free to be creative.

    1. Ride Class:
    Create a base class Ride that holds core details such as rideID, pickupLocation, dropoffLocation, distance, and fare.
    Define methods for calculating the fare() based on distance and a rideDetails() method to display ride information.
    2. Specific Ride Subclasses:
    Implement at least two derived classes of Ride, such as StandardRide and PremiumRide.
    Each subclass should override the fare() method to calculate the fare based on ride type (e.g., premium rides might cost more per mile).
    Demonstrate polymorphism by calling the overridden fare() method on a list of different ride types.
    3. Driver Class:
    Create a Driver class with attributes like driverID, name, rating, and assignedRides, a list of rides completed by the driver.
    Include methods such as addRide(Ride ride) to add rides to the driver’s list and getDriverInfo() to display driver details.
    Use encapsulation to keep assignedRides private and accessible only through defined methods.
    4. Rider Class:
    Create a Rider class with attributes like riderID, name, and requestedRides, a list of rides requested by the rider.
    Include methods such as requestRide(Ride ride) to add a ride to the rider’s requested list, and viewRides() to display ride history.
    5. System Functionality
    Demonstrate polymorphism by storing rides of different types in a list (array or collection) and invoking fare() and rideDe- tails() polymorphically.


3	Deliverable

    1. Code Implementation:
    Implement the Ride Sharing System in Smalltalk and C++, ensuring it meets all specified requirements. Your code should be stored in a GitHub repo for this assignment. Add the link to the repo in your report.
    Both implementations should accurately demonstrate encap- sulation, inheritance, and polymorphism.
    2. Documentation:
    A brief report, 1-2 pages, explaining how each OOP principle is used in each language.
    Report should follow APA 7 guidelines.
    3. Sample Output
    Provide screenshots of your code and sample output showing system usage in both languages.
    The screenshots should be appended to your report.


Submit one document (.docx or pdf) that includes your report, GitHub link, and your screenshots.
