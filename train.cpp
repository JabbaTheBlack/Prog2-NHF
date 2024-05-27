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
    std::ofstream outfile(filename, std::ios::app);

    if(outfile.is_open()){
        outfile << "Train:\n"
                << id << std::endl
                << name << std::endl
                << type << std::endl
                << (isBooked ? 0 : 1) << std::endl << std::endl;

        if (schedules[0] != nullptr) {
            outfile << "Schedules:\n";
            int scheduleCount = 0; // Counter to track the number of schedules written
            for (Node<Schedule*>* scheduleNode = schedules.begin(); scheduleNode != nullptr; scheduleNode = scheduleNode->getNext()) {
                Schedule* schedule = scheduleNode->getData();
                schedule->serialize(outfile);
                scheduleCount++;
            }
        }

        if (coaches[0] != nullptr) {
            outfile << "Coaches:\n";
            for (Node<Coach*>* coachNode = coaches.begin(); coachNode != nullptr; coachNode = coachNode->getNext()) {
                Coach* coach = coachNode->getData();
                coach->serialize(filename);
            }
        }

        outfile.close();
    } else {
        throw "Error opening file\n";
    }
}

