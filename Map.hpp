#ifndef MAP_HPP
#define MAP_HPP

#include "Pixel.hpp"
#include "Ant.hpp"

class Pixel;
class Ant;

class Map {
private:
    Pixel* pixel[ROWS][COLS];
    Ant* ants[ANT_NUM];
    
public:
    Map();
    void draw();
    void move();
    Pixel* getPixel(sf::Vector2f position);
};

#endif
