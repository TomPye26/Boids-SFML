#include <cmath>
#include <iostream>

#include "BoidObject.hpp"

BoidObject::BoidObject(
    sf::RenderWindow* pWindow,
    float size,
    float mass
) : pWindow(pWindow), mass(mass)
{
    shape.setPointCount(4);
    shape.setPoint(0, sf::Vector2f(0, -5) * size);  // top point
    shape.setPoint(1, sf::Vector2f(-5, 5) * size);  // left point
    shape.setPoint(2, sf::Vector2f(0, 2.5) * size); // inner-middle point
    shape.setPoint(3, sf::Vector2f(5, 5) * size);   // Right point
    shape.setFillColor(sf::Color::White);     // Color of the boid
    shape.setOrigin(0.f, 0.f);
    // shape.setPosition(pos);
    // setAngle(); 
};

void BoidObject::setPosition(sf::Vector2f position) {
    this->position = position;
    shape.setPosition(position);
};

void BoidObject::setVelocity(sf::Vector2f velocity) {
    this->velocity = velocity;
    setAngle();
};

sf::Vector2f BoidObject::getPosition() const {
    return position;
}

sf::Vector2f BoidObject::getVelocity() const {
    return velocity;
}

void BoidObject::draw() {
    pWindow->draw(shape);
};

void BoidObject::update(float dt, std::vector<BoidObject>& boids) {
    
    sf::Vector2f sepForce = calcSeparationForce(boids, 80.0f) / mass;
    sf::Vector2f coheForce = calcCohesionForce(boids, 100.0f)  / mass;
    sf::Vector2f algnForce = calcAlignmentForce(boids, 100.0f)  / mass;


    float separationWeight = 4.0;
    float cohesionWeight = 1.0;
    float alignmentWeight = 1.5;

    velocity += sepForce * separationWeight;
    velocity += coheForce * cohesionWeight;
    velocity += algnForce * alignmentWeight;

    float absVelocity = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
    if (absVelocity > maxSpeed) {
        velocity = normalise(velocity) * maxSpeed;
    }
    setAngle();

    position += velocity * dt;

    sf::Vector2u windowSize = pWindow->getSize();
    
    // Check if the boid is near the edge and loop back around
    if (position.x <= 0 || position.x >= windowSize.x || 
        position.y <= 0 || position.y >= windowSize.y) {
        if (position.x < 0) position.x = windowSize.x;
        if (position.x > windowSize.x) position.x = 0;
        if (position.y < 0) position.y = windowSize.y;
        if (position.y > windowSize.y) position.y = 0;
    }
    
    shape.setPosition(position);
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

// flocking behaviour functions

const float BoidObject::distToOtherBoid(const BoidObject& otherBoid) {
    sf::Vector2f thisPos = this->getPosition();
    sf::Vector2f otherPos = otherBoid.getPosition();

    sf::Vector2u windowSize = pWindow->getSize();

    float dx = thisPos.x - otherPos.x;
    float dy = thisPos.y - otherPos.y;

    // // Handle the wrapping in the x direction
    // if (std::abs(dx) > windowSize.x / 2) {
    //     if (dx > 0) {
    //         dx -= windowSize.x;
    //     } else {
    //         dx += windowSize.x;
    //     }
    // }

    // // Handle the wrapping in the y direction
    // if (std::abs(dy) > windowSize.y / 2) {
    //     if (dy > 0) {
    //         dy -= windowSize.y;
    //     } else {
    //         dy += windowSize.y;
    //     }
    // }

    float dist = std::sqrt(dx * dx + dy * dy);

    return dist;
}


sf::Vector2f BoidObject::normalise(const sf::Vector2f& vector) {
        float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
        return length > 0.f ? vector / length : sf::Vector2f(0.f, 0.f);
    }

sf::Vector2f BoidObject::calcSeparationForce(
    const std::vector<BoidObject>& boids,
    float impactDistance
) {
    sf::Vector2f force(0.0f, 0.0f);
    int otherBoidCount = 0;

    for (const BoidObject& boid : boids) {

        // skip self
        if (this == &boid) {
            continue;
        }

        float distToOther = distToOtherBoid(boid);
        
        if (distToOther <= impactDistance && distToOther != 0) {
            sf::Vector2f posDiff = position - boid.getPosition();
            force += (posDiff / distToOther);

            otherBoidCount++;
        }

    }
    // normalise by how many other boids impact this one.
    if (otherBoidCount>0) {
        force /= float(otherBoidCount);
    }

    return force;

};

sf::Vector2f BoidObject::calcCohesionForce(
    const std::vector<BoidObject>& boids,
    float impactDistance
) {
    sf::Vector2f force(0.0f, 0.0f);
    int otherBoidCount = 0;

    for (const BoidObject& boid : boids) {

        // skip self
        if (this == &boid) {continue;}

        float distToOther = distToOtherBoid(boid);

        if (distToOther <= impactDistance) {
            force += boid.getPosition();

            otherBoidCount++;
        }

    }
    // normalise by how many other boids impact this one.
    if (otherBoidCount>0) {
        force /= float(otherBoidCount);
        force = force - position;
        force = normalise(force);
    };

    return force;
    
};

sf::Vector2f BoidObject::calcAlignmentForce(
    const std::vector<BoidObject>& boids,
    float impactDistance
) {
    sf::Vector2f force(0.0f, 0.0f);
    int otherBoidCount = 0;

    for (const BoidObject& boid : boids) {

        // skip self
        if (this == &boid) {continue;}

        float distToOther = distToOtherBoid(boid);

        if (distToOther <= impactDistance) {
            force += boid.getVelocity();

            otherBoidCount++;
        }

    }
    // normalise by how many other boids impact this one.
    if (otherBoidCount>0) {
        force /= float(otherBoidCount);
        force = normalise(force);
    };

    return force;
    
};
