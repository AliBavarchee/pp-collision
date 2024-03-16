#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

// Define particle properties
struct Particle {
  double px, py, pz, E; // Momentum and energy
};

// Function to generate random momentum within kinematic limits
Particle generateParticle(double beamEnergy) {
  // Use a random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> pTrans(-beamEnergy, beamEnergy);
  std::uniform_real_distribution<double> pLong(0, beamEnergy);

  // Calculate momentum components and total energy
  Particle p;
  p.px = pTrans(gen);
  p.py = pTrans(gen);
  p.pz = pLong(gen);
  p.E = sqrt(p.px * p.px + p.py * p.py + p.pz * p.pz + pow(beamEnergy, 2));
  return p;
}

// Function to perform head-to-head collision
std::vector<Particle> collide(Particle p1, Particle p2) {
  // very simple model of momenta
  p1.px *= -1;
  p2.px *= -1;
  std::vector<Particle> out = {p1, p2};
  return out;
}

int main() {
  // Set up SFML window
  sf::RenderWindow window(sf::VideoMode(800, 600), "ALICE Gold Ion Collision");

  // Define beam energy and number of events
  double beamEnergy = 6.5 * 10e12; // 13 TeV in center of mass
  int nEvents = 100;

  // Loop over events
  for (int i = 0; i < nEvents; ++i) {
    // Generate colliding particles
    Particle p1 = generateParticle(beamEnergy);
    Particle p2 = generateParticle(beamEnergy);

    // Perform collision
    std::vector<Particle> out = collide(p1, p2);

    // Clear window and draw axes
    window.clear();
    sf::VertexArray axisX(sf::Lines, 2);
    axisX[0].position = sf::Vector2f(0, window.getSize().y / 2);
    axisX[1].position = sf::Vector2f(window.getSize().x, window.getSize().y / 2);
    axisX[0].color = sf::Color::Red;
    axisX[1].color = sf::Color::Red;
    window.draw(axisX);
    sf::VertexArray axisY(sf::Lines, 2);
    axisY[0].position = sf::Vector2f(window.getSize().x / 2, 0);
    axisY[1].position = sf::Vector2f(window.getSize().x / 2, window.getSize().y);
    axisY[0].color = sf::Color::Green;
    axisY[1].color = sf::Color::Green;
    window.draw(axisY);

    // Draw outgoing particles
    for (const Particle& p : out) {
      sf::CircleShape circle(2);
      circle.setPosition(sf::Vector2f(window.getSize().x / 2 + p.px * 100,
                                     window.getSize().y / 2 - p.py * 100));
      circle.setFillColor(sf::Color::Blue);
      window.draw(circle);
    }

    // Display window and handle events
    window.display();
    sf::sleep(sf::milliseconds(100));
  }

  return 0;
}
