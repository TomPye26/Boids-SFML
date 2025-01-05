
#ifndef BOID_OBJECT_H
#define BOID_OBJECT_H

#include <SFML\Graphics.hpp>

class BoidObject {

public:
    BoidObject(
        sf::RenderWindow* window,
        sf::Vector2f pos,
        sf::Vector2f vel,
        float size
    );

    void draw();
    
    void update(float dt);

private:
    sf::RenderWindow* window;

    sf::Vector2f position;
    sf::Vector2f velocity;

    sf::ConvexShape shape;

    void setAngle();
};

#endif // BOID_OBJECT_H