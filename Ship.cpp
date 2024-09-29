#include "Ship.h"


Ship::Ship(unsigned short length) {
    checkLength(length);
    this->length = length;
    segments.resize(length);
    is_placed = false;
    for (auto &segment: segments) {
        segment.state = 2;
    }
}

Ship::Ship(const Ship &other) {
    length = other.length;
    segments.resize(length);
    is_placed = other.is_placed;
    for (int i = 0; i < length; i++) {
        segments[i].state = other.segments[i].state;
        segments[i].x = other.segments[i].x;
        segments[i].y = other.segments[i].y;
    }
}


Ship &Ship::operator=(const Ship &other) {
    if (this == &other) {
        return *this;
    }
    length = other.length;
    segments.resize(length);
    is_placed = other.is_placed;
    for (int i = 0; i < length; i++) {
        segments[i].state = other.segments[i].state;
        segments[i].x = other.segments[i].x;
        segments[i].y = other.segments[i].y;
    }
    return *this;
}

void Ship::checkLength(int length) {
    if (length < 1 || length > 4) {
        throw std::invalid_argument("Invalid ship length");
    }
}

void Ship::takeDamage(int x, int y) {
    for (auto &segment: segments) {
        if (segment.x == x && segment.y == y) {
            if (segment.state > 0)
                segment.state--;
            return;
        }
    }
}

std::vector<std::vector<int>> Ship::getShipCoords() {
    std::vector<std::vector<int>> ship_coords;
    for (auto &segment: segments) {
        ship_coords.push_back({segment.x, segment.y});
    }
    return ship_coords;
}

bool Ship::isShipDestroyed() {
    for (auto &segment: segments) {
        if (segment.state > 0)
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

int Ship::getSegmentState(int x, int y) {
    for (auto &segment: segments) {
        if (segment.x == x && segment.y == y) {
            return segment.state;
        }
    }
    throw std::invalid_argument("Segment not found");
}

void Ship::setSegmentCoords(int x, int y, int index) {
    checkSegmentIndex(index);
    segments[index].x = x;
    segments[index].y = y;
}

bool Ship::isPlaced() {
    return is_placed;
}

void Ship::setPlaced(bool is_placed) {
    this->is_placed = is_placed;
}

