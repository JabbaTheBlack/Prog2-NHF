#include "time.h"
#include "memtrace.h"

int Time::getHours() const{
    return hours;
}

int Time::getMinutes() const{
    return minutes;
}

void Time::setHours(int hours){
    if(hours > 24){
        throw"Hours cannot be more than 24\n";
    }
    this->hours = hours;
}

void Time::setMinutes(int minutes){
    if(minutes > 60){
        throw"Minutes cannot be more than 60\n";
        return;
    }
    this->minutes = minutes;
}

bool Time::operator==(const Time &time)const{
    return(hours == time.hours && minutes == time.minutes);
}

bool Time::operator<(const Time &time)const{
    if (hours < time.hours) {
        return true;
    } else if (hours > time.hours) {
        return false;
    } else {
        return minutes < time.minutes;
    }
}

Time::Time(const Time &time){
    if(time.hours > 24){
        this->hours = time.hours;
    }
    else if(time.minutes > 60){
        this->hours += 1;
        if(this->hours > 24){
            this->hours -= 24;
        }
    }
    this->hours = time.hours;
    this->minutes = time.minutes;
}

bool Time::operator>(const Time &time) const{
    if(hours > time.hours) {
        return true;
    }else if(hours == time.hours && minutes < time.minutes){
        return true;
    }else{
        return false;
    }
}

bool Time::operator>=(const Time &time) const{
    if(hours > time.hours) {
        return true;
    }else if(hours == time.hours && minutes >= time.minutes){
        return true;
    }else{
        return false;
    }
}

bool Time::operator<=(const Time &time) const{
    if(hours < time.hours) {
        return true;
    }else if(hours == time.hours && minutes <= time.minutes){
        return true;
    }else{
        return false;
    }
}

std::ostream& operator<<(std::ostream &os, const Time &time){
    os << time.getHours()<<":";
    if(time.getMinutes() < 10){
        os<<"0";
    }else{
        os<<time.getMinutes()<<std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream &is, Time &time){
    is >> time.hours >> time.minutes;
    return is;
}

Time Time::operator+(const Time &time) const{
    int totalMinutes = this->hours * 60 + this->minutes + time.getHours() * 60 + time.getMinutes();
    int newHours = totalMinutes / 60;
    int newMinutes = totalMinutes % 60;
    return Time(newHours, newMinutes);
}