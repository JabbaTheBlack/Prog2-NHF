#ifndef NH_SEAT_H
#define NH_SEAT_H

#include "memtrace.h"

/**
 * @brief A class representing a seat.
 */
class Seat{
    int seatNumber; /**< The seat number. */
    bool isBooked;  /**< A flag indicating whether the seat is booked or not. */

public:
    /**
     * @brief Constructor for Seat class.
     *
     * @param seatNumber The seat number.
     * @param isBooked A flag indicating whether the seat is booked or not.
     */
    Seat(int seatNumber = 0, bool isBooked = false) : seatNumber(seatNumber), isBooked(isBooked){}

    /**
     * @brief Books the seat.
     */
    void bookSeat();

    /**
     * @brief Unbooks the seat.
     */
    void unBookSeat();

    /**
    * @brief Checks if the seat is booked.
    *
    * @return True if the seat is booked, false otherwise.
    */
    bool booked() const;

    /**
     * @brief Overloaded equality operator.
     *
     * @param seat The seat to compare with.
     * @return True if the seat numbers are equal, false otherwise.
     */
    bool operator ==(const Seat &seat) const;

    /**
    * @brief Gets the seat number.
    *
    * @return The seat number.
    */
    int getSeatNumber() const;
};

#endif //NH_SEAT_H
