#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "EventSystem.hpp"

sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1700, 1000), "Escape To Eclipse", sf::Style::Default);
GlobalEvents::GlobalHandler* hnd = new GlobalEvents::GlobalHandler(window);

//#-- Inits
void initBasicEventFunctionallity();

int main() {    

    initBasicEventFunctionallity();
    
    while (window->isOpen()) {
        window->display();
        hnd->pollAndExecuteEvents();
        window->clear(sf::Color::Black);
    }
    return 0;
}

void initBasicEventFunctionallity() {
    //ToDo
}