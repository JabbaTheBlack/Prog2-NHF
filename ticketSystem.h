#ifndef NH_TICKETSYSTEM_H
#define NH_TICKETSYSTEM_H

#include "linkedList.h"
#include "train.h"
#include "ticket.h"
#include "memtrace.h"

/**
 * @brief The TicketSystem class manages trains and tickets.
 */
class TicketSystem{
    LinkedList<Train*> trains; /**< List of trains managed by the system */
    LinkedList<Ticket*> tickets; /**< List of tickets issued by the system */

public:
    /**
     * @brief Adds a train to the system.
     * @param train Reference to the train to be added.
     */
    void addTrain(Train &train);



    /**
     * @brief Removes a train from the system.
     * @param trainId ID of the train to be removed.
     */
    void removeTrain(int trainId);

    /**
     * @brief Removes a ticket from the system.
     * @param ticketId ID of the ticket to be removed.
     */
    void removeTicket(int ticketId);


    /**
     * @brief Issues a ticket for a specific schedule and time.
     * @param schedule Reference to the schedule.
     * @param time Reference to the time.
     */
    void issueTicket(Schedule &schedule, const Time &time);

    /**
    * @brief Gets the list of trains in the system.
    * @return Reference to the list of trains.
    */
    LinkedList<Train*> &getTrains();

    /**
     * @brief Gets the list of tickets in the system.
     * @return Reference to the list of tickets.
     */
    LinkedList<Ticket*> &getTickets();

    /**
     * @brief Searches for a train in the system by ID.
     * @param id ID of the train to search for.
     * @return Pointer to the train if found, nullptr otherwise.
     */
    Train* searchTrain(int id);

    /**
    * @brief Deserializes train data from a file.
    */
    void desirializeTrain(TicketSystem &ticketSystem, const std::string &filename);

    /**
     * @brief Deserializes ticket data from a file.
     */
    void deserializeTicket(TicketSystem &ticketSystem, const std::string &filename);

    ~TicketSystem(){
        // Delete all trains
        Node<Train*> *trainNode = trains.begin();
        while (trainNode != nullptr) {
            delete trainNode->getData();
            trainNode = trainNode->getNext();
        }

        // Delete all tickets
        Node<Ticket*> *ticketNode = tickets.begin();
        while (ticketNode != nullptr) {
            delete ticketNode->getData();
            ticketNode = ticketNode->getNext();
        }
    };

};

#endif //NH_TICKETSYSTEM_H
