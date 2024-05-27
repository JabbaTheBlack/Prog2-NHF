#ifndef NH_TIME_H
#define NH_TIME_H

#include <iostream>
#include "memtrace.h"

/**
 * @brief The Time class represents a specific time in hours and minutes.
 */
class Time {
    int hours;   /**< Hours component of the time */
    int minutes; /**< Minutes component of the time */
public:
    /**
   * @brief Constructor for Time class.
   * @param hours Number of hours (default is 0).
   * @param minutes Number of minutes (default is 0).
   */
    Time(int hours = 0, int minutes = 0) : hours(hours), minutes(minutes){}

    /**
     * @brief Copy constructor for Time class.
     * @param time Reference to another Time object.
     */
    Time(const Time &time) : hours(time.hours), minutes(time.minutes) {}


    /**
     * @brief Get the hours component of the time.
     * @return Number of hours.
     */
    int getHours() const;

    /**
     * @brief Get the minutes component of the time.
     * @return Number of minutes.
     */
    int getMinutes() const;


    /**
     * @brief Set the hours component of the time.
     * @param hours Number of hours.
     */
    void setHours(int hours);

    /**
    * @brief Set the minutes component of the time.
    * @param minutes Number of minutes.
    */
    void setMinutes(int minutes);

    /**
     * @brief Less than operator for comparing two Time objects.
     * @param time Another Time object to compare with.
     * @return True if this Time is less than the other Time, false otherwise.
     */
    bool operator<(const Time &time) const;

    /**
     * @brief Equality operator for comparing two Time objects.
     * @param time Another Time object to compare with.
     * @return True if this Time is equal to the other Time, false otherwise.
     */
    bool operator==(const Time &time) const;

    /**
    * @brief Greater than or equal operator for comparing two Time objects.
    * @param time Another Time object to compare with.
    * @return True if this Time is greater than or equal to the other Time, false otherwise.
    */
    bool operator>=(const Time &time) const;

    /**
    * @brief Less than or equal operator for comparing two Time objects.
    * @param time Another Time object to compare with.
    * @return True if this Time is less than or equal to the other Time, false otherwise.
    */
    bool operator<=(const Time &time) const;

    /**
     * @brief Greater than operator for comparing two Time objects.
     * @param time Another Time object to compare with.
     * @return True if this Time is greater than the other Time, false otherwise.
     */
    bool operator>(const Time &time) const;

    /**
     * @brief Addition operator for adding two Time objects.
     * @param time Another Time object to add.
     * @return A new Time object representing the sum of the two times.
     */
    Time operator+(const Time &time) const;

    /**
     * @brief Output stream operator for Time class.
     * @param os Output stream.
     * @param time Time object to output.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream &os, const Time &time);

    /**
     * @brief Input stream operator for Time class.
     * @param is Input stream.
     * @param time Time object to input.
     * @return Reference to the input stream.
     */
    friend std::istream& operator>>(std::istream &is, Time &time);
};

/**
 * @brief Overloaded output stream operator for Time class.
 * @param os Output stream.
 * @param time Time object to output.
 * @return Reference to the output stream.
 */
std::ostream& operator<<(std::ostream &os, const Time &time);

/**
 * @brief Overloaded input stream operator for Time class.
 * @param is Input stream.
 * @param time Time object to input.
 * @return Reference to the input stream.
 */
std::istream& operator>>(std::istream &is, const Time &time);

#endif //NH_TIME_H
