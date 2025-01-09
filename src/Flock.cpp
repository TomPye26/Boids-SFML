
#include "Flock.hpp"
#include <cmath>
#include <random>
#include <iostream>


Flock::Flock(sf::RenderWindow* pWindow, int nBoids, float boidSize) : pWindow(pWindow) {
    
    sf::Vector2u windowSize = pWindow->getSize();

    // random normal dist gen
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 100.0f);

    /* 
    change mass to scale how much impact the "force" has on boids.
    0.1 seems like a good value.
    */
    static const float BOID_MASS = 0.1f; 
    // initalise boids in a grid with random velocity
    
    float spacing = boidSize * 10.0f * 2.0f;
    float posX, posY;
    posX = spacing/2.0f;
    posY = spacing/2.0f;
    for (int i=0; i<nBoids; i++) {
        if (posX > windowSize.x) {
            posY += spacing;
            posX = spacing/2.0f;
        }

        if (posY > windowSize.y) {
            std::cout << "Number of boids exceeds starting capacity";  
            throw;
        }

        BoidObject boid(pWindow, boidSize, BOID_MASS);
        boid.setPosition(sf::Vector2f(posX, posY));
        boid.setVelocity(sf::Vector2f(dist(gen), dist(gen)));

        boids.push_back(boid);
        posX += spacing;
    };

};

void Flock::draw() {
    for (BoidObject& boid : boids) {
        boid.draw();
    }
};

void Flock::update(float dt) {
    for (BoidObject& boid : boids) {
        boid.update(dt, boids);
    }
}