#include "Pythia8/Pythia.h"
#include "SFML/Graphics.hpp"
#include "vector"
#include "cstdlib"
#include "ctime"

using namespace Pythia8;

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for random number gen

    sf::RenderWindow window(sf::VideoMode(800, 600), "Gold Ion Collisions Simulation");

    // Representing two gold ions
    sf::CircleShape ion1(30);
    sf::CircleShape ion2(30);
    ion1.setFillColor(sf::Color::Yellow);
    ion2.setFillColor(sf::Color::Yellow);
    ion1.setPosition(100, 300);
    ion2.setPosition(700, 300);

    // Simulation parameters
    float speed = 0.1f;
    bool collided = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (!collided) {
            // Move ions towards each other
            ion1.move(speed, 0);
            ion2.move(-speed, 0);

            if (ion1.getPosition().x + 60 >= ion2.getPosition().x) {
                collided = true;
            }
        } else {
            // Very simple visualizing particle production :/
            for (int i = 0; i < 10; ++i) {
                sf::CircleShape particle(5);
                particle.setFillColor(sf::Color::Red);
                float angle = static_cast<float>(rand() % 360);
                float distance = static_cast<float>(rand() % 50 + 10);
                float x = 400 + distance * cos(angle);
                float y = 300 + distance * sin(angle);
                particle.setPosition(x, y);
                window.draw(particle);
            }
        }

        window.draw(ion1);
        window.draw(ion2);
        window.display();
    }

    return 0;
}
