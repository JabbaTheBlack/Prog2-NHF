#include "schedule.h"
#include "memtrace.h"

string Schedule::getDestination() const{
    return destination;
}

string Schedule::getDeparture() const{
    return departure;
}

Time Schedule::getArrivalTime() const{
    return arrivalTime;
}

Time Schedule::getDepartureTime() const{
    return departureTime;
}

int Schedule::getLatency() const{
    return latency;
}

void Schedule::setDestination(string destination){
    this->destination = destination;
}

void Schedule::setDeparture(string departure){
    this->departure = departure;
}

void Schedule::setArrivalTime(const Time &arrivalTime) {
    this->arrivalTime = arrivalTime;
}

void Schedule::setDepartureTime(const Time &departureTime){
    this->departureTime = departureTime;
}

void Schedule::setLatency(int latency){
    this->latency = latency;
}

std::ostream& operator<<(std::ostream &os, const Schedule &schedule) {
    os << "Departure station: " << schedule.getDeparture()
       << "\nDeparture time: " << schedule.getDepartureTime()
       << "\nDestination station: " << schedule.getDestination();

    // Calculate the arrival time including the latency
    Time arrivalTime = schedule.getArrivalTime();
    int latency = schedule.getLatency();
    int totalMinutes = arrivalTime.getMinutes() + latency;
    int additionalHours = totalMinutes / 60;
    int finalMinutes = totalMinutes % 60;

    int totalHours = arrivalTime.getHours() + additionalHours;
    int finalHours = totalHours % 24;

    // Set the updated time
    arrivalTime.setHours(finalHours);
    arrivalTime.setMinutes(finalMinutes);

    os << "\nArrival time: " << arrivalTime << std::endl;
    return os;
}

