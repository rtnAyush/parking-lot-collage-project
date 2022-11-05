# parking-lot-collage-project
This i made in 3rd semester
Concepts used in this project:
          Basic CPP knowledge , File input/output , Basic knowleadge of OOPs .
          

Question :
Parking Lot Problem -

I own a multi-storey parking lot that can hold up to 'n' cars at any given point in time. Each slot is given a number starting at 1 increasing with increasing distance from the entry point in steps of one. I want to create an automated ticketing system that allows my customers use my parking lot without human intervention.

When a car enters my parking lot, I want to have a ticket issued to the driver. The ticket issuing process includes us documenting the registration number (number plate) and the colour of the car and allocating an available parking slot to the car before actually
handing over a ticket to the driver (we assume that our customers are nice enough to always park in the slots allocated to them). The customer should be allocated a parking slot which is nearest to the entry. At the exit the customer returns the ticket which then marks the slot they were using as being available.

Due to government regulation, the system should provide me with the ability to find out:

a) Registration numbers of all cars of a particular colour.

b) Slot number in which a car with a given registration number is parked.

c) Slot numbers of all slots where a car of a particular colour is parked.

We interact with the system via a simple set of commands which produce a specific output.

Please take a look at the example below, which includes all the commands you need to support - they're self explanatory. The system should allow input in two ways. Just to clarify, the same codebase should support both modes of input (we don't want two distinct submissions).
    It should provide us with an interactive command prompt based
    shell where commands can be typed in

    It should accept a filename as a parameter at the command prompt
    and read the commands from that file


Commands are,

create_parking_lot 50
park KA01R9988 blue
unpark KA01R9977
find_parking_slot 5
find_car_number KL01R6699
find_car blue
filename.txt
WORING:::
when you run this cpp file , it prints the above option list with an option ""type 1 to close program"".
after it will make a database.txt file ,in which it will store token number====>
        token number consist of car_number-slot_number-color  (KL01R6699-L0-blue)
the program makes two row of parking slot L and R and if the size was 30 ,it will store 15 on either sides(if 31 the 16 in L and 15 in R).


$$ park() ,data function does this token generation part and sore it into database.txt file and make parked place array value to one
$$  unpark() , data function select requrid value from database.txt and add "unpark-" before that entry and make parked place array value to zero
