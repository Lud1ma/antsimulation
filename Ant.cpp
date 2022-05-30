#ifndef ANT_CPP
#define ANT_CPP

#include "Ant.hpp"
#include "Map.hpp"
#include "Pixel.hpp"

Ant::Ant(sf::Vector2f pos, sf::Vector2f head, Map *map) {
    position = pos;
    heading = head;
    this->map = map;
}

    void Ant::move() {
        position += heading;
        heading = getNewDirection();
    }

    sf::Vector2f Ant::getNewDirection() {
        return sf::Vector2f(0, 0);
    }

void Ant::draw() 

void Ant::print() 

#endif
