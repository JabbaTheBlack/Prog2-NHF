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
        delete ticket;
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
void TicketSystem::issueTicket(Schedule &schedule, const Time &time, const double discount){
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
                Node<Schedule*> *destinationScheduleNode = currentScheduleNode;
                Time departureTime = currentSchedule->getDepartureTime();

                while (destinationScheduleNode != nullptr) {
                    Schedule *destinationSchedule = destinationScheduleNode->getData();

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


    if (bestTrain != nullptr) {
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
                    bestSchedule->setLatency(0);

                    //Schedule *schedule = new Schedule(bestSchedule.getDeparture(), bestSchedule.getDestination(), bestSchedule.getArrivalTime(), bestSchedule.getDepartureTime());
                    Ticket *newTicket = new Ticket(static_cast<int>(tickets.getSize() + 1), bestSchedule, bestTrain, coach.getData(), availableSeat, discount);

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


/**
 * @brief Deserializes train data from a file.
 *
 * This method reads train data from a file named "train.txt" and populates the train list in the system.
 * It expects the file to be formatted with train details followed by their schedules and coaches.
 */

void TicketSystem::desirializeTrain(TicketSystem &ticketSystem, const std::string &filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw "Failed to open file";
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "Train:") {
            int trainId = 0;
            std::string trainName = "";
            std::string trainType = "";
            bool isFull = false;

            file >> trainId;
            file.ignore();
            std::getline(file, trainName);
            std::getline(file, trainType);
            file >> isFull;
            file.ignore();

            Train *train = new Train(trainId, trainName, trainType, isFull);


            std::getline(file, line);

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
                ss.ignore(1);
                ss >> minutes;
                departureTime = Time(hours, minutes);

                std::getline(file, line);
                std::stringstream ss2(line);
                ss2 >> hours;
                ss2.ignore(1);
                ss2 >> minutes;
                arrivalTime = Time(hours, minutes);

                Schedule *schedule1 = new Schedule(departure, destination, arrivalTime, departureTime);
                train->addSchedule(*schedule1);

                std::getline(file, line);
            }


            while (std::getline(file, line) && line != "Seats:") {
                if (line.empty()) continue;

                int coachNumber = std::stoi(line);
                int numSeats;
                file >> numSeats;
                file.ignore();

                Coach *coach = new Coach(coachNumber, numSeats);


                std::getline(file, line);
                std::getline(file, line);
                for (int i = 0; i < numSeats; ++i) {
                    int seatNumber = 0, booked = 0;
                    file >> seatNumber >> booked;
                    if (booked == 1) {
                        coach->getSeats()[seatNumber - 1].bookSeat();
                    }
                }

                train->addCoach(*coach);

                std::getline(file, line);
            }
            ticketSystem.addTrain(*train);
        }
    }

    file.close();
}


/**
 * @brief Deserializes ticket data from a file.
 *
 * This method reads ticket data from a file named "ticket.txt" and populates the ticket list in the system.
 * It expects the file to be formatted with ticket details followed by their associated schedules, trains, coaches, and seats.
 */
void TicketSystem::deserializeTicket(TicketSystem &ticketSystem, const std::string &filename){
    std::ifstream infile(filename);

    if (infile.is_open()) {
        std::string line, departure, destination, trainName, trainType;
        int id = 0, trainId = 0, coachNumber = 0, seatNumber = 0, hours = 0, minutes = 0, count = 1;
        double discount = 0;
        Time arrivalTime, departureTime;

        while (std::getline(infile, line)) {
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
                    ss.ignore(1);
                    ss >> minutes;
                    departureTime.setHours(hours);
                    departureTime.setMinutes(minutes);
                    break;

                case 5:
                    ss >> hours;
                    ss.ignore(1);
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

                Train *train = searchTrain(trainId);
                if (train == nullptr) {
                    throw "Searching for train was unsuccessful\n";
                }

                Coach *coach = nullptr;
                for (size_t i = 0; i < train->getCoaches().getSize(); i++) {
                    if (train->getCoaches()[i]->getData()->getCoachNumber() == coachNumber) {
                        coach = train->getCoaches()[i]->getData();
                        break;
                    }
                }

                if (coach == nullptr) {
                    coach = new Coach(coachNumber);
                    train->addCoach(*coach);
                }
                Schedule *newSchedule = new Schedule(departure, destination, arrivalTime, departureTime);
                train->addSchedule(*newSchedule);

                Seat *seat = &coach->getSeats()[seatNumber - 1];
                seat->bookSeat();

                Ticket *newTicket = new Ticket(id, newSchedule, train, coach, seat, discount);

                tickets.insert(newTicket);

                count = 1;
            } else {
                count++;
            }
        }

        infile.close();
    } else {
        throw "File cannot be opened";
    }
}