#include "ticketSystem.h"
#include <iostream>
#include <limits>

// Function declarations
void displayMenu();
void handleUserInput(TicketSystem &ticketSystem, bool &exitFlag);
int getChoice();
void addTrain(TicketSystem &ticketSystem);
void searchTrain(TicketSystem &ticketSystem);
void removeTrain(TicketSystem &ticketSystem);

void displayMenu() {
    std::cout << "Main Menu:\n";
    std::cout << "1. Tickets\n";
    std::cout << "2. Trains\n";
    std::cout << "3. Schedules\n";
    std::cout << "4. Exit\n";
}

void displayTrainsMenu(){
    std::cout<<"1. Add Train\n";
    std::cout<<"2. Search Train\n";
    std::cout<<"3. Remove Train\n";
}

void displayTrainsSubMenu(){
    std::cout<<"1. Add Coach\n";
    std::cout<<"2. Remove Coach\n";
    std::cout<<"3. Add Schedule\n";
    std::cout<<"4. Remove Schedule\n";
}

void handleUserInput(TicketSystem &ticketSystem, bool &exitFlag) {
    std::cout << "Enter your choice: ";
    int choice = getChoice();

    switch (choice) {
        case 1: {

            break;
        }
        //Kész
        case 2: {
            displayTrainsMenu();
            std::cout << "Enter your choice: ";
            int choice = getChoice();

            switch(choice){
                case 1:{
                    addTrain(ticketSystem);
                    break;}

                case 2:{
                    searchTrain(ticketSystem);
                    break;
                }
                case 3:
                    removeTrain(ticketSystem);
                    break;
            }
            break;
        }
        case 3: {

            break;
        }
        case 4: {
            exitFlag = true;

            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}


int getChoice() {
    int choice;
    while (true) {
        std::cin >> choice;

        if (std::cin.fail()) {
            // Clear the error flag on cin
            std::cin.clear();
            // Ignore the rest of the input until a newline is found
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number.\n";
        } else {
            // Ignore the rest of the input until a newline is found (to prevent issues with leftover characters)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

void addTrain(TicketSystem &ticketSystem){
    std::string name, type;
    std::cout << "Enter train's name: ";
    std::getline(std::cin, name);
    std::cout << "Enter train's type: ";
    std::getline(std::cin, type);
    int trainId = ticketSystem.getTrains().getSize() + 1;
    Train* train = new Train(trainId, name, type);
    ticketSystem.addTrain(*train);
    std::cout << "Train added with ID: " << trainId << std::endl;
}

void searchTrain(TicketSystem &ticketSystem){
    int choice;
    std::cout<<"Enter train's id:\n";
    int id = getChoice();

    Train *searchedTrain = ticketSystem.searchTrain(id);

    if(searchedTrain == nullptr){
        return;
    }

    displayTrainsSubMenu();

    choice = getChoice();

    switch(choice){
        case 1:{
            int coachNumber, numSeats;
            std::cout<<"Enter coach's number:\n";
            coachNumber = getChoice();

            std::cout<<"Enter the number of seats the coach has:\n";
            numSeats = getChoice();

            Coach *coach = new Coach(coachNumber, numSeats);

            searchedTrain->addCoach(*coach);
            break;
        }
        case 2:{
            std::cout<<"Enter coach number:\n";
            int coachNumber = getChoice();

            for(size_t i = 0; i < searchedTrain->getCoaches().getSize(); i++){
                if(searchedTrain->getCoaches()[i]->getData()->getCoachNumber() == coachNumber){
                    Coach *coach = searchedTrain->getCoaches()[i]->getData();
                    searchedTrain->removeCoach(*coach);
                    delete coach;
                }
            }
            break;
        }

        case 3:{
            std::string departure, destination;
            Time departureTime, arrivalTime;

            std::cout<<"Enter Departure:\n";
            std::getline(std::cin, departure);
            std::cout<<"Enter Destination:\n";
            std::getline(std::cin, destination);

            std::cout<<"Enter departure time (h m)\n";
            cin>>departureTime;

            std::cout<<"Enter arrival time (h m)\n";
            cin>>arrivalTime;

            Schedule *schedule = new Schedule(departure, destination, arrivalTime, departureTime);

            searchedTrain->addSchedule(*schedule);
            break;
        }

        case 4:{
            std::string departure, destination;

            std::cout<<"Enter train's departure:\n";
            std::getline(std::cin, departure);
            std::cout<<"Enter train's destination\n";
            std::getline(std::cin, destination);

            Node<Schedule*> *scheduleNode = searchedTrain->getSchedule().begin();
            while (scheduleNode != nullptr) {

                if(scheduleNode->getData()->getDeparture() == departure && scheduleNode->getData()->getDestination() == destination){
                    Schedule *curr = scheduleNode->getData();
                    searchedTrain->removeSchedule(*curr);
                    break;
                }
                scheduleNode = scheduleNode->getNext();
            }
            delete scheduleNode;
            break;
        }


    }
}

void removeTrain(TicketSystem &ticketSystem){
    std::cout<<"Enter train's id:\n";
    int id = getChoice();

    Train *searchedTrain = ticketSystem.searchTrain(id);

    if(searchedTrain == nullptr){
        return;
    }

    ticketSystem.removeTrain(searchedTrain->getId());
    std::cout<<"Train has been removed\n";
}

void listSchedule(TicketSystem &ticketSystem){

}