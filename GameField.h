#ifndef OOP_LAB1_GAMEFIELD_H
#define OOP_LAB1_GAMEFIELD_H

#include <iostream>
#include "Cell.h"
#include "ShipManager.h"

class GameField {
private:
    std::vector<std::vector<Cell>> field;
    int width;
    int height;
    int number_of_deployed_ships;

    void check_collide(std::vector<std::vector<int>> ship_1_coords, std::vector<std::vector<int>> ship_2_coords);

    void checkXCoord(int x, int ship_length);

    void checkYCoord(int y, int ship_length);

    void checkCoords(int x, int y);

    void checkWidthAndHeight(int width, int height);

    void setShipCoords(Ship &ship, int x, int y, int ship_length, char position);

public:
    GameField(int width, int height);

    GameField(const GameField &other);

    GameField &operator=(const GameField &other);

    GameField(GameField &&other);

    GameField &operator=(GameField &&other);

    void attackCell(int x, int y, ShipManager &ship_manager);

    void show();

    void placeShip(Ship &ship, int x, int y, char position, std::vector<Ship> &ships);

    int getWidth();

    int getHeight();


};


#endif //OOP_LAB1_GAMEFIELD_H
