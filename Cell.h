#ifndef OOP_LAB1_CELL_H
#define OOP_LAB1_CELL_H

#include "Ship.h"

enum class Status {
    Empty, Occupied
};

class Cell {
private:
    int x;
    int y;
    bool is_open;
    Status status;
    Ship *pointer_to_ship;

    void copyCell(const Cell &other);

public:
    Cell(int x = 0, int y = 0);

    Cell(const Cell &other);

    Cell &operator=(const Cell &other);

    void display();

    void openCell();

    void setStatus(Status status);

    Status getStatus();

    Ship *getPointerToShip();

    void setPointerToShip(Ship *pointer_to_ship);

    int getX();

    int getY();

};


#endif //OOP_LAB1_CELL_H
