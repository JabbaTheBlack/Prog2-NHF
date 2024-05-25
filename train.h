#ifndef NH_TRAIN_H
#define NH_TRAIN_H

#include "seat.h"
#include "coach.h"
#include "linkedList.h"
#include "schedule.h"
#include "memtrace.h"

#include <iostream>


/**
 * @brief Represents a Train entity.
 */
class Train{
    int id; /**< The ID of the train. */
    string name; /**< The name of the train. */
    string type; /**< The type of the train. */
    LinkedList<Schedule*> schedules; /**< List of schedules associated with the train. */
    LinkedList<Coach*> coaches; /**< List of coaches associated with the train. */
    bool isBooked; /**< Indicates whether the train is booked or not. */

public:
    /**
   * @brief Constructs a new Train object.
   * @param id The ID of the train.
   * @param name The name of the train.
   * @param type The type of the train.
   * @param isBooked Indicates whether the train is booked or not.
   */
    Train(int id, std::string name = "", std::string type = "Sebesvonat", bool isBooked = false) : id(id), name(name),
    type(type), schedules(), coaches(), isBooked(isBooked){}


    /**
     * @brief Copy constructor.
     * @param train The train object to copy.
     */
    Train(const Train &train);

    /**
    * @brief Adds a schedule to the train.
    * @param schedule The schedule to be added.
    */
    void addSchedule(Schedule &schedule);

    /**
    * @brief Removes a schedule from the train.
    * @param schedule The schedule to be removed.
    */
    void removeSchedule(Schedule &schedule);

    /**
   * @brief Adds a schedule to the train.
   * @param schedule The schedule to be added.
   */
    void addCoach(Coach &coach);

    /**
     * @brief Removes a schedule from the train.
     * @param schedule The schedule to be removed.
     */
    void removeCoach(Coach &coach);

    /**
    * @brief Gets the ID of the train.
    * @return The ID of the train.
    */
    int getId() const;

    /**
   * @brief Gets the name of the train.
   * @return The name of the train.
   */
    std::string getName() const;

    /**
     * @brief Gets the type of the train.
     * @return The type of the train.
     */
    std::string getType() const;

    /**
    * @brief Gets whether the train is booked or not.
    * @return True if the train is booked, false otherwise.
    */
    bool getBooked() const;


    /**
   * @brief Sets the ID of the train.
   * @param id The ID of the train.
   */
    void setId(int id);

    /**
     * @brief Sets the name of the train.
     * @param name The name of the train.
     */
    void setName(std::string name);

    /**
    * @brief Sets the type of the train.
    * @param type The type of the train.
    */
    void setType(std::string type);

    /**
   * @brief Sets whether the train is booked or not.
   * @param isBooked True if the train is booked, false otherwise.
   */
    void setBooked(bool isBooked);

    /**
     * @brief Gets the list of schedules associated with the train.
     * @return Reference to the list of schedules.
     */
    LinkedList<Schedule*> &getSchedule();

    /**
     * @brief Gets the list of coaches associated with the train.
     * @return Reference to the list of coaches.
     */
    LinkedList<Coach*> &getCoaches();

    /**
     * @brief Serializes the train data to a file.
     */
    void serialize(const std::string &filename);

    ~Train(){
        Node<Coach*> *coachNode = coaches.begin();
        while (coachNode != nullptr) {
            delete coachNode->getData();
            coachNode = coachNode->getNext();
        }
        delete coachNode;

        Node<Schedule*> *scheduleNode = schedules.begin();
        while (scheduleNode != nullptr) {
            delete scheduleNode->getData();
            scheduleNode = scheduleNode->getNext();
        }
        delete coachNode;
    }

};

/**
 * @brief Overloaded stream insertion operator for printing train details.
 * @param os The output stream.
 * @param train The train object to be printed.
 * @return Reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, Train &train);

#endif //NH_TRAIN_H
