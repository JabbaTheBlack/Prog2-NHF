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


    Schedule(const Schedule& other) : departure(other.departure), destination(other.destination) {}
    /**
      * @brief Get the destination.
      * @return The destination string.
      */
    string getDestination() const;

    /**
     * @brief Get the departure location.
     * @return The departure location string.
     */
    string getDeparture() const;

    /**
     * @brief Get the arrival time.
     * @return The arrival time object.
     */
    Time getArrivalTime() const;

    /**
     * @brief Get the departure time.
     * @return The departure time object.
     */
    Time getDepartureTime() const;

    /**
     * @brief Get the latency.
     * @return The latency value (in minutes).
     */
    int getLatency() const;

    // Setters
    /**
     * @brief Set the destination.
     * @param destination The new destination string.
     */
    void setDestination(string destination);

    /**
     * @brief Set the departure location.
     * @param departure The new departure location string.
     */
    void setDeparture(string departure);

    /**
     * @brief Set the arrival time.
     * @param arrivalTime The new arrival time object.
     */
    void setArrivalTime(const Time& arrivalTime);

    /**
     * @brief Set the departure time.
     * @param departureTime The new departure time object.
     */
    void setDepartureTime(const Time& departureTime);

    /**
     * @brief Set the latency.
     * @param latency The new latency value (in minutes).
     */
    void setLatency(int latency);

    /**
     * @brief Serialize the schedule data to an output stream (e.g., file).
     *
     * @param outfile The output stream to write the data to.
     */
    void serialize(std::ofstream& outfile) const;

    /**
     * @brief Deserialize the schedule data from an input stream (e.g., file).
     *
     * @param infile The input stream to read the data from.
     */
    void deserialize(std::ifstream& infile);

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
