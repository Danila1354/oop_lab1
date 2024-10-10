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


void GameField::attackCell(int x, int y) {
    checkCoords(x, y);
    field[y][x].openCell();
    if (field[y][x].getStatus() == Status::Occupied) {
        auto pointer_to_ship = field[y][x].getPointerToShip();
        auto index = field[y][x].getIndexOfSegment();
        pointer_to_ship->takeDamage(index);
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

bool GameField::checkCollide(int x, int y) {
    int row_above = y-1;
    int row_below = y+1;
    int left_col = x-1;
    int right_col = x+1;
    for (int i = row_above;i<row_below+1;i++){
        for (int j = left_col;j<right_col+1;j++){
            if ((j == x && i == y) || (j<0 || i<0 || i>=height || j>=width))
                continue;
            else{
                if (field[i][j].getStatus() == Status::Occupied)
                    return false;
            }
        }
    }
    return true;

}

void GameField::setShipCoords(Ship &ship, int x, int y, int ship_length, char position) {
    for (int i = 0; i < ship_length; i++) {
        if (position == 'v') {
            field[y + i][x].setStatus(Status::Occupied);
            field[y + i][x].setPointerToShip(&ship);
            field[y+i][x].setIndexOfSegment(i);
            if (!(ship.isPlaced())) {
                ship.setPlaced(true);
            }
        } else if (position == 'h') {
            field[y][x + i].setStatus(Status::Occupied);
            field[y][x + i].setPointerToShip(&ship);
            field[y][x+i].setIndexOfSegment(i);
            if (!(ship.isPlaced())) {
                ship.setPlaced(true);
            }
        } else {
            throw std::invalid_argument("Invalid position");
        }
    }

}

void GameField::placeShip(Ship &ship, int x, int y, char position) {
    auto ship_length = ship.getLength();
    for (int i = 0; i < ship_length; i++) {
        if (position == 'v') {
            checkYCoord(y, ship_length);
            if (!(checkCollide(x,y+i))){
                std::cout<<"Ships collide\n";
                return;
            }
        } else if (position == 'h') {
            checkXCoord(x, ship_length);
            if (!(checkCollide(x+i,y))){
                std::cout<<"Ships collide\n";
                return;
            }

        } else {
            throw std::invalid_argument("Invalid position");
        }
    }
    setShipCoords(ship,x,y,ship_length,position);
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
