#ifndef FLOCK_H
#define FLOCK_H

#include <vector>
#include <SFML\Graphics.hpp>
#include "BoidObject.hpp"

class Flock {
public:

    Flock(sf::RenderWindow* pWindow, int nBoids);

    void draw();

    void update(float dt);

private:
    sf::RenderWindow* pWindow;
    
    std::vector<BoidObject> boids;
};

#endif //FLOCK_H