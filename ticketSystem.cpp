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

/*
void TicketSystem::issueTicket(Schedule &schedule, Time &time){
    Train *bestTrain = nullptr;
    Schedule *bestDepartureSchedule = nullptr;
    Time bestDepartureTime;
    Time bestDestinationTime;

    Node<Train*> *currentTrainNode = trains.begin();

    while (currentTrainNode != trains.end()) {
        Train *train = currentTrainNode->getData();
        Node<Schedule*> *currentScheduleNode = train->getSchedule().begin();

        while (currentScheduleNode != nullptr) {
            Schedule *currentSchedule = currentScheduleNode->getData();

            // Check if departure matches and the departure time is >= purchase time
            if ((currentSchedule->getDeparture() == schedule.getDeparture()) && (currentSchedule->getDepartureTime() >= time)) {
                Node<Schedule*> *destinationScheduleNode = currentScheduleNode;

                while (destinationScheduleNode != nullptr) {
                    Schedule *destinationSchedule = destinationScheduleNode->getData();

                    // Check if the destination matches
                    if (destinationSchedule->getDestination() == schedule.getDestination()) {
                        Time departureTime = currentSchedule->getDepartureTime();
                        Time destinationTime = destinationSchedule->getArrivalTime();

                        // Check for the best schedule based on departure and destination times
                        if (bestDepartureSchedule == nullptr ||
                            (departureTime < bestDepartureTime ||
                             (departureTime == bestDepartureTime && destinationTime < bestDestinationTime))) {
                            bestTrain = train;
                            bestDepartureSchedule = currentSchedule;
                            bestDepartureTime = departureTime;
                            bestDestinationTime = destinationTime;
                        }
                    }
                    destinationScheduleNode = destinationScheduleNode->getNext();
                }
            }
            currentScheduleNode = currentScheduleNode->getNext();
        }
        currentTrainNode = currentTrainNode->getNext();
    }


}
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


                    bestSchedule->setDepartureTime(bestDepartureTime);
                    bestSchedule->setArrivalTime(bestDestinationTime);
                    // Create a ticket
                    Ticket *newTicket = new Ticket(static_cast<int>(tickets.getSize() + 1), bestSchedule, bestTrain, coach.getData(), availableSeat);

                    // Add ticket to the system's ticket list
                    tickets.insert(newTicket);

                    std::cout << "Ticket issued successfully for train " << bestTrain->getId() <<
                              " departing at " << bestDepartureTime
                              <<" Ticket id: "<<newTicket->getId()<<std::endl;

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

void TicketSystem::desirializeTrain(){

}


/**
 * @brief Deserializes ticket data from a file.
 *
 * This method reads ticket data from a file named "ticket.txt" and populates the ticket list in the system.
 * It expects the file to be formatted with ticket details followed by their associated schedules, trains, coaches, and seats.
 */

void TicketSystem::deserializeTicket() {
}