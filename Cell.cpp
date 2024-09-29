#include "Cell.h"

Cell::Cell(int x, int y) {
    this->x = x;
    this->y = y;
    is_open = false;
    status = Status::Empty;
    pointer_to_ship = nullptr;
}

void Cell::copyCell(const Cell &other) {
    x = other.x;
    y = other.y;
    is_open = other.is_open;
    status = other.status;
    if (other.pointer_to_ship != nullptr) {
        pointer_to_ship = new Ship(*other.pointer_to_ship);
    } else {
        pointer_to_ship = nullptr;
    }
}

Cell::Cell(const Cell &other) {
    copyCell(other);
}

Cell &Cell::operator=(const Cell &other) {
    if (this != &other) {
        delete pointer_to_ship;
        copyCell(other);
    }
    return *this;
}

void Cell::display() {
    if (is_open) {
        if (status == Status::Empty)
            std::cout << "⚪";
        else {
            if (pointer_to_ship->isShipDestroyed()) {
                std::cout << "🔥";
                return;
            }
            int segment_state = pointer_to_ship->getSegmentState(x, y);
            if (segment_state == 1) {
                std::cout << u8"\U0001F7E5";
            } else {
                std::cout << "❌";
            }

        }
    } else
        std::cout << "⬜\uFE0F";
}

void Cell::openCell() {
    is_open = true;
}

void Cell::setStatus(Status status) {
    this->status = status;
}

Status Cell::getStatus() {
    return status;
}

Ship *Cell::getPointerToShip() {
    return pointer_to_ship;
}

void Cell::setPointerToShip(Ship *pointer_to_ship) {
    this->pointer_to_ship = pointer_to_ship;
}

int Cell::getX() {
    return x;
}

int Cell::getY() {
    return y;
}