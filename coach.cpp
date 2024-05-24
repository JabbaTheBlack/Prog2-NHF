#include "coach.h"

Seat *Coach::getSeats(){
    return seats;
}

size_t Coach::size() const{
    return numSeats;
}

bool Coach::getBooked() const{
    return isBooked;
}

void Coach::booked() {
    isBooked = true;
}

int Coach::getCoachNumber() const{
    return coachNumber;
}

size_t Coach::getNumSeats() const {
    return numSeats;
}