#include "ShipManager.h"

ShipManager::ShipManager(int number_of_ships, const std::vector<int> &ship_sizes) {
    this->ship_sizes = ship_sizes;
    for (int i = 0; i < number_of_ships; i++) {
        ships.emplace_back(Ship(ship_sizes[i]));
    }
}

std::vector<Ship> &ShipManager::getShips() {
    return ships;
}

void ShipManager::reportDamage(int x, int y) {
    for (auto &ship: ships) {
        ship.takeDamage(x, y);
    }
}