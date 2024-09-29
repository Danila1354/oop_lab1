#include "GameField.h"

GameField::GameField(int width, int height) {
    checkWidthAndHeight(width, height);
    this->width = width;
    this->height = height;
    number_of_deployed_ships = 0;
    field.resize(height, std::vector<Cell>(width));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            field[i][j] = Cell(j, i);
        }
    }
}

GameField::GameField(const GameField &other)
        : width(other.width), height(other.height), number_of_deployed_ships(other.number_of_deployed_ships) {
    field.resize(height);
    for (int i = 0; i < height; ++i) {
        field[i].resize(width);
        for (int j = 0; j < width; ++j) {
            field[i][j] = other.field[i][j];
        }
    }
}

GameField &GameField::operator=(const GameField &other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        number_of_deployed_ships = other.number_of_deployed_ships;
        field.resize(height);
        for (int i = 0; i < height; ++i) {
            field[i].resize(width);
            for (int j = 0; j < width; ++j) {
                field[i][j] = other.field[i][j];
            }
        }
    }
    return *this;
}

GameField::GameField(GameField &&other)
        : width(other.width), height(other.height), number_of_deployed_ships(other.number_of_deployed_ships) {
    field = std::move(other.field);
    other.width = 0;
    other.height = 0;
    other.number_of_deployed_ships = 0;
}

GameField &GameField::operator=(GameField &&other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        number_of_deployed_ships = other.number_of_deployed_ships;
        field = std::move(other.field);
        other.width = 0;
        other.height = 0;
        other.number_of_deployed_ships = 0;
    }
    return *this;
}


void GameField::attackCell(int x, int y, ShipManager &ship_manager) {
    checkCoords(x, y);
    field[y][x].openCell();
    if (field[y][x].getStatus() == Status::Occupied) {
        ship_manager.reportDamage(x, y);
    }
}

void GameField::show() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            field[i][j].display();
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void
GameField::check_collide(std::vector<std::vector<int>> ship_1_coords, std::vector<std::vector<int>> ship_2_coords) {
    for (auto &ship_1_coord: ship_1_coords) {
        int x = ship_1_coord[0];
        int y = ship_1_coord[1];
        int block_coords[9][2] = {{x - 1, y - 1},
                                  {x - 1, y},
                                  {x - 1, y + 1},
                                  {x,     y - 1},
                                  {x,     y},
                                  {x,     y + 1},
                                  {x + 1, y - 1},
                                  {x + 1, y},
                                  {x + 1, y + 1}};
        for (auto &block_coord: block_coords) {
            for (auto &ship_2_coord: ship_2_coords) {
                if (block_coord[0] == ship_2_coord[0] && block_coord[1] == ship_2_coord[1]) {
                    throw std::invalid_argument("Ships collide");
                }
            }
        }
    }
}

void GameField::setShipCoords(Ship &ship, int x, int y, int ship_length, char position) {
    for (int i = 0; i < ship_length; i++) {
        if (position == 'v') {
            checkYCoord(y, ship_length);
            field[y + i][x].setStatus(Status::Occupied);
            field[y + i][x].setPointerToShip(&ship);
            ship.setSegmentCoords(x, y + i, i);
            if (!(ship.isPlaced())) {
                ship.setPlaced(true);
            }
        } else if (position == 'h') {
            checkXCoord(x, ship_length);
            field[y][x + i].setStatus(Status::Occupied);
            field[y][x + i].setPointerToShip(&ship);
            ship.setSegmentCoords(x + i, y, i);
            if (!(ship.isPlaced())) {
                ship.setPlaced(true);
            }
        } else {
            throw std::invalid_argument("Invalid position");
        }
    }
}

void GameField::placeShip(Ship &ship, int x, int y, char position, std::vector<Ship> &ships) {
    auto ship_length = ship.getLength();
    if (number_of_deployed_ships != 0) {
        for (auto &other_ship: ships) {
            if (&other_ship == &ship || !(other_ship.isPlaced()))
                continue;
            auto other_ship_coords = other_ship.getShipCoords();
            setShipCoords(ship, x, y, ship_length, position);
            auto ship_coords = ship.getShipCoords();
            check_collide(ship_coords, other_ship_coords);
        }
    }
    setShipCoords(ship, x, y, ship_length, position);
    number_of_deployed_ships++;
}

int GameField::getWidth() {
    return width;
}

int GameField::getHeight() {
    return height;
}


void GameField::checkWidthAndHeight(int width, int height) {
    if (width < 0 || height < 0)
        throw std::invalid_argument("Width and height must be positive");
}

void GameField::checkXCoord(int x, int ship_length) {
    if (x < 0 || x >= width)
        throw std::out_of_range("X coordinate is out of bounds");
    if (x + ship_length > width)
        throw std::out_of_range("Ship goes out of bounds");
}

void GameField::checkYCoord(int y, int ship_length) {
    if (y < 0 || y >= height)
        throw std::out_of_range("Y coordinate is out of bounds");
    if (y + ship_length > height)
        throw std::out_of_range("Ship goes out of bounds");

}

void GameField::checkCoords(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        throw std::out_of_range("Coordinates are out of bounds");
}
