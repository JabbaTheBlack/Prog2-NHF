#include "node.h"
#include "linkedList.h"
#include "seat.h"
#include "coach.h"
#include "time.h"
#include "schedule.h"
#include "train.h"
#include "memtrace.h"
#include "ticketSystem.h"
#include "menu.h"


#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>


/**
 * @brief Test function for the LinkedList class.
 *
 * This function creates a LinkedList of integers, inserts some elements, removes an element,
 * and then displays the size of the list and its contents before and after the removal.
 */
void testLinkedList() {
    // Create a LinkedList of integers
    LinkedList<int> list;

    // Insert elements into the list
    list.insert(10);
    list.insert(20);
    list.insert(30);
    //Size should be 3 and elements 10,20,30
    assert(list.getSize() == 3);
    assert(list[0]->getData() == 10);
    assert(list[1]->getData() == 20);
    assert(list[2]->getData() == 30);
    // Remove an element from the list
    list.remove(20);
    // Size == 2
    assert(list.getSize() == 2);

    assert(list[0]->getData() == 10);
    assert(list[1]->getData() == 30);

    assert(list.begin()->getData() == 10);
    assert(list.end() == nullptr);

    std::cout <<"LinkedList: all tests passed\n\n";
}



/**
 * @brief function to test the seat class
 */
void testSeat() {
    // Create two seats
    Seat seat1(1);
    Seat seat2(2);

    // Initially, both seats should be unbooked
    assert(seat1.booked() == false);
    assert(seat2.booked() == false);
    // Book seat 1
    seat1.bookSeat();
    //seat 1 should be booked
    assert(seat1.booked() == true);
    assert(seat2.booked() == false);

    // Unbook seat 1
    seat1.unBookSeat();
    assert(seat1.booked() == false);
    // Check if seat 1 and seat 2 are equal
    assert((seat1 == seat2) == false);
    // Check the seat numbers
    assert(seat1.getSeatNumber() == 1);
    assert(seat2.getSeatNumber() == 2);

    std::cout<<"Seat: all test passed\n\n";
}



/**
 * @brief function to test the coach class
 */
void testCoach() {
    // Create a coach with 50 seats
    Coach coach(1, 50);

    // Check the initial state
    assert(coach.getCoachNumber() == 1);
    assert(coach.getNumSeats() == 50);
    assert(coach.getBooked() == false);

    // Book some seats
    for (int i = 0; i < 50; ++i) {
        coach.getSeats()[i].bookSeat();
    }
    if(coach.getSeats()[49].booked()){
        coach.booked();
    }
    // Check the updated state
    assert(coach.getBooked() == true);
    coach.serialize("coach.txt");
}


/**
 * @brief function to test the schedule class
 */
void testSchedule() {
    // Creating a Schedule object with initial values
    Schedule schedule("Budapest", "Vienna", Time(9, 0), Time(10, 0), 0);

    // Testing getter functions
    assert(schedule.getDeparture() == "Budapest");
    assert(schedule.getDestination() == "Vienna");
    Time time1(10,0);
    assert(schedule.getDepartureTime() == time1);
    time1.setHours(9);
    assert(schedule.getArrivalTime() == time1);
    assert(schedule.getLatency() == 0);;

    // Testing setter functions
    schedule.setDestination("Prague");
    assert(schedule.getDestination() == "Prague");
    schedule.setDeparture("Paris");
    assert(schedule.getDeparture() == "Paris");
    schedule.setArrivalTime(Time(12, 0));
    time1.setHours(12);
    assert(schedule.getArrivalTime() == time1);
    schedule.setDepartureTime(Time(11, 0));
    time1.setHours(11);
    assert(schedule.getDepartureTime() == time1);
    schedule.setLatency(20);
    assert(schedule.getLatency() == 20);

    // Printing modified schedule details
    std::cout<<std::endl<<schedule;
    std::cout<<"Schedule: all test passed\n\n";
    std::ofstream outfile("schedule.txt", std::ios::app);
    std::ifstream infile("schedule.txt");
    schedule.serialize(outfile);
    schedule.deserialize(infile);
}



/**
 * @brief function to test the train class
 */
void testTrain() {
    // Create a ticket system
    TicketSystem ticketSystem;

    // Create a train object
    Train *train = new Train(123, "Night Express", "Sebesvonat", false);
    ticketSystem.addTrain(*train);

    // Test getId() method
    assert(train->getId() == 123);

    // Test getName() method
    assert(train->getName() == "Night Express");

    // Test getType() method
    assert(train->getType() == "Sebesvonat");

    // Test getBooked() method
    assert(train->getBooked() == false);

    // Test setId() method
    train->setId(456);
    assert(train->getId() == 456);

    // Test setName() method
    train->setName("Morning Express");
    assert(train->getName() == "Morning Express");

    // Test setType() method
    train->setType("InterCity");
    assert(train->getType() == "InterCity");

    // Test setBooked() method
    train->setBooked(true);
    assert(train->getBooked() == true);

    // Test addSchedule() and getSchedule() methods
    Schedule *schedule1 = new Schedule("Budapest", "Vienna", Time(9, 0), Time(10, 0));
    Schedule *schedule2 = new Schedule("Vienna", "Prague", Time(13, 0), Time(14, 0));
    train->addSchedule(*schedule1);
    train->addSchedule(*schedule2);
    LinkedList<Schedule*> &schedules = train->getSchedule();
    assert(schedules.getSize() == 2);

    // Test removeSchedule() method
    train->removeSchedule(*schedule1);
    assert(schedules.getSize() == 1);

    // Test addCoach() and getCoaches() methods
    Coach *coach1 = new Coach(1, 50);
    coach1->getSeats()[0].bookSeat();
    coach1->getSeats()[1].bookSeat();
    coach1->getSeats()[2].bookSeat();
    assert(coach1->getSeats()[0].booked() == true);
    assert(coach1->getSeats()[1].booked() == true);
    assert(coach1->getSeats()[2].booked() == true);

    Coach *coach2 = new Coach(2, 40);
    coach2->getSeats()[2].bookSeat();
    coach2->getSeats()[0].bookSeat();
    coach2->getSeats()[1].bookSeat();

    train->addCoach(*coach1);
    train->addCoach(*coach2);
    LinkedList<Coach*> &coaches = train->getCoaches();
    assert(coaches.getSize() == 2);

    // Test removeCoach() method
    train->removeCoach(*coach1);
    assert(coaches.getSize() == 1);

    // Test serializeTrain() method
    train->serialize("testserializetrain.txt");

    // Print train details
    std::cout << "Train details: " << *train << std::endl;
    std::cout << "All tests passed successfully!\n" << std::endl;

    // Clean up memory
    delete coach1;
    delete schedule1;
}

/**
 * @brief funnction to test the ticket class
 */
void testTicket() {
    // Create some objects required for the ticket
    Schedule schedule("Budapest", "Vienna", Time(10, 0), Time(9, 0));
    Train train(123, "Night Express", "Sebesvonat", false);
    Coach coach(1, 50);
    Seat seat(1, false);

    // Create a ticket
    Ticket ticket(1, &schedule, &train, &coach, &seat, 0.5);

    // Test getId() method
    assert(ticket.getId() == 1);

    // Test getDiscount() method
    assert(ticket.getDiscount() == 0.5);

    // Test getSeat() method
    assert(ticket.getSeat() == &seat);

    // Test getCoach() method
    assert(ticket.getCoach() == &coach);

    // Test getTrain() method
    assert(ticket.getTrain() == &train);

    // Test setDiscount() method
    ticket.setDiscount(0.7);
    assert(ticket.getDiscount() == 0.7);

    // Test setTrain() method
    Train newTrain(456, "Morning Express", "InterCity", true);
    ticket.setTrain(&newTrain);
    assert(ticket.getTrain() == &newTrain);

    // Test setCoach() method
    Coach newCoach(2, 40);
    ticket.setCoach(&newCoach);
    assert(ticket.getCoach() == &newCoach);

    // Test setSeat() method
    Seat newSeat(2, true);
    ticket.setSeat(&newSeat);
    assert(ticket.getSeat() == &newSeat);

    // Test serializeTicket() method
    ticket.serialize("testserializeticket.txt");

    // Test output operator (<<) for Ticket
    std::cout << "Ticket details: " << ticket << std::endl;

    std::cout << "Ticket: all tests passed" << std::endl<<std::endl;
}

/**
 * @brief Function to test the time class
 */
void testTime() {
    // Test default constructor
    Time t1;
    assert(t1.getHours() == 0);
    assert(t1.getMinutes() == 0);

    // Test parameterized constructor
    Time t2(5, 45);
    assert(t2.getHours() == 5);
    assert(t2.getMinutes() == 45);

    // Test copy constructor
    Time t3(t2);
    assert(t3.getHours() == 5);
    assert(t3.getMinutes() == 45);

    // Test getters and setters
    t1.setHours(3);
    t1.setMinutes(30);
    assert(t1.getHours() == 3);
    assert(t1.getMinutes() == 30);

    // Test comparison operators
    assert(t1 < t2);
    assert(t2 > t1);
    assert(t1 <= t3);
    assert(t2 >= t3);
    assert(t2 == t3);

    // Test addition operator
    Time t4 = t1 + t2;
    assert(t4.getHours() == 9);
    assert(t4.getMinutes() == 15);

    // Test output operator
    std::cout << "Time t4: " << t4;

    // Test input operator
    Time t5;
    std::istringstream iss("4 25");
    iss >> t5;
    assert(t5.getHours() == 4);
    assert(t5.getMinutes() == 25);

    std::cout << "Time :All tests passed!\n" << std::endl;
}




/**
 * @brief Function to test adding train
 */
void testAddTrain() {
    TicketSystem ticketSystem;
    Train *train = new Train(1, "Express", "TypeA");
    ticketSystem.addTrain(*train);

    if (ticketSystem.getTrains().getSize() == 1 && ticketSystem.getTrains()[0]->getData()->getId() == 1) {
        std::cout << "Test Passed: Add Train" << std::endl;
    } else {
        std::cout << "Test Failed: Add Train" << std::endl;
    }
}

/**
 * @brief Test function for removing a train
 */
void testRemoveTrain() {
    TicketSystem ticketSystem;
    Train *train1 = new Train(1, "Express", "TypeA");
    Train *train2 = new Train(2, "Local", "TypeB");
    ticketSystem.addTrain(*train1);
    ticketSystem.addTrain(*train2);

    ticketSystem.removeTrain(1);

    if (ticketSystem.getTrains().getSize() == 1 && ticketSystem.getTrains()[0]->getData()->getId() == 2) {
        std::cout << "Test Passed: Remove Train" << std::endl;
    } else {
        std::cout << "Test Failed: Remove Train" << std::endl;
    }
}
/**
 * @brief Test function for issuing a ticket
 */
void testIssueTicket() {
    TicketSystem ticketSystem;
    Train *train2 = new Train(1, "Express", "TypeA");

    // Add three schedules
    Schedule *schedule1 = new Schedule("CityA", "CityB", Time(12, 0), Time(10, 0));
    Schedule *schedule2 = new Schedule("CityB", "CityC", Time(13, 30), Time(12, 1));
    Schedule *schedule3 = new Schedule("CityC", "CityD", Time(14, 30), Time(13, 30));
    train2->addSchedule(*schedule1);
    train2->addSchedule(*schedule2);
    train2->addSchedule(*schedule3);

    Coach *coach1 = new Coach(1, 10);
    train2->addCoach(*coach1);
    ticketSystem.addTrain(*train2);

    // Define sample schedule and time
    Time time1(9, 0);
    Schedule requestSchedule("CityA", "CityD");

    // Issue a ticket
    ticketSystem.issueTicket(requestSchedule, time1);

    // Verify that a ticket was issued
    LinkedList<Ticket*>& tickets = ticketSystem.getTickets();
    assert(tickets.getSize() == 1);
    Ticket* issuedTicket = tickets[0]->getData();
    assert(issuedTicket->getTrain()->getId() == 1);
    assert(issuedTicket->getSchedule()->getDeparture() == "CityA");
    assert(issuedTicket->getSchedule()->getDestination() == "CityD");
    std::cout << "Test Passed: Issue Ticket" << std::endl;

}
/**
 * @brief Test function for deserializing train data
 */
void testDeserializeTrain() {
    TicketSystem ticketSystem;
    try{
        ticketSystem.desirializeTrain(ticketSystem, "testtrain.txt");
    }catch(const char*){
        std::cout<<"File cannot be opened. Aborting testDeserializeTrain\n";
        return;
    }

    assert(ticketSystem.getTrains().getSize() == 1);
    assert(ticketSystem.getTrains()[0]->getData()->getId() == 456);
    assert(ticketSystem.getTrains()[0]->getData()->getName() == "Morning Express");
    assert(ticketSystem.getTrains()[0]->getData()->getType() == "InterCity");
    assert(ticketSystem.getTrains()[0]->getData()->getSchedule()[0]->getData()->getDeparture() == "Vienna");
    assert(ticketSystem.getTrains()[0]->getData()->getSchedule()[0]->getData()->getDestination() == "Prague");
    assert(ticketSystem.getTrains()[0]->getData()->getCoaches()[0]->getData()->getCoachNumber() == 2);
    assert(ticketSystem.getTrains()[0]->getData()->getCoaches()[0]->getData()->getNumSeats() == 40);
    assert(ticketSystem.getTrains()[0]->getData()->getCoaches()[0]->getData()->getSeats()[0].getSeatNumber() == 1);
    assert(ticketSystem.getTrains()[0]->getData()->getCoaches()[0]->getData()->getSeats()[0].booked() == true);
    assert(ticketSystem.getTrains()[0]->getData()->getCoaches()[0]->getData()->getSeats()[2].getSeatNumber() == 3);
    assert(ticketSystem.getTrains()[0]->getData()->getCoaches()[0]->getData()->getSeats()[2].booked() == true);
    assert(ticketSystem.getTrains()[0]->getData()->getCoaches()[0]->getData()->getSeats()[39].getSeatNumber() == 40);
    assert(ticketSystem.getTrains()[0]->getData()->getCoaches()[0]->getData()->getSeats()[39].booked() == false);

    std::cout<<"Train deserialization: all test passed\n";
}

/**
 * @brief Test function for deserializing ticket data
 */
void testDeserializeTicket() {
    TicketSystem ticketSystem;


    try
    {
        ticketSystem.desirializeTrain(ticketSystem, "testtrain.txt");
        ticketSystem.deserializeTicket(ticketSystem, "testticket.txt");
    }catch(const char*){
        std::cout<<"File cannot be found. Aborting testDeserializeTicket\n";
        return;
    }



    assert(ticketSystem.getTickets().getSize() == 1);
    assert(ticketSystem.getTickets()[0]->getData()->getId() == 1);
    assert(ticketSystem.getTickets()[0]->getData()->getDiscount() == 0.7);
    assert(ticketSystem.getTickets()[0]->getData()->getSchedule()->getDeparture() == "Budapest");
    assert(ticketSystem.getTickets()[0]->getData()->getSchedule()->getDestination() == "Vienna");
    assert(ticketSystem.getTickets()[0]->getData()->getTrain()->getId() == 456);
    assert(ticketSystem.getTickets()[0]->getData()->getTrain()->getName() == "Morning Express");
    assert(ticketSystem.getTickets()[0]->getData()->getTrain()->getType() == "InterCity");
    assert(ticketSystem.getTickets()[0]->getData()->getSeat()->getSeatNumber() == 2);

    std::cout<<"Ticket desirialization: all tests passed\n";

}

int main() {

   /* testLinkedList();
    testSeat();
    testCoach();
    testSchedule();
    testTrain();
    testTicket();
    testTime();
    testAddTrain();
    testRemoveTrain();*/
    testIssueTicket();/*
    testDeserializeTrain();
    testDeserializeTicket();*/

    TicketSystem ticketSystem;

    std::cout << "\n";

    // Main loop to display and handle the menu
    bool exitFlag = false;

    ticketSystem.desirializeTrain(ticketSystem, "train.txt");
    ticketSystem.deserializeTicket(ticketSystem, "ticket.txt");
    while (!exitFlag) {
        displayMenu();
        handleUserInput(ticketSystem, exitFlag);
    }
    return 0;
}
