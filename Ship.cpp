#include "Ship.h"


Ship::Ship(unsigned short length) {
    checkLength(length);
    this->length = length;
    segments.resize(length);
    is_placed = false;
    for (auto &segment: segments) {
        segment = SegmentState::FULL;
    }
}


void Ship::checkLength(int length) {
    if (length < 1 || length > 4) {
        throw std::invalid_argument("Invalid ship length");
    }
}

void Ship::takeDamage(int index) {
    checkSegmentIndex(index);
    auto &segment = segments[index];
    switch (segment){
        case SegmentState::FULL:
            segment = SegmentState::Damaged;
            break;
        case SegmentState::Damaged:
            segment = SegmentState::Destroyed;
            break;
        case SegmentState::Destroyed:
            break;
    }

}


bool Ship::isShipDestroyed() {
    for (auto &segment: segments) {
        if (segment == SegmentState::FULL || segment == SegmentState::Damaged)
            return false;
    }
    return true;
}

unsigned short Ship::getLength() {
    return length;
}

void Ship::checkSegmentIndex(int index) {
    if (index >= segments.size()) {
        throw std::out_of_range("Invalid segment index");
    }
}

SegmentState Ship::getSegmentState(int index) {
    checkSegmentIndex(index);
    return segments[index];
}

bool Ship::isPlaced() {
    return is_placed;
}

void Ship::setPlaced(bool is_placed) {
    this->is_placed = is_placed;
}

