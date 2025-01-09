
#ifndef BOID_OBJECT_H
#define BOID_OBJECT_H

#include <SFML\Graphics.hpp>

class BoidObject {

public:
    /*
    @breif: initaliser for boid object

    @param pWindow: pointer to SFML window that the boid is drawn on.
    @param size: scalar value to scale size of object.
    */
    BoidObject(
        sf::RenderWindow* pWindow,
        float size,
        float mass
    );

    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    

    void draw();
    
    void update(float dt, std::vector<BoidObject>& boids);

    // forces for flocking behaviour

    const float distToOtherBoid(const BoidObject& otherBoid);

    sf::Vector2f normalise(const sf::Vector2f& vector);

    sf::Vector2f calcSeparationForce(
        const std::vector<BoidObject>& boids,
        float impactDistance
    );

    sf::Vector2f calcCohesionForce(
        const std::vector<BoidObject>& boids,
        float impactDistance
    );

    sf::Vector2f calcAlignmentForce(
        const std::vector<BoidObject>& boids,
        float impactDistance
    );
    

private:
    sf::RenderWindow* pWindow;

    sf::Vector2f position;
    sf::Vector2f velocity;
    float mass;
    float maxSpeed = 300.0f;

    sf::ConvexShape shape;

    void setAngle();
};

#endif // BOID_OBJECT_H