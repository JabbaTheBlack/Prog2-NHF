#ifndef NH_TICKET_H
#define NH_TICKET_H

#include "train.h"
#include "schedule.h"
#include "coach.h"
#include "seat.h"
#include "memtrace.h"

/**
 * @brief The Ticket class represents a ticket for a train journey.
 */
class Ticket{
    int id; /**< Ticket ID */
    double discount; /**< Discount applied to the ticket */
    Seat *seat; /**< Pointer to the seat booked */
    Coach *coach; /**< Pointer to the coach booked */
    Train *train; /**< Pointer to the train */
    Schedule *schedule; /**< Pointer to the schedule */
public:
    /**
    * @brief Constructor for Ticket class.
    * @param id Ticket ID.
    * @param schedule Pointer to the schedule (default is nullptr).
    * @param train Pointer to the train (default is nullptr).
    * @param coach Pointer to the coach (default is nullptr).
    * @param seat Pointer to the seat (default is nullptr).
    * @param discount Discount applied to the ticket (default is 1).
    */
    Ticket(int id, Schedule *schedule = nullptr, Train *train = nullptr, Coach *coach = nullptr, Seat *seat = nullptr, double discount = 1)
            : id(id), discount(discount), seat(seat), coach(coach), train(train), schedule(schedule) {}

    /**
     * @brief Gets the ticket ID.
     * @return The ticket ID.
     */
    int getId() const;

    /**
    * @brief Gets the seat booked for the ticket.
    * @return Pointer to the seat booked.
    */
    Seat* getSeat() const;


    /**
     * @brief Gets the coach booked for the ticket.
     * @return Pointer to the coach booked.
     */
    Coach* getCoach() const;

    /**
     * @brief Gets the train booked for the ticket.
     * @return Pointer to the train booked.
     */
    Train* getTrain() const;

    /**
     * @brief Gets the schedule booked for the ticket
     * @return Pointer to the schedule
     */
    Schedule* getSchedule() const;
    /**
    * @brief Gets the discount applied to the ticket.
    * @return The discount applied.
    */
    double getDiscount() const;

    /**
    * @brief Sets the discount for the ticket.
    * @param discount The discount to be applied.
    */
    void setDiscount(double discount);

    /**
     * @brief Sets the train for the ticket.
     * @param train Pointer to the train.
     */
    void setTrain(Train *train);


    /**
     * @brief Sets the coach for the ticket.
     * @param coach Pointer to the coach.
     */
    void setCoach(Coach *coach);

    /**
     * @brief Sets the seat for the ticket.
     * @param seat Pointer to the seat.
     */
    void setSeat(Seat *seat);

    /**
     * @brief Serializes the ticket information to a file.
     */
    void serializeTicket(const std::string &filename);


};

/**
 * @brief Overloaded output operator for Ticket class.
 * @param os Output stream
 * @param ticket Ticket object
 * @return Reference to the output stream
 */
std::ostream& operator<<(std::ostream &os, const Ticket &ticket);

#endif //NH_TICKET_H
