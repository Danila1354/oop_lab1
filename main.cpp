#include "GameField.h"
#include "ShipManager.h"

int main() {
    GameField field{10, 10};
    auto ship_manager = ShipManager(3, {3, 1, 2});
    int ships_coords[3][2] = {{5, 4},
                              {9, 4},
                              {7, 1}};
    auto &ships = ship_manager.getShips();
    char positions[] = {'h', 'h', 'v'};
    for (int i = 0; i < 3; i++) {
        field.placeShip(ships[i], ships_coords[i][0], ships_coords[i][1], positions[i], ships);
    }
    field.attackCell(5, 4, ship_manager);
    field.show();


    return 0;
}
