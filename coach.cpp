#include <sstream>
#include <fstream>
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


void Coach::serialize(const std::string &filename) const {
    std::ofstream outfile(filename, std::ios::app); // Open file for writing

    if (outfile.is_open()) {
        outfile << coachNumber << std::endl; // Coach number
        outfile << numSeats << std::endl;    // Number of seats
        outfile << "Seats:" << std::endl;
        for (size_t i = 0; i < numSeats; ++i) {
            outfile << seats[i].getSeatNumber() << " "; // Seat number
            outfile << (seats[i].booked() ? 1 : 0) << std::endl; // Booked status
        }
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }

    outfile.close();
}

void Coach::deserialize(const std::string &filename){
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(infile, line)) {
        int seatNumber, booked;
        std::stringstream ss(line);
        ss >> seatNumber >> booked;

        seats[seatNumber - 1].bookSeat();
    }

    infile.close();
}

Coach& Coach::operator=(Coach&& other) noexcept {
    if (this != &other) {
        coachNumber = other.coachNumber;
        seats = other.seats;
        numSeats = other.numSeats;
        isBooked = other.isBooked;
        other.seats = nullptr;
        other.numSeats = 0;
        other.isBooked = false;
    }
    return *this;
}