#ifndef NH_MENU_H
#define NH_MENU_H

#ifndef MENU_H
#define MENU_H

#include "ticketSystem.h"

/**
 * @brief Displays the main menu options to the user.
 */
void displayMenu();

/**
 * @brief Displays the train-related menu options to the user.
 */
void displayTrainsMenu();

/**
 * @brief Displays the train-related menu options to the user.
 */
void displayTrainsSubMenu();

/**
 * @brief Handles user input for the main menu and interacts with the TicketSystem object.
 *
 * @param ticketSystem A reference to the TicketSystem object for data access and manipulation.
 * @param exitFlag A reference to a boolean flag indicating whether the user wants to exit the program.
 *        The function should update this flag based on user input.
 */
void handleUserInput(TicketSystem &ticketSystem, bool &exitFlag);

/**
 * @brief Prompts the user for a menu choice and validates their input.
 *
 * @return An integer representing the user's chosen menu option.
 */
int getChoice();

/**
 * @brief Guides the user through adding a new train to the TicketSystem object.
 *
 * @param ticketSystem A reference to the TicketSystem object to add the new train to.
 */
void addTrain(TicketSystem &ticketSystem);

/**
 * @brief Guides the user through searching for a train in the TicketSystem object.
 *
 * @param ticketSystem A reference to the TicketSystem object to search for trains in.
 */
void searchTrain(TicketSystem &ticketSystem);

/**
 * @brief Guides the user through removing a train from the TicketSystem object.
 *
 * @param ticketSystem A reference to the TicketSystem object to remove the train from.
 */
void removeTrain(TicketSystem &ticketSystem);

/**
 * @brief Displays the ticket-related menu options to the user.
 */
void displayTicketsMenu();



#endif // MENU_H


#endif //NH_MENU_H
