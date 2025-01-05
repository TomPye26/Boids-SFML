#include <cmath>
#include <iostream>

#include "BoidObject.hpp"

BoidObject::BoidObject(
    sf::RenderWindow* window,
    sf::Vector2f pos,
    sf::Vector2f vel,
    float size
) : position(pos), velocity(vel), window(window) 
{
    shape.setPointCount(4);
    shape.setPoint(0, sf::Vector2f(0, -5) * size);  // top point
    shape.setPoint(1, sf::Vector2f(-5, 5) * size);  // left point
    shape.setPoint(2, sf::Vector2f(0, 2.5) * size); // inner-middle point
    shape.setPoint(3, sf::Vector2f(5, 5) * size);   // Right point
    shape.setFillColor(sf::Color::White);     // Color of the boid
    shape.setOrigin(0.f, 0.f);
    shape.setPosition(pos);
    setAngle(); 
};

void BoidObject::draw() {
    window->draw(shape);
};

void BoidObject::update(float dt) {
    position += velocity * dt;

    sf::Vector2u windowSize = window->getSize();
    
    // Check if the boid is near the edge and loop back around
    if (position.x <= 0 || position.x >= windowSize.x || 
        position.y <= 0 || position.y >= windowSize.y) {
        if (position.x < 0) position.x = windowSize.x;
        if (position.x > windowSize.x) position.x = 0;
        if (position.y < 0) position.y = windowSize.y;
        if (position.y > windowSize.y) position.y = 0;
    }
    
    shape.setPosition(position);
    // setAngle();
};

void BoidObject::setAngle() {
    float velX = velocity.x;
    float velY = velocity.y;


    if (velX != 0.f || velY != 0.f) {
        float angle = std::atan2(velY, velX);
        angle = angle * (180.0f / 3.1415927f) + 90;
        
        
        shape.setRotation(angle);
    }
}