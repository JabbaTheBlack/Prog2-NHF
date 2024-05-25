cmake_minimum_required(VERSION 3.26)
project(NH)

set(CMAKE_CXX_STANDARD 17)

add_executable(NH main.cpp
        node.h
        linkedList.h
        seat.h
        seat.cpp
        coach.h
        time.h
        time.cpp
        schedule.h
        schedule.cpp
        train.h
        train.cpp
        ticket.h
        ticket.cpp
        ticketSystem.h
        ticketSystem.cpp
        memtrace.h
        memtrace.cpp
        coach.cpp)
