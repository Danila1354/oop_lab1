#ifndef OOP_LAB1_SHIP_H
#define OOP_LAB1_SHIP_H

#include <iostream>

enum class SegmentState{
    FULL, Damaged, Destroyed
};

class Ship {
private:
    unsigned short length;
    std::vector<SegmentState> segments;
    bool is_placed;

    void checkSegmentIndex(int index);

    void checkLength(int length);

public:
    Ship(unsigned short length);

    void takeDamage(int index);

    bool isShipDestroyed();

    unsigned short getLength();

    SegmentState getSegmentState(int index);

    void setPlaced(bool is_placed);

    bool isPlaced();

};


#endif //OOP_LAB1_SHIP_H
