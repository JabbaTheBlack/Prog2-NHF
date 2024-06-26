#include <sstream>
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

    Time arrivalTime = schedule.getArrivalTime();
    int latency = schedule.getLatency();
    int totalMinutes = arrivalTime.getMinutes() + latency;
    int additionalHours = totalMinutes / 60;
    int finalMinutes = totalMinutes % 60;

    int totalHours = arrivalTime.getHours() + additionalHours;
    int finalHours = totalHours % 24;

    arrivalTime.setHours(finalHours);
    arrivalTime.setMinutes(finalMinutes);

    os << "\nArrival time: " << arrivalTime << std::endl;
    return os;
}


void Schedule::serialize(std::ofstream &outfile) const {
    outfile << departure << std::endl
            << destination << std::endl
            << departureTime
            << arrivalTime<<std::endl;
}

void Schedule::deserialize(std::ifstream &infile) {
    std::string departure;
    std::string destination;
    std::string line;
    Time departureTime;
    Time arrivalTime;
    int hours = 0, minutes = 0;

    std::getline(infile, departure);
    std::getline(infile, destination);

    std::getline(infile, line);
    std::stringstream ss(line);

    ss >> hours;
    ss.ignore(1);
    ss >> minutes;
    departureTime = Time(hours, minutes);

    std::getline(infile, line);
    std::stringstream ss2(line);
    ss2 >> hours;
    ss2.ignore(1);
    ss2 >> minutes;
    arrivalTime = Time(hours, minutes);

    setDeparture(departure);
    setDestination(destination);
    setDepartureTime(departureTime);
    setArrivalTime(arrivalTime);
}