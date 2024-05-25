#include <fstream>
#include "train.h"
#include "memtrace.h"

void Train::addSchedule(Schedule &schedule){
    schedules.insert(&schedule);
}

void Train::removeSchedule(Schedule &schedule){
    schedules.remove(&schedule);
}

void Train::addCoach(Coach &coach){
    coaches.insert(&coach);
}

void Train::removeCoach(Coach &coach){
    coaches.remove(&coach);
}

int Train::getId() const{
    return id;
}

string Train::getName() const {
    return name;
}

string Train::getType() const{
    return type;
}

void Train::setId(int id){
    this->id = id;
}

void Train::setName(string name){
    this->name = name;
}

void Train::setType(string type){
    this->type =type;
}

LinkedList<Schedule*>& Train::getSchedule(){
    return schedules;
}

LinkedList<Coach*>& Train::getCoaches(){
    return coaches;
}

bool Train::getBooked() const{
    return isBooked;
}

void Train::setBooked(bool isBooked){
    this->isBooked = isBooked;
}

std::ostream& operator<<(std::ostream &os, Train &train){
    os<<"Id: "<<train.getId()
             <<"\nName: "<<train.getName()
             <<"\nType: "<<train.getType()
             <<"\nNumber of coaches: "<<train.getCoaches().getSize()
             <<"\nNumber of schedules: "<<train.getSchedule().getSize();

    return os;
}


void Train::serialize(const std::string &filename){
    std::ofstream outfile(filename, std::ios::app); // Open file for appending

    if(outfile.is_open()){
        outfile << "Train:\n"
                << id << std::endl // Train ID
                << name << std::endl // Train Name
                << type << std::endl // Train Type
                << (isBooked ? 0 : 1) << std::endl << std::endl; // Is Booked

        // Write schedules information if available
        if (schedules[0] != nullptr) {
            outfile << "Schedules:\n";
            for (Node<Schedule*>* scheduleNode = schedules.begin(); scheduleNode != nullptr; scheduleNode = scheduleNode->getNext()) {
                Schedule* schedule = scheduleNode->getData();
                schedule->serialize(outfile); // Serialize schedule
            }
        }

        // Write coaches information if available
        if (coaches[0] != nullptr) {
            outfile << "Coaches:\n";
            for (Node<Coach*>* coachNode = coaches.begin(); coachNode != nullptr; coachNode = coachNode->getNext()) {
                Coach* coach = coachNode->getData();
                outfile << coach->getCoachNumber() << std::endl // Coach Number
                        << coach->getNumSeats() << std::endl << std::endl; // Number of seats

                coach->serialize(filename); // Serialize coach
            }
        }

        outfile << std::endl << std::endl;
        outfile.close();
    } else {
        throw "Error opening file\n";
    }
}


/*

void Train::serializeTrain(const std::string &filename){
    std::ofstream outfile(filename, std::ios::app); // Open file for appending

    if(outfile.is_open()){
        outfile<<"Train:\n";
        outfile << id << std::endl // Train ID
        << name << std::endl // Train Name
        << type << std::endl // Train Type
        << (isBooked ? 0 : 1) << std::endl<<std::endl; // Is Booked

        // Write schedules information if available
        if (schedules[0] != nullptr) {
            outfile<<"Schedules:\n";
            for (Node<Schedule*>* scheduleNode = schedules.begin(); scheduleNode != nullptr; scheduleNode = scheduleNode->getNext()) {
                Schedule* schedule = scheduleNode->getData();
                outfile << schedule->getDeparture() << std::endl //Departure
                <<schedule->getDestination() << std::endl //Destination
                << schedule->getDepartureTime()<<std::endl //Departure Time
                << schedule->getArrivalTime()<<std::endl<<std::endl; //Arrival Time
            }
        }

        // Write coaches information if available
        if (coaches[0] != nullptr) {
            outfile<<"Coaches:\n";
            for (Node<Coach*>* coachNode = coaches.begin(); coachNode != nullptr; coachNode = coachNode->getNext()) {
                outfile<< coachNode->getData()->getCoachNumber() << std::endl //Coach Number
                << coachNode->getData()->getNumSeats() << std::endl<<std::endl; //Number of seats

                // Print booked seats
                outfile<<"Seats:\n";
                for (size_t i = 0; i < coachNode->getData()->getNumSeats(); i++) {
                    if (coachNode->getData()->getSeats()[i].booked()) {
                        outfile << coachNode->getData()->getSeats()[i].getSeatNumber() << std::endl;
                    }
                }
            }
        }
        outfile<<std::endl<<std::endl;
        outfile.close();
    } else {
        throw"Error opening file\n";
    }
}
*/
