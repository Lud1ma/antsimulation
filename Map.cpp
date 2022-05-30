#ifndef MAP_CPP
#define MAP_CPP

#include "Map.hpp"
#include "Pixel.hpp"
#include "Ant.hpp"

Map::Map() {
    for (int i = 0; i < ANT_NUM; i++) {
        ants[i] = new Ant(sf::Vector2f(0, 0), sf::Vector2f(1, 1), this);
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            pixel[i][j] = new Pixel(sf::Vector2f(i, j));
        }
    }
}
void Map::draw() {
    for (int i = 0; i < ANT_NUM; i++) {
        ants[i]->draw();
    }
}
void Map::move() {
    for (int i = 0; i < ANT_NUM; i++) {
        ants[i]->move();
    }
}
Pixel* Map::getPixel(sf::Vector2f position) {
    return pixel[(int)position.x][(int)position.y];
}

#endif
