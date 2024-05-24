#ifndef MENU_H
#define MENU_H

#include "ticketSystem.h"
#include <iostream>
#include <string>


/**
 * @brief Abstract base class representing a menu.
 */
class Menu {
protected:
    std::string title; ///< Title of the menu
    TicketSystem ticketSystem; ///< Reference to the TicketSystem object

public:
    /**
     * @brief Constructs a new Menu object.
     * @param title The title of the menu.
     * @param ts Reference to the TicketSystem object.
     */
    Menu(const std::string& title, TicketSystem &ts) : title(title) , ticketSystem(ts){}

    /**
     * @brief Displays the menu options.
     */
    virtual void displayMenu() = 0;

    /**
     * @brief Handles user input for the menu.
     */
    virtual void handleUserInput() = 0;

    /**
    * @brief Executes the selected action.
    */
    virtual void executeAction() = 0;

    /**
     * @brief Gets the title of the menu.
     * @return The title of the menu.
     */
    std::string getTitle() const {
        return title;
    }
};

/**
 * @brief Class representing the Tickets menu.
 */
class TicketsMenu : public Menu {
public:
    /**
     * @brief Constructs a new TicketsMenu object.
     * @param ts Reference to the TicketSystem object.
     */
    TicketsMenu(TicketSystem &ts) : Menu("Tickets", ts) {}

    /**
     * @brief Displays the Tickets menu.
     */
    void displayMenu() override;

    /**
     * @brief Handles user input for the Tickets menu.
     */
    void handleUserInput() override;

    /**
    * @brief Executes the selected action in the Tickets menu.
    */
    void executeAction() override;
};

/**
 * @brief Class representing the Trains menu.
 */
class TrainsMenu : public Menu {
public:
    /**
     * @brief Constructs a new TrainsMenu object.
     * @param ts Reference to the TicketSystem object.
     */
    TrainsMenu(TicketSystem &ts) : Menu("Trains", ts) {}

    /**
    * @brief Displays the Trains menu.
    */
    void displayMenu() override;


    /**
     * @brief Handles user input for the Trains menu.
     */
    void handleUserInput() override;

    /**
    * @brief Executes the selected action in the Trains menu.
    */
    void executeAction() override;
};

/**
 * @brief Class representing the Schedule menu.
 */
class ScheduleMenu : public Menu {
public:
    /**
    * @brief Constructs a new ScheduleMenu object.
    * @param ts Reference to the TicketSystem object.
    */
    ScheduleMenu(TicketSystem &ts) : Menu("Schedule", ts) {}

    /**
     * @brief Displays the Schedule menu.
     */
    void displayMenu() override;

    /**
    * @brief Handles user input for the Schedule menu.
    */
    void handleUserInput() override;

    /**
  * @brief Executes the selected action in the Schedule menu.
  */
    void executeAction() override;
};

/**
 * @brief Class representing the Exit menu.
 */
class ExitMenu : public Menu {
public:
    /**
     * @brief Constructs a new ExitMenu object.
     * @param ts Reference to the TicketSystem object.
     */
    ExitMenu(TicketSystem &ts) : Menu("Exit", ts) {}

    /**
     * @brief Displays the Exit menu.
     */
    void displayMenu() override;

    /**
    * @brief Handles user input for the Exit menu.
    */
    void handleUserInput() override;

    /**
    * @brief Executes the selected action in the Exit menu.
    */
    void executeAction() override;
};

/**
 * @brief Class representing the Main menu.
 */
class MainMenu : public Menu {
private:
    Menu* subMenus[4]; /// Array of pointers to submenus

public:
    /**
    * @brief Constructs a new MainMenu object.
    * @param ts Reference to the TicketSystem object.
    */
    MainMenu(TicketSystem &ts) : Menu("Main Menu", ts) {}


    /**
    * @brief Adds a submenu to the Main menu.
    * @param subMenu Pointer to the submenu.
    * @param index Index to add the submenu.
    */
    void addSubMenu(Menu* subMenu, int index);

    /**
     * @brief Displays the Main menu.
     */
    void displayMenu() override;

    /**
     * @brief Handles user input for the Main menu.
     */
    void handleUserInput() override;

    /**
     * @brief Executes the selected action in the Main menu.
     */
    void executeAction() override;
};

#endif // MENU_H
