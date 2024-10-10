#include "Cell.h"

Cell::Cell(int x, int y) : x(x), y(y), is_open(false), status(Status::Empty), pointer_to_ship(nullptr),
index_of_segment(-1) {}


void Cell::display() {
    if (is_open) {
        if (status == Status::Empty)
            std::cout << "⚪";
        else {
            if (pointer_to_ship->isShipDestroyed()) {
                std::cout << "🔥";
                return;
            }
            SegmentState segment_state = pointer_to_ship->getSegmentState(index_of_segment);
            if (segment_state == SegmentState::Damaged) {
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


void Cell::setIndexOfSegment(int index) {
    index_of_segment = index;
}

int Cell::getIndexOfSegment() {
    return index_of_segment;
}


