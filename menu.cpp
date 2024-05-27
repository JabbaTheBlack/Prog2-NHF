#include "ticketSystem.h"
#include "menu.h"
#include <iostream>
#include <limits>

// Function declarations
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
void displayTicketsMenu(){
    std::cout<<"1. Issue Ticket\n";
    std::cout<<"2. Delete Ticket\n";
}

void handleUserInput(TicketSystem &ticketSystem, bool &exitFlag) {
    std::cout << "Enter your choice: ";
    int choice = getChoice();

    switch (choice) {
        case 1: {
            displayTicketsMenu();
            std::cout<<"Enter your choice:\n";
            int choice = getChoice();

            switch(choice){
                case 1:{
                    double discount;
                    std::string departure, destination;
                    Time currentTime;
                    std::cout << "Enter departure station:\n";
                    std::getline(std::cin, departure);
                    std::cout << "Enter destination station:\n";
                    std::getline(std::cin, destination);
                    std::cout << "Enter time: (h m)\n";
                    std::cin >> currentTime;
                    std::cout << "Enter applicable discount in % (e.g. 30):\n";
                    std::cin >> discount;
                    std::cin.ignore();

                    Schedule schedule(departure, destination);
                    ticketSystem.issueTicket(schedule, currentTime, discount / 100);

                    break;
                }
                case 2:{
                    int id;
                    std::cout<<"Enter ticket's id:\n";
                    cin>>id;
                    ticketSystem.removeTicket(id);
                    std::cout<<"Ticket has been removed\n\n";

                    break;
                }
            }
            break;
        }
        case 2: {
            displayTrainsMenu();
            std::cout << "Enter your choice:\n";
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
            std::string station;
            std::cout<<"Station's name:\n";
            std::getline(std::cin, station);

            LinkedList<Train*> stationTrains;
            Node<Train*> *trainNode = ticketSystem.getTrains().begin();

            while (trainNode != nullptr) {
                Train* train = trainNode->getData();

                Node<Schedule*> *scheduleNode = train->getSchedule().begin();
                while (scheduleNode != nullptr) {
                    Schedule* schedule = scheduleNode->getData();
                    if (schedule->getDeparture() == station || schedule->getDestination() == station) {
                        stationTrains.insert(train);
                        break;
                    }
                    scheduleNode = scheduleNode->getNext();
                }

                trainNode = trainNode->getNext();
            }

            std::cout<<std::endl;
            Node<Train*> *stationTrainNode = stationTrains.begin();
            while (stationTrainNode != nullptr) {
                Train* train = stationTrainNode->getData();
                std::cout << *train << std::endl<<std::endl;
                stationTrainNode = stationTrainNode->getNext();
            }

            break;
        }
        case 4: {
           /* std::ofstream train("train.txt");
            train.close();
            Node<Train*> *trainNode = ticketSystem.getTrains().begin();
            while(trainNode != nullptr){

                trainNode->getData()->serialize("train.txt");
                trainNode = trainNode->getNext();
            }

            std::ofstream ticket("ticket.txt");
            ticket.close();
            Node<Ticket*> *ticketNode = ticketSystem.getTickets().begin();
            while(ticketNode != nullptr){

                ticketNode->getData()->serialize("ticket.txt");
                ticketNode = ticketNode->getNext();
            }*/
            exitFlag = true;
            std::cout << "Exiting program..." << std::endl;
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
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number.\n";
        } else {
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