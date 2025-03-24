#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "EventSystem.hpp"

sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1700, 1000), "Escape To Eclipse", sf::Style::Default);

int main() {    
    while (window->isOpen()) {
        window->display();
        window->clear(sf::Color::Black);
    }
    return 0;
}