#include <fstream>
#include "ticket.h"
#include "memtrace.h"

int Ticket::getId() const{
    return id;
}

Seat* Ticket::getSeat() const{
    return seat;
}

Coach* Ticket::getCoach() const{
    return coach;
}

Train* Ticket::getTrain() const{
    return train;
}

Schedule* Ticket::getSchedule() const{
    return schedule;
}

double Ticket::getDiscount() const{
    return discount;
}

void Ticket::setDiscount(double discount){
    this->discount = discount;
}

void Ticket::setTrain(Train *train){
    this->train = train;
}

void Ticket::setCoach(Coach *coach){
    this->coach = coach;
}

void Ticket::setSeat(Seat *seat){
    this->seat = seat;
}

std::ostream& operator<<(std::ostream &os, const Ticket &ticket){
    os << "Id: " << ticket.getId();

    if (ticket.getTrain() != nullptr)
        os << "\nTrain id: " << ticket.getTrain()->getId();
    else
        os << "\nTrain: (null)";

    if (ticket.getCoach() != nullptr)
        os << "\nCoach number: " << ticket.getCoach()->getCoachNumber();
    else
        os << "\nCoach: (null)";

    if (ticket.getSeat() != nullptr)
        os << "\nSeat number: " << ticket.getSeat()->getSeatNumber();
    else
        os << "\nSeat: (null)";

    if (ticket.getDiscount() > 0){
        os << "\nDiscount: " << (100 - ticket.getDiscount() * 100)<<"%";
    }

    return os;
}

void Ticket::serializeTicket() {
    std::ofstream outfile("ticket.txt", std::ios::app); // Open file for writing

    if (outfile.is_open() && !outfile.eof()) {
        outfile << id << std::endl; // Ticket ID

        // Write schedule information if available
        if (schedule != nullptr) {
            outfile << schedule->getDeparture() << std::endl // Departure
                    << schedule->getDestination() << std::endl // Destination
                    << schedule->getDepartureTime().getHours() << ":" << schedule->getDepartureTime().getMinutes() << std::endl // Departure Time
                    << schedule->getArrivalTime().getHours() << ":" << schedule->getArrivalTime().getMinutes() << std::endl; // Arrival Time
        }

        // Write train information if available
        if (train != nullptr) {
            outfile << train->getId() << std::endl // Train ID
                    << train->getName() << std::endl // Train Name
                    << train->getType() << std::endl; // Train Type
        }

        // Write coach information if available
        if (coach != nullptr) {
            outfile << coach->getCoachNumber() << std::endl; // Coach Number
        }

        // Write seat information if available
        if (seat != nullptr) {
            outfile << seat->getSeatNumber() << std::endl; // Seat Number
        }

        // Write discount
        outfile << discount << std::endl << std::endl;
    } else {
        std::cout << "File cannot be opened" << std::endl;
    }

    outfile.close();
}