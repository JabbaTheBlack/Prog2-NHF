#ifndef NH_SCHEDULE_H
#define NH_SCHEDULE_H

#include <iostream>

using namespace std;

#include <fstream>
#include "time.h"
#include "memtrace.h"

/**
 * @brief Represents a schedule for a transportation service.
 */
class Schedule{
    Time arrivalTime; /**< The arrival time */
    Time departureTime; /**< The departure time */
    string destination; /**< The destination */
    string departure; /**< The departure location */
    int latency; /**< The latency */

public:
    /**
     * @brief Constructs a schedule with specified departure, destination, arrival time, departure time, and latency.
     *
     * @param departure The departure location.
     * @param destination The destination.
     * @param arrivalTime The arrival time.
     * @param departureTime The departure time.
     * @param latency The latency.
     */
    Schedule(string departure, string destination, const Time &arrivalTime, const Time &departureTime, int latency = 0) {
        this->arrivalTime = arrivalTime;
        this->departureTime = departureTime;
        this->departure = departure;
        this->destination = destination;
        this->latency = latency;
    }

    /**
     * @brief Constructs a schedule with specified departure and destination.
     *
     * @param departure The departure location.
     * @param destination The destination.
     */
    Schedule(string departure, string destination) {
        this->departure = departure;
        this->destination = destination;
    }

    string getDestination() const; /**< Get the destination. */
    string getDeparture() const; /**< Get the departure location. */
    Time getArrivalTime() const; /**< Get the arrival time. */
    Time getDepartureTime() const; /**< Get the departure time. */
    int getLatency() const; /**< Get the latency. */

    void setDestination(string destination); /**< Set the destination. */
    void setDeparture(string departure); /**< Set the departure location. */
    void setArrivalTime(const Time &arrivalTime); /**< Set the arrival time. */
    void setDepartureTime(const Time &departureTime); /**< Set the departure time. */
    void setLatency(int latency); /**< Set the latency. */


    void serialize(std::ofstream &outfile) const;
    void deserialize(std::ifstream &infile);

};

/**
 * @brief Overloaded stream insertion operator for Schedule class.
 *
 * @param os The output stream.
 * @param schedule The schedule to be inserted.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream &os, const Schedule &schedule);

#endif //NH_SCHEDULE_H
