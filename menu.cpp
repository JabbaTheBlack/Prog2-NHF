#include <limits>
#include "menu.h"

void TicketsMenu::displayMenu() {
    std::cout << "Tickets Menu:\n";
    std::cout << "1. Issue Ticket\n";
    std::cout << "2. Remove Ticket\n";
    std::cout << "3. Exit to Main Menu\n";
}

void TicketsMenu::handleUserInput() {
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1: {
            std::string departure, destination;
            int hours, minutes;
            std::cout << "Enter departure station: ";
            std::getline(std::cin, departure);

            std::cout << "Enter destination station: ";
            std::getline(std::cin, destination);

            std::cout << "Please enter departure time (hour minute): ";
            std::cin >> hours >> minutes;

            Time departureTime(hours, minutes);
            Schedule schedule(departure, destination);

            ticketSystem.issueTicket(schedule, departureTime);
            break;
        }
        case 2: {
            int id;
            std::cout << "Enter ticket's id: \n";
            cin>>id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            ticketSystem.removeTicket(id);

            std::cout << "Ticket has been deleted\n";
            break;
        }
        case 3:
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            break;
    }
}


void TicketsMenu::executeAction() {
    // Execute action for Tickets Menu
}

void TrainsMenu::displayMenu() {
    std::cout << "Trains Menu:\n";
    std::cout << "1. Add Train\n";
    std::cout << "2. Search Train\n";
    std::cout << "3. Remove Train\n";
}

void TrainsMenu::handleUserInput() {
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore();

    switch(choice){
        case 1: {
            string name, type;
            std::cout<<"Enter train's name: \n";
            std::getline(std::cin, name);

            std::cout<<"Enter train's type: \n";
            std::getline(std::cin, type);

            Train train(ticketSystem.getTrains().getSize() + 1, name ,type);
            ticketSystem.addTrain(train);

            std::cout<<"Train's id: "<<ticketSystem.getTrains().getSize()<<std::endl;
            break;
        }
        case 2: {
            int id;
            std::cout << "Enter train's id:\n";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            Train *searchedTrain = ticketSystem.searchTrain(id);

            if (searchedTrain != nullptr) {
                int subChoice;
                std::cout << "(1) Add schedule\n";
                std::cout << "(2) Remove schedule\n";
                std::cout << "(3) Add Carriage\n";
                std::cout << "(4) Remove Carriage\n";
                std::cout << "Enter your choice: ";
                std::cin >> subChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                switch (subChoice) {
                    case 1: {
                        std::string departure, destination;
                        int depHour, depMinute, arrHour, arrMinute;

                        std::cout << "Enter departure station: ";
                        std::getline(std::cin, departure);

                        std::cout << "Enter destination station: ";
                        std::getline(std::cin, destination);

                        std::cout << "Enter departure time (hour minute): ";
                        std::cin >> depHour >> depMinute;

                        std::cout << "Enter arrival time (hour minute): ";
                        std::cin >> arrHour >> arrMinute;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        Time departureTime(depHour, depMinute);
                        Time arrivalTime(arrHour, arrMinute);
                        Schedule newSchedule(departure, destination, departureTime, arrivalTime);

                        searchedTrain->addSchedule(newSchedule);
                        std::cout << "Schedule added successfully\n";
                        break;
                    }
                    case 2: {
                        std::string departure;
                        int depHour, depMinute;

                        std::cout << "Enter departure station of schedule to remove: ";
                        std::getline(std::cin, departure);

                        std::cout << "Enter departure time of schedule to remove (hour minute): ";
                        std::cin >> depHour >> depMinute;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        Time departureTime(depHour, depMinute);
                        Schedule* scheduleToRemove = nullptr;

                        for (auto& schedule : searchedTrain->getSchedule()) {
                            if (schedule.getData()->getDeparture() == departure &&
                                schedule.getData()->getDepartureTime() == departureTime) {
                                scheduleToRemove = schedule.getData();
                                break;
                            }
                        }

                        if (scheduleToRemove) {
                            searchedTrain->removeSchedule(*scheduleToRemove);
                            std::cout << "Schedule removed successfully\n";
                        } else {
                            std::cout << "Schedule not found\n";
                        }
                        break;
                    }
                    case 3: {
                        int coachNumber, seatCount;

                        std::cout << "Enter coach number: ";
                        std::cin >> coachNumber;

                        std::cout << "Enter number of seats: ";
                        std::cin >> seatCount;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        Coach newCoach(coachNumber, seatCount);
                        searchedTrain->addCoach(newCoach);
                        std::cout << "Coach added successfully\n";
                        break;
                    }
                    case 4: {
                        int coachNumber;

                        std::cout << "Enter coach number to remove: ";
                        std::cin >> coachNumber;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        Coach* coachToRemove = nullptr;
                        for (auto& coach : searchedTrain->getCoaches()) {
                            if (coach.getData()->getCoachNumber() == coachNumber) {
                                coachToRemove = coach.getData();
                                break;
                            }
                        }

                        if (coachToRemove) {
                            searchedTrain->removeCoach(*coachToRemove);
                            std::cout << "Coach removed successfully\n";
                        } else {
                            std::cout << "Coach not found\n";
                        }
                        break;
                    }
                    default:
                        std::cout << "Invalid choice. Please enter a valid number.\n";
                        break;
                }
            } else {
                std::cout << "Train not found" << std::endl;
            }
            break;
        }
        case 3:
            int id;
            std::cout<<"Enter train's id:\n";
            std::cin>>id;

            ticketSystem.removeTrain(id);
            std::cout<<"Train has been removed\n";
            break;
    }

}

void TrainsMenu::executeAction() {
    // Execute action for Trains Menu
}

void ScheduleMenu::displayMenu() {
    std::cout << "Schedule Menu:\n";
    std::cout << "Search Train Schedule\n";
}

void ScheduleMenu::handleUserInput() {
    std::string station;
    std::cout << "Enter station's name:\n";
    std::getline(std::cin, station);
    std::cin.ignore();

    LinkedList<int> incomingTrains;
    LinkedList<int> outgoingTrains;

    auto contains = [](const LinkedList<int>& list, int id) {
        for (Node<int>* node = list.begin(); node != nullptr; node = node->getNext()) {
            if (node->getData() == id) {
                return true;
            }
        }
        return false;
    };

    // Iterate through all trains
    for (Node<Train*>* trainNode = ticketSystem.getTrains().begin(); trainNode != nullptr; trainNode = trainNode->getNext()) {
        Train* train = trainNode->getData();

        // Iterate through all schedules of the current train
        for (Node<Schedule*>* scheduleNode = train->getSchedule().begin(); scheduleNode != nullptr; scheduleNode = scheduleNode->getNext()) {
            Schedule* schedule = scheduleNode->getData();

            // Check for outgoing trains
            if (schedule->getDeparture() == station && !contains(outgoingTrains, train->getId())) {
                outgoingTrains.insert(train->getId());
            }

            // Check for incoming trains
            if (schedule->getDestination() == station && !contains(incomingTrains, train->getId())) {
                incomingTrains.insert(train->getId());
            }
        }
    }

    // Print outgoing trains
    std::cout << "Outgoing trains from " << station << ":\n";
    for (Node<int>* node = outgoingTrains.begin(); node != nullptr; node = node->getNext()) {
        std::cout << "Train ID: " << node->getData() << std::endl;
    }

    // Print incoming trains
    std::cout << "Incoming trains to " << station << ":\n";
    for (Node<int>* node = incomingTrains.begin(); node != nullptr; node = node->getNext()) {
        std::cout << "Train ID: " << node->getData() << std::endl;
    }

}

void ScheduleMenu::executeAction() {
    // Execute action for Schedule Menu
}

void ExitMenu::displayMenu() {
    std::cout << "Exiting...\n";
}

void ExitMenu::handleUserInput() {

    for(size_t i = 0; i < ticketSystem.getTickets().getSize(); i++){
       ticketSystem.getTickets()[i]->getData()->serializeTicket();
    }

    for(size_t i = 0; i < ticketSystem.getTrains().getSize(); i++){
        ticketSystem.getTrains()[i]->getData()->serializeTrain("train.txt");
    }

    std::exit(0);
}

void ExitMenu::executeAction() {
    // Execute action for Exit Menu
}

void MainMenu::addSubMenu(Menu* subMenu, int index) {
    if (index >= 0 && index < 4) {
        subMenus[index] = subMenu;
    }
}

void MainMenu::displayMenu() {
    std::cout << "Main Menu:\n";
    for (int i = 0; i < 4; ++i) {
        if (subMenus[i] != nullptr) {
            std::cout << (i + 1) << ". " << subMenus[i]->getTitle() << std::endl;
        }
    }
}

void MainMenu::handleUserInput() {

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choice >= 1 && choice <= 4 && subMenus[choice - 1] != nullptr) {
        subMenus[choice - 1]->displayMenu();
        subMenus[choice - 1]->handleUserInput();
        subMenus[choice - 1]->executeAction();
    } else {
        std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
    }
}

void MainMenu::executeAction() {
    // No action for main menu, just navigate to submenus
}
