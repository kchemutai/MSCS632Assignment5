#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// 1. Ride Class (Base Class)
class Ride {
protected:
    string rideID;
    string pickupLocation;
    string dropoffLocation;
    float distance;
    float fare;
    
public:
    Ride(string id, string pickup, string dropoff, float dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist), fare(0.0) {}
    
    virtual ~Ride() {}
    
    virtual void calculateFare() = 0;
    
    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID << "\n"
             << "Pickup: " << pickupLocation << "\n"
             << "Dropoff: " << dropoffLocation << "\n"
             << "Distance: " << distance << " miles\n"
             << "Fare: $" << fare << "\n";
    }
    
    string getRideID() const { return rideID; }
    string getPickupLocation() const { return pickupLocation; }
    string getDropoffLocation() const { return dropoffLocation; }
    float getDistance() const { return distance; }
    float getFare() const { return fare; }
};

// 2. Specific Ride Subclasses
class StandardRide : public Ride {
private:
    static const float BASE_FARE;
    static const float PER_MILE;
    
public:
    StandardRide(string id, string pickup, string dropoff, float dist)
        : Ride(id, pickup, dropoff, dist) {
        calculateFare();
    }
    
    void calculateFare() override {
        fare = BASE_FARE + (distance * PER_MILE);
    }
};

const float StandardRide::BASE_FARE = 2.0;
const float StandardRide::PER_MILE = 1.5;

class PremiumRide : public Ride {
private:
    static const float BASE_FARE;
    static const float PER_MILE;
    static const float SERVICE_FEE;
    
public:
    PremiumRide(string id, string pickup, string dropoff, float dist)
        : Ride(id, pickup, dropoff, dist) {
        calculateFare();
    }
    
    void calculateFare() override {
        fare = BASE_FARE + (distance * PER_MILE) + SERVICE_FEE;
    }
    
    void rideDetails() const override {
        cout << "PREMIUM RIDE DETAILS:\n";
        Ride::rideDetails();
        cout << "Includes premium service fee: $" << SERVICE_FEE << "\n";
    }
};

const float PremiumRide::BASE_FARE = 5.0;
const float PremiumRide::PER_MILE = 2.5;
const float PremiumRide::SERVICE_FEE = 3.0;

// 3. Driver Class
class Driver {
private:
    string driverID;
    string name;
    float rating;
    vector<shared_ptr<Ride>> assignedRides;
    
public:
    Driver(string id, string n, float r)
        : driverID(id), name(n), rating(r) {}
    
    void addRide(shared_ptr<Ride> ride) {
        assignedRides.push_back(ride);
    }
    
    void getDriverInfo() const {
        cout << "Driver ID: " << driverID << "\n"
             << "Name: " << name << "\n"
             << "Rating: " << rating << "/5.0\n"
             << "Completed Rides: " << assignedRides.size() << "\n";
    }
    
    float getRating() const { return rating; }
    int getAssignedRidesCount() const { return assignedRides.size(); }
};

// 4. Rider Class
class Rider {
private:
    string riderID;
    string name;
    vector<shared_ptr<Ride>> requestedRides;
    
public:
    Rider(string id, string n)
        : riderID(id), name(n) {}
    
    void requestRide(shared_ptr<Ride> ride) {
        requestedRides.push_back(ride);
    }
    
    void viewRides() const {
        cout << "Ride History for " << name << " (ID: " << riderID << "):\n";
        for (const auto& ride : requestedRides) {
            ride->rideDetails();
            cout << "-----------------\n";
        }
    }
    
    int getRequestedRidesCount() const { return requestedRides.size(); }
};

// 5. Main Function
int main() {
    cout << "Ride Sharing System Demonstration\n";
    cout << "================================\n\n";

    // Create rides of different types
    vector<shared_ptr<Ride>> rides;
    rides.push_back(make_shared<StandardRide>("R001", "123 Main St", "456 Oak Ave", 5.2));
    rides.push_back(make_shared<PremiumRide>("R002", "789 Pine Rd", "321 Elm Blvd", 8.7));
    rides.push_back(make_shared<StandardRide>("R003", "555 Center St", "999 Park Ave", 3.1));
    rides.push_back(make_shared<PremiumRide>("R004", "111 River Rd", "444 Mountain Ln", 12.5));

    // Create driver and rider
    Driver driver("D100", "John Smith", 4.8);
    Rider rider("C200", "Alice Johnson");

    // Assign rides
    for (const auto& ride : rides) {
        driver.addRide(ride);
        // Create a copy of the ride for the rider
        if (dynamic_cast<PremiumRide*>(ride.get())) {
            rider.requestRide(make_shared<PremiumRide>(*dynamic_cast<PremiumRide*>(ride.get())));
        } else {
            rider.requestRide(make_shared<StandardRide>(*dynamic_cast<StandardRide*>(ride.get())));
        }
    }

    // Display information
    cout << "\nDriver Information:\n";
    driver.getDriverInfo();

    cout << "\nRider Ride History:\n";
    rider.viewRides();

    cout << "\nPolymorphic Ride Details:\n";
    for (const auto& ride : rides) {
        ride->rideDetails();
        cout << "-----------------\n";
    }

    return 0;
}