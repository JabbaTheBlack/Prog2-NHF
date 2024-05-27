#include "seat.h"
#include "memtrace.h"

void Seat::bookSeat(){
    isBooked = true;
}

void Seat::unBookSeat(){
    isBooked = false;
}

bool Seat::booked() const{
    return isBooked;
}

bool Seat::operator==(const Seat &seat) const{
    return(seatNumber == seat.seatNumber);
}

int Seat::getSeatNumber() const{
    return seatNumber;
}

