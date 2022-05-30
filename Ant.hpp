#ifndef ANT_HPP
#define ANT_HPP

#include "Map.hpp"
#include "Pixel.hpp"

class Pixel;
class Map;

class Ant {
private:
    sf::Vector2f position;
    sf::Vector2f heading;
    Map *map;
    
public:
    Ant(sf::Vector2f pos, sf::Vector2f head, Map *map);
    void move();
    sf::Vector2f getNewDirection();
    void draw();
    void print();
};

#endif
