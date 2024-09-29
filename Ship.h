#ifndef OOP_LAB1_SHIP_H
#define OOP_LAB1_SHIP_H

#include <iostream>

struct Segment {
    int state;
    int x;
    int y;
};

class Ship {
private:
    unsigned short length;
    std::vector<Segment> segments;
    bool is_placed;

    void checkSegmentIndex(int index);

    void checkLength(int length);

public:
    Ship(unsigned short length);

    Ship(const Ship &other);

    Ship &operator=(const Ship &other);

    void takeDamage(int x, int y);

    std::vector<std::vector<int>> getShipCoords();

    bool isShipDestroyed();

    unsigned short getLength();

    int getSegmentState(int x, int y);

    void setSegmentCoords(int x, int y, int index);

    void setPlaced(bool is_placed);

    bool isPlaced();

};


#endif //OOP_LAB1_SHIP_H
