#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>

#include "BoidObject.hpp"

int main()
{
    // random normal dist gen
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 100);

    // SFML window
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML works!");
    window.setFramerateLimit(60);

    // create collection of boids
    std::vector<BoidObject> boids;
    int pos0 = 100;
    for (int i=0; i<10; i++) {
        float velX, velY;
        velX = dist(gen);
        velY = dist(gen);

        std::cout << "V_x, V_y = " << velX << ", " << velY << std::endl;
        pos0 += 50;

        BoidObject boid(
            &window,
            sf::Vector2f(pos0,pos0),
            sf::Vector2f(velX, velY),
            5
        );

        boids.push_back(boid);
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = 1.0f/60.0f;
        window.clear();
        
        for (BoidObject& boid : boids) {
            boid.update(dt);
            boid.draw();
        }

        window.display();
    }

    return 0;
}
