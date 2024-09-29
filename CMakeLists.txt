cmake_minimum_required(VERSION 3.27)
project(oop_lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(oop_lab1 main.cpp
        Ship.cpp
        Ship.h
        Cell.cpp
        Cell.h
        ShipManager.cpp
        ShipManager.h
        GameField.cpp
        GameField.h
)
