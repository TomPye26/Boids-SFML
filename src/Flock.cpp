
#include "Flock.hpp"
#include <cmath>
#include <random>
#include <iostream>


Flock::Flock(sf::RenderWindow* pWindow, int nBoids) : pWindow(pWindow) {
    
    sf::Vector2u windowSize = pWindow->getSize();

    // random normal dist gen
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 100.0f);

    /* 
    change mass to scale how much impact the "force" has on boids.
    0.1 seems like a good value.
    */
    const float boidMass = 0.1f; 
    const float boidSize = 3.0f;
    // initalise boids in a grid with random velocity
    
    float posX, posY;
    posX = 30.0f;
    posY = 30.0f;
    for (int i=0; i<nBoids; i++) {
        if (posX > windowSize.x) {
            posY += 100.0f;
            posX = 30.0f;
        }

        if (posY > windowSize.y) {
            std::cout << "Number of boids exceeds starting capacity";  
            throw;
        }

        BoidObject boid(pWindow, boidSize, boidMass);
        boid.setPosition(sf::Vector2f(posX, posY));
        boid.setVelocity(sf::Vector2f(dist(gen), dist(gen)));

        boids.push_back(boid);
        posX += 100.0f;
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