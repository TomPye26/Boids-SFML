#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>

// #include "BoidObject.hpp"
# include "Flock.hpp"

int main() {

    // SFML window
    sf::RenderWindow window(sf::VideoMode({2000, 1500}), "SFML works!");
    window.setFramerateLimit(60);
    
    Flock flock(&window, 300, 2.0f);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            }

        float dt = 1.0f/60.0f;
        window.clear();
        
        flock.update(dt);
        flock.draw();

        window.display();
    }

    return 0;
}
