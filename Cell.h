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
    int index_of_segment;
    Ship *pointer_to_ship;


public:
    Cell(int x = 0, int y = 0);

    void display();

    void openCell();

    void setStatus(Status status);

    Status getStatus();

    Ship *getPointerToShip();

    void setPointerToShip(Ship *pointer_to_ship);

    int getX();

    int getY();

    void setIndexOfSegment(int index);

    int getIndexOfSegment();

};


#endif //OOP_LAB1_CELL_H
