"Ride Sharing System Demonstration in Smalltalk"

"1. Ride Class (Base Class)"
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance fare |
    
    initialize: id pickup: pickup dropoff: dropoff dist: dist [
        rideID := id.
        pickupLocation := pickup.
        dropoffLocation := dropoff.
        distance := dist.
        fare := 0.
        ^self
    ]
    
    calculateFare [
        self subclassResponsibility
    ]
    
    rideDetails [
        Transcript 
            show: 'Ride ID: ', rideID; cr;
            show: 'Pickup: ', pickupLocation; cr;
            show: 'Dropoff: ', dropoffLocation; cr;
            show: 'Distance: ', distance asString, ' miles'; cr;
            show: 'Fare: $', fare asString; cr.
    ]
    
    rideID [ ^rideID ]
    pickupLocation [ ^pickupLocation ]
    dropoffLocation [ ^dropoffLocation ]
    distance [ ^distance ]
    fare [ ^fare ]
]

"2. Specific Ride Subclasses"
Ride subclass: StandardRide [
    StandardRide class >> baseFare [ ^2.0 ]
    StandardRide class >> perMile [ ^1.5 ]
    
    initialize: id pickup: pickup dropoff: dropoff dist: dist [
        super initialize: id pickup: pickup dropoff: dropoff dist: dist.
        self calculateFare.
        ^self
    ]
    
    calculateFare [
        fare := (self class baseFare) + (distance * (self class perMile)).
    ]
]

Ride subclass: PremiumRide [
    PremiumRide class >> baseFare [ ^5.0 ]
    PremiumRide class >> perMile [ ^2.5 ]
    PremiumRide class >> serviceFee [ ^3.0 ]
    
    initialize: id pickup: pickup dropoff: dropoff dist: dist [
        super initialize: id pickup: pickup dropoff: dropoff dist: dist.
        self calculateFare.
        ^self
    ]
    
    calculateFare [
        fare := (self class baseFare) + (distance * (self class perMile)) + (self class serviceFee).
    ]
    
    rideDetails [
        Transcript show: 'PREMIUM RIDE DETAILS:'; cr.
        super rideDetails.
        Transcript show: 'Includes premium service fee: $', (self class serviceFee) asString; cr.
    ]
]

"3. Driver Class"
Object subclass: Driver [
    | driverID name rating assignedRides |
    
    initialize: id name: n rating: r [
        driverID := id.
        name := n.
        rating := r.
        assignedRides := OrderedCollection new.
        ^self
    ]
    
    addRide: aRide [
        assignedRides add: aRide.
    ]
    
    getDriverInfo [
        Transcript 
            show: 'Driver ID: ', driverID; cr;
            show: 'Name: ', name; cr;
            show: 'Rating: ', rating asString, '/5.0'; cr;
            show: 'Completed Rides: ', assignedRides size asString; cr.
    ]
    
    driverID [ ^driverID ]
    name [ ^name ]
    rating [ ^rating ]
    assignedRidesCount [ ^assignedRides size ]
]

"4. Rider Class"
Object subclass: Rider [
    | riderID name requestedRides |
    
    initialize: id name: n [
        riderID := id.
        name := n.
        requestedRides := OrderedCollection new.
        ^self
    ]
    
    requestRide: aRide [
        requestedRides add: aRide.
    ]
    
    viewRides [
        Transcript show: 'Ride History for ', name, ' (ID: ', riderID, '):'; cr.
        requestedRides do: [:ride | 
            ride rideDetails.
            Transcript show: '-----------------'; cr.
        ].
    ]
    
    riderID [ ^riderID ]
    name [ ^name ]
    requestedRidesCount [ ^requestedRides size ]
]

"5. Main Program"
| rides driver rider |

Transcript clear.
Transcript show: 'Ride Sharing System Demonstration'; cr;
           show: '================================'; cr; cr.

"Create rides of different types"
rides := OrderedCollection new.
rides add: (StandardRide new initialize: 'R001' pickup: '123 Main St' dropoff: '456 Oak Ave' dist: 5.2).
rides add: (PremiumRide new initialize: 'R002' pickup: '789 Pine Rd' dropoff: '321 Elm Blvd' dist: 8.7).
rides add: (StandardRide new initialize: 'R003' pickup: '555 Center St' dropoff: '999 Park Ave' dist: 3.1).
rides add: (PremiumRide new initialize: 'R004' pickup: '111 River Rd' dropoff: '444 Mountain Ln' dist: 12.5).

"Create driver and rider"
driver := Driver new initialize: 'D100' name: 'John Smith' rating: 4.8.
rider := Rider new initialize: 'C200' name: 'Alice Johnson'.

"Assign rides"
rides do: [:ride |
    driver addRide: ride.
    "In Smalltalk, we can use copy to create a new instance with the same values"
    rider requestRide: (ride copy).
].

"Display information"
Transcript show: 'Driver Information:'; cr.
driver getDriverInfo.
Transcript cr.

Transcript show: 'Rider Ride History:'; cr.
rider viewRides.
Transcript cr.

"Demonstrate polymorphism"
Transcript show: 'Polymorphic Ride Details:'; cr.
rides do: [:ride |
    ride rideDetails.
    Transcript show: '-----------------'; cr.
].