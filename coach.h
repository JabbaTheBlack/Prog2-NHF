#ifndef NH_COACH_H
#define NH_COACH_H

#include <memory>
#include "seat.h"
#include "memtrace.h"

#include <iostream>
/**
 * @brief Class representing a coach in a train.
 */
class Coach{
    int coachNumber; /**< The number of the coach. */
    Seat *seats; /**< Pointer to an array of seats in the coach. */
    size_t numSeats; /**< The number of seats in the coach. */
    bool isBooked; /**< Indicates whether the coach is booked. */

public:
    /**
      * @brief Construct a new Coach object.
      *
      * @param coachNumber The number of the coach.
      * @param numSeats The number of seats in the coach.
      * @param isBooked Indicates whether the coach is booked.
      */
    Coach(int coachNumber, int numSeats = 100, bool isBooked = false) : coachNumber(coachNumber), numSeats(numSeats), isBooked(isBooked){
        seats = new Seat[numSeats];
        for (size_t i = 0; i < static_cast<size_t>(numSeats); ++i) {
            seats[i] = Seat(i + 1); // Seat numbers start from 1 (optional)
        }
    }

    Coach(const Coach &coach);
    Coach& operator=(const Coach&);
    Coach(Coach&& other) noexcept
            : coachNumber(other.coachNumber), seats(other.seats),
              numSeats(other.numSeats), isBooked(other.isBooked) {
        other.seats = nullptr;
        other.numSeats = 0;
        other.isBooked = false;
    }

    Coach& operator=(Coach&& other) noexcept;

        /**
         * @brief Get a pointer to the array of seats in the coach.
         *
         * @return Seat* Pointer to the array of seats.
         */
    Seat *getSeats();

    /**
     * @brief Get the number of seats in the coach.
     *
     * @return size_t The number of seats.
     */
    size_t size() const;

    /**
     * @brief Check if the coach is booked.
     *
     * @return true If the coach is booked.
     * @return false If the coach is not booked.
     */
    bool getBooked() const;

    /**
     * @brief Books the whole coach
     */
    void booked();
    /**
     * @brief Get the number of the coach.
     *
     * @return int The number of the coach.
     */
    int getCoachNumber() const;

    /**
     * @brief Get the total number of seats in the coach.
     *
     * @return size_t The total number of seats.
     */
    size_t getNumSeats() const;

    /**
     * @brief Serialize the coach data to a file.
     *
     * @param filename The name of the file to write the data to.
     */
    void serialize(const std::string &filename) const;

    /**
     * @brief Deserialize the coach data from a file.
     *
     * @param filename The name of the file to read the data from.
     */
    void deserialize(const std::string &filename);

    /**
     * @brief Destroy the Coach object and deallocate memory for seats.
     */
    ~Coach(){delete[] seats;}
};

#endif //NH_COACH_H
