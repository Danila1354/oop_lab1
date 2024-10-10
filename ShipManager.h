#ifndef OOP_LAB1_SHIPMANAGER_H
#define OOP_LAB1_SHIPMANAGER_H

#include <iostream>
#include "Ship.h"

class ShipManager {
private:
    std::vector<int> ship_sizes;
    std::vector<Ship> ships;
public:
    ShipManager(int number_of_ships, const std::vector<int> &ship_sizes);

    std::vector<Ship> &getShips();


};


#endif //OOP_LAB1_SHIPMANAGER_H
