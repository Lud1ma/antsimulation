#define ROWS 1500
#define COLS 1000
#define ANT_NUM 10
#define WINDOW_X 1900
#define WINDOW_Y 1100
#define MAX_STRENGTH 100
#define PI 3.14
#define ANGLE 25*PI/180

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <functional>
#include <cmath>

#include <SFML/Graphics.hpp>

sf::RenderWindow* window;

class Pixel {
private:
    sf::Vector2f position;
    float strength;
    float it;
    
public:
    Pixel(sf::Vector2f pos) {
        position = pos;
        strength = 0;
    }
    Pixel(float x, float y) {
        position = sf::Vector2f(x, y);
        strength = 0;
    }
    void print() {
        std::cout << "(" << position.x << "|" << position.y << "): " << strength << std::endl;
    }
    void setActive() {
        strength = MAX_STRENGTH; 
        draw(sf::Color(0, 255, 0));
        it++;
    }
    bool diminish() {
        draw(sf::Color(0, (int)255*(strength/MAX_STRENGTH), 0));
        if (strength > 0) {
            strength--;
            return false;
        } else {
            return true;
        }
        //draw(sf::Color(0, 0, 0));
    }
    void show() {
        draw(sf::Color(it*10, 0, 0));
    }
    sf::Vector2f getPosition() {return position;}
    float getStrength() {return strength;}
    
    void draw(sf::Color color) {
        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(2, 2));
        rect.setPosition(position);
        rect.setFillColor(color);
        window->draw(rect);
    }
};

Pixel *pixel[ROWS][COLS];
std::vector<Pixel*> activePixel = std::vector<Pixel*>();

sf::Vector2f inRange(sf::Vector2f v) {
    if (v.x < 0) v.x += ROWS-1;
    if (v.y < 0) v.y += COLS-1;
    v.x = fmod(v.x, ROWS-1);
    v.y = fmod(v.y, COLS-1);
    return v;
}

Pixel* getPixel(sf::Vector2f v) {
    return pixel[(int)std::ceil(inRange(v).x)][(int)std::ceil(inRange(v).y)];
}

class Ant {
private:
    sf::Vector2f position;
    sf::Vector2f heading;
    
public:
    Ant(sf::Vector2f pos, sf::Vector2f head) {
        position = pos;
        heading = head;
    }
    void move() {
        position += heading;
        if (position.x < 0) position.x += ROWS-1;
        if (position.y < 0) position.y += COLS-1;
        position.x = fmod(position.x, ROWS-1);
        position.y = fmod(position.y, COLS-1);
        heading = getNewDirection();
    }
    sf::Vector2f getNewDirection() {
        std::vector<sf::Vector2f> tests = std::vector<sf::Vector2f>();
        for (int i = -15; i < 20; i++) {
            tests.push_back(sf::Vector2f(heading.x * cos(i*PI/180) - heading.y * sin(i*PI/180), heading.x * sin(i*PI/180)+ heading.y * cos(i*PI/180)));
        }
        
        float best = 0;
        sf::Vector2f bester = heading;
        
        for (sf::Vector2f v: tests) {
            sf::Vector2f p = inRange(position+v);
            if (pixel[(int)std::ceil((p).x)][(int)std::ceil((p).y)]->getStrength() > best) {
                best = pixel[(int)std::ceil((p).x)][(int)std::ceil((p).y)]->getStrength();
                bester = v;
            }
        }
        
        return bester;
    }
    void draw() {
        std::vector<sf::Vector2f> points = {sf::Vector2f(0, 0), sf::Vector2f(0, 1), sf::Vector2f(1, 0), sf::Vector2f(1, 1), sf::Vector2f(0, -1), sf::Vector2f(-1, 0), sf::Vector2f(-1, -1), sf::Vector2f(1, -1), sf::Vector2f(-1, 1)}; //
        //std::vector<sf::Vector2f> points = {sf::Vector2f(0, 0)};
        
        for (sf::Vector2f v: points) {
            getPixel(position+v)->setActive();
            activePixel.push_back(getPixel(position+v));
        }
    }
    void print() {
        std::cout << "(" << position.x << "|" << position.y << ")" << std::endl;
    }
};

Ant *ants[ANT_NUM];

void pixelBefuellen() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            pixel[i][j] = new Pixel(sf::Vector2f(i, j));
        }
    }
}

void pixelDiminish() {
//     std::vector<Pixel*>::iterator it = activePixel.begin();
//     while (it != activePixel.end()) {
//         if (activePixel.at(it)->diminish()) {
//             it = activePixel.erase(it);
//         } else {
//             it++;
//         }
//     }
    // activePixel <Pixel*>
     auto remove = [&](Pixel* p) {return p->diminish();};
     activePixel.erase(std::remove_if(activePixel.begin(), activePixel.end(), remove), activePixel.end());
}

void pixelBefahren() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            pixel[i][j]->show();
        }
    }
}


void ameisenBefuellen() {
    srand(time(0));
    for (int i = 0; i < ANT_NUM; i++) {
        ants[i] = new Ant(sf::Vector2f(rand()%ROWS, rand()%COLS), sf::Vector2f(2-(rand()%4), 2-(rand()%4)));
    }
}

void ameisenZeichnen() {
    for (int i = 0; i < ANT_NUM; i++) {
        ants[i]->draw();
        //ants[i]->print();
    }
}

void ameisenBewegen() {
    for (int i = 0; i < ANT_NUM; i++) {
        ants[i]->move();
    }
}

int main() {
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Ant Simulation");
//     window->setFramerateLimit(30);
    
    pixelBefuellen();
    ameisenBefuellen();
    ameisenZeichnen();
    
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                pixelBefahren();
                window->display();
                std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
                window->close();
            }
        }

        ameisenBewegen();
        ameisenZeichnen();
        pixelDiminish();
        //std::cout << "Length: " << activePixel.size() << std::endl;
        
        window->display();
        std::this_thread::sleep_for(std::chrono::nanoseconds(0));
    }
}



