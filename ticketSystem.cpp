#include <fstream>
#include <sstream>
#include <limits>
#include "ticketSystem.h"
#include "memtrace.h"

void TicketSystem::addTrain(Train &train){
    trains.insert(&train);
}

void TicketSystem::removeTrain(int trainId){
    for(size_t i = 0;  i < trains.getSize(); i++){
        Train *curr = trains[i]->getData();

        if(curr->getId() == trainId){
            trains.remove(curr);
            delete curr;
        }
    }
}

void TicketSystem::removeTicket(int ticketId){
    for(size_t i = 0; i < tickets.getSize(); i++){
        Ticket *ticket = tickets[i]->getData();

        if(ticket->getId() == ticketId){
            tickets.remove(ticket);
        }
    }
}


/**
 * @brief Issues a ticket for a specific schedule and time.
 *
 * This method searches for the best available train and schedule that matches the given departure and destination
 * and issues a ticket if a suitable train and seat are found.
 *
 * @param schedule Reference to the schedule containing departure and destination information.
 * @param time Reference to the time of ticket purchase.
 */
void TicketSystem::issueTicket(Schedule &schedule, const Time &time){
    Train *bestTrain = nullptr;
    Time bestDepartureTime;
    Time bestDestinationTime;
    Schedule *bestSchedule = &schedule;


    Node<Train*> *currentTrainNode = trains.begin();

    while(currentTrainNode != nullptr){
        Train *train = currentTrainNode->getData();
        Node<Schedule*> *currentScheduleNode = train->getSchedule().begin();

        while(currentScheduleNode != nullptr){
            Schedule *currentSchedule = currentScheduleNode->getData();

            if(currentSchedule->getDeparture() == schedule.getDeparture() && (currentSchedule->getDepartureTime() >= time)){
                Node<Schedule*> *destinationScheduleNode = currentScheduleNode->getNext();
                Time departureTime = currentSchedule->getDepartureTime();

                while (destinationScheduleNode != nullptr) {
                    Schedule *destinationSchedule = destinationScheduleNode->getData();

                    // Check if the destination matches
                    if (destinationSchedule->getDestination() == schedule.getDestination()) {
                        Time destinationTime = destinationSchedule->getArrivalTime();

                        if(bestDepartureTime.getHours() == 0 && bestDepartureTime.getMinutes() == 0){
                            bestDepartureTime = departureTime;
                            bestDestinationTime = destinationTime;
                            bestTrain = train;
                        }else if(bestDepartureTime < departureTime){
                            bestDepartureTime = departureTime;
                            bestDestinationTime = destinationTime;
                            bestTrain = train;
                        }
                    }
                    destinationScheduleNode = destinationScheduleNode->getNext();
                }
            }
            currentScheduleNode = currentScheduleNode->getNext();
        }
        currentTrainNode = currentTrainNode->getNext();
    }
    delete currentTrainNode;


    if (bestTrain != nullptr) {
        // Look for a seat with the same ticket type in any coach
        bool foundSeat = false;
        for (auto &coach : bestTrain->getCoaches()) {
            for (size_t seatIndex = 0; seatIndex < static_cast<size_t>(coach.getData()->size()); seatIndex++) {
                Seat* currentSeat = &coach.getData()->getSeats()[seatIndex];
                if (!currentSeat->booked()) {
                    foundSeat = true;
                    Seat* availableSeat = currentSeat;

                    coach.getData()->getSeats()[availableSeat->getSeatNumber() - 1].bookSeat();
                    bestSchedule->setDepartureTime(bestDepartureTime);
                    bestSchedule->setArrivalTime(bestDestinationTime);
                    // Create a ticket
                    Ticket *newTicket = new Ticket(static_cast<int>(tickets.getSize() + 1), bestSchedule, bestTrain, coach.getData(), availableSeat);

                    // Add ticket to the system's ticket list
                    tickets.insert(newTicket);

                    std::cout << "Ticket issued successfully for train " << bestTrain->getId() <<
                              " departing at " << bestDepartureTime
                              <<" Ticket id: "<<newTicket->getId()<<std::endl;


                    int max = coach.getData()->getNumSeats();
                    if(coach.getData()->getSeats()[max].booked()){
                        coach.getData()->booked();
                    }
                    return;
                }
            }
        }

        if (!foundSeat) {
            std::cout << "No seat available with the required ticket type on the chosen trains for the desired route." << std::endl;
        }
    } else {
        std::cout << "No train found with a matching or upcoming schedule for the provided departure and destination." << std::endl;
    }
}

LinkedList<Train*>& TicketSystem::getTrains(){
    return trains;
}

LinkedList<Ticket*>& TicketSystem::getTickets(){
    return tickets;
}

Train* TicketSystem::searchTrain(int id) {
    Node<Train *> *current = trains.begin();
    while (current != nullptr) {
        if (current->getData()->getId() == id) {
            std::cout << "Train found: " << current->getData()->getId() << std::endl;
            return current->getData();
        }
        current = current->getNext();
    }
    std::cout << "Train with ID " << id << " not found." << std::endl;
    return nullptr;
}

void TicketSystem::desirializeTrain(TicketSystem &ticketSystem, const std::string &filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "Train:") {
            int trainId = 0;
            std::string trainName = "";
            std::string trainType = "";
            bool isFull = false;

            // Read train details
            file >> trainId;
            file.ignore(); // Ignore the newline
            std::getline(file, trainName);
            std::getline(file, trainType);
            file >> isFull;
            file.ignore(); // Ignore the newline

            Train *train = new Train(trainId, trainName, trainType, isFull);


            // Skip the blank line
            std::getline(file, line);

            // Read schedules
            while (std::getline(file, line) && line != "Coaches:") {
                if (line.empty()) continue;

                std::string departure = "";
                std::string destination = "";
                Time departureTime, arrivalTime;

                departure = line;
                std::getline(file, departure);
                std::getline(file, destination);

                std::getline(file, line);
                std::stringstream ss(line);
                int hours, minutes;
                ss >> hours;
                ss.ignore(1); // Skip colon (':')
                ss >> minutes;
                departureTime = Time(hours, minutes);

                std::getline(file, line);
                std::stringstream ss2(line);
                ss2 >> hours;
                ss2.ignore(1); // Skip colon (':')
                ss2 >> minutes;
                arrivalTime = Time(hours, minutes);

                Schedule *schedule1 = new Schedule(departure, destination, arrivalTime, departureTime);
                train->addSchedule(*schedule1);
                // Skip the blank line
                std::getline(file, line);
            }

            // Read coaches
            while (std::getline(file, line) && line != "Seats:") {
                if (line.empty()) continue;

                int coachNumber = std::stoi(line);
                int numSeats;
                file >> numSeats;
                file.ignore(); // Ignore the newline

                Coach *coach = new Coach(coachNumber, numSeats);

                // Read seats
                std::getline(file, line);
                std::getline(file, line); // Skip the empty line
                for (int i = 0; i < numSeats; ++i) {
                    int seatNumber = 0, booked = 0;
                    file >> seatNumber >> booked;
                    if (booked == 1) {
                        coach->getSeats()[seatNumber - 1].bookSeat();
                    }
                }

                train->addCoach(*coach);
                // Skip the blank line
                std::getline(file, line);
            }
            ticketSystem.addTrain(*train);
        }
    }

    file.close();
}



void TicketSystem::deserializeTicket(TicketSystem &ticketSystem, const std::string &filename){
    std::ifstream infile(filename);

    if (infile.is_open()) {
        std::string line, departure, destination, trainName, trainType;
        int id = 0, trainId = 0, coachNumber = 0, seatNumber = 0, hours = 0, minutes = 0, count = 1;
        double discount = 0;
        Time arrivalTime, departureTime;

        while (std::getline(infile, line)) {
            // Skip empty lines
            if (line.empty()) {
                continue;
            }

            std::stringstream ss(line);

            switch (count) {
                case 1:
                    ss >> id;
                    break;

                case 2:
                    departure = line;
                    break;

                case 3:
                    destination = line;
                    break;

                case 4:
                    ss >> hours;
                    ss.ignore(1); // Skip colon (':')
                    ss >> minutes;
                    departureTime.setHours(hours);
                    departureTime.setMinutes(minutes);
                    break;

                case 5:
                    ss >> hours;
                    ss.ignore(1); // Skip colon (':')
                    ss >> minutes;
                    arrivalTime.setHours(hours);
                    arrivalTime.setMinutes(minutes);
                    break;

                case 6:
                    ss >> trainId;
                    break;

                case 7:
                    trainName = line;
                    break;

                case 8:
                    trainType = line;
                    break;

                case 9:
                    ss >> coachNumber;
                    break;

                case 10:
                    ss >> seatNumber;
                    break;

                case 11:
                    ss >> discount;
                    break;
            }

            if (count == 11) {

                // Search for the train
                Train *train = searchTrain(trainId);
                if (train == nullptr) {
                    throw "Searching for train was unsuccessful\n";
                }

                // Search for the coach
                Coach *coach = nullptr;
                for (size_t i = 0; i < train->getCoaches().getSize(); i++) {
                    if (train->getCoaches()[i]->getData()->getCoachNumber() == coachNumber) {
                        coach = train->getCoaches()[i]->getData();
                        break;
                    }
                }

                // Create a new coach if not found
                if (coach == nullptr) {
                    coach = new Coach(coachNumber);
                    train->addCoach(*coach);
                }
                Schedule *newSchedule = new Schedule(departure, destination, arrivalTime, departureTime);
                train->addSchedule(*newSchedule);
                // Create the seat
                Seat *seat = &coach->getSeats()[seatNumber - 1];
                seat->bookSeat(); // Mark the seat as booked
                // Create the new ticket
                Ticket *newTicket = new Ticket(id, newSchedule, train, coach, seat, discount);

                // Add the ticket to the system's ticket list
                tickets.insert(newTicket);

                // Reset count to start reading the next ticket
                count = 1;
            } else {
                count++;
            }
        }

        infile.close();
    } else {
        std::cout << "File cannot be opened" << std::endl;
    }
}






























/**
 * @brief Deserializes train data from a file.
 *
 * This method reads train data from a file named "train.txt" and populates the train list in the system.
 * It expects the file to be formatted with train details followed by their schedules and coaches.
 */
/*
void TicketSystem::desirializeTrain(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "Train:") {
            int trainId = 0;
            std::string trainName = "";
            std::string trainType = "";
            bool isFull = false;

            // Read train details
            file >> trainId;
            file.ignore(); // Ignore the newline
            std::getline(file, trainName);
            std::getline(file, trainType);
            file >> isFull;
            file.ignore(); // Ignore the newline

            Train *train = new Train(trainId, trainName, trainType, isFull);
            addTrain(*train);

            // Skip the blank line
            std::getline(file, line);

            // Read schedules
            while (std::getline(file, line) && line != "Coaches:") {
                if (line.empty()) continue;

                std::string departure = "";
                std::string destination = "";
                Time departureTime, arrivalTime;

                departure = line;
                std::getline(file, departure);
                std::getline(file, destination);

                std::getline(file, line);
                std::stringstream ss(line);
                int hours, minutes;
                ss >> hours;
                ss.ignore(1); // Skip colon (':')
                ss >> minutes;
                departureTime = Time(hours, minutes);

                std::getline(file, line);
                std::stringstream ss2(line);
                ss2 >> hours;
                ss2.ignore(1); // Skip colon (':')
                ss2 >> minutes;
                arrivalTime = Time(hours, minutes);

                Schedule *schedule = new Schedule(departure, destination, departureTime, arrivalTime);
                train->addSchedule(*schedule);

                // Skip the blank line
                std::getline(file, line);
            }

            // Read coaches
            while (std::getline(file, line) && line != "Seats:") {
                if (line.empty()) continue;

                int coachNumber = std::stoi(line);
                int numSeats;
                file >> numSeats;
                file.ignore(); // Ignore the newline

                Coach *coach = new Coach(coachNumber, numSeats);

                // Read seats
                std::getline(file, line); // Skip "Seats:" line
                while (std::getline(file, line) && !line.empty()) {
                    int seatNumber;
                    file >>seatNumber;
                    coach->getSeats()[seatNumber - 1].booked();
                }

                train->addCoach(*coach);
                // Skip the blank line
                std::getline(file, line);
            }
        }
    }

    file.close();
}



*/
/**
 * @brief Deserializes ticket data from a file.
 *
 * This method reads ticket data from a file named "ticket.txt" and populates the ticket list in the system.
 * It expects the file to be formatted with ticket details followed by their associated schedules, trains, coaches, and seats.
 *//*


void TicketSystem::deserializeTicket(const std::string &filename) {
    std::ifstream infile(filename);

    if(infile.is_open()){
        std::string line, departure, destination, trainName, trainType;
        int id = 0, trainId = 0, coachNumber = 0, seatNumber = 0, hours = 0,minutes = 0, count = 1;
        double discount = 0;
        Time arrivalTime, departureTime;


        while (std::getline(infile, line)) {
            // Skip empty lines
            if (line.empty()) {
                continue;
            }

            std::stringstream ss(line);

            switch(count){
                case 1:
                    ss >> id;
                    break;

                case 2:
                    ss >> departure;
                    break;

                case 3:
                    ss >> destination;
                    break;

                case 4:
                    ss >> hours;
                    ss.ignore(1); // Skip colon (':')
                    ss >> minutes;

                    departureTime.setHours(hours);
                    departureTime.setMinutes(minutes);
                    break;

                case 5:
                    ss >> hours;
                    ss.ignore(1); // Skip colon (':')
                    ss >> minutes;
                    arrivalTime.setHours(hours);
                    arrivalTime.setMinutes(minutes);
                    break;

                case 6:
                    ss >> trainId;
                    break;

                case 7:
                    ss >> trainName;
                    break;

                case 8:
                    ss >> trainType;
                    break;

                case 9:
                    ss >> coachNumber;
                    break;

                case 10:
                    ss >> seatNumber;
                    break;

                case 11:
                    ss >> discount;
                    break;

            }

            if(count == 11){
                Schedule *newSchedule = new Schedule(departure, destination, arrivalTime, departureTime);
                Train *train = searchTrain(trainId);
                if(train == nullptr){
                    delete train;
                    delete newSchedule;
                    throw"Seaching for train was unsuccessful\n";
                }
                Coach *coach = train->getCoaches()[coachNumber - 1]->getData();
                Seat *seat = &coach->getSeats()[seatNumber - 1];
                Ticket *newTicket = new Ticket(id, newSchedule, train, coach, seat, discount);
                tickets.insert(newTicket);
                count = 1;
            }
            else{
                count++;
            }
        }

        infile.close();
    } else {
        std::cout << "File cannot be opened" << std::endl;
    }
}
*/
