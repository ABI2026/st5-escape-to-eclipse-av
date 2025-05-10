#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Test.hpp"

sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1700, 1000), "Escape To Eclipse", sf::Style::Default);
GlobalEvents::GlobalHandler* hnd = new GlobalEvents::GlobalHandler(window);

//#-- Inits
void initBasicEventFunctionallity(GlobalEvents::GlobalHandler*);

int main() {    

    initBasicEventFunctionallity(hnd);
    
    while (window->isOpen()) {
        window->display();
        hnd->pollAndExecuteEvents();
        window->draw(new DialogTest());
        window->clear(sf::Color::Black);
    }
    return 0;
}

void initBasicEventFunctionallity(GlobalEvents::GlobalHandler* handler) {
    handler->deployActionMappingList(9,
        sf::Keyboard::Key::Escape,
        sf::Keyboard::Key::W,
        sf::Keyboard::Key::A,
        sf::Keyboard::Key::S,
        sf::Keyboard::Key::D,
        sf::Keyboard::Key::Up,
        sf::Keyboard::Key::Down,
        sf::Keyboard::Key::Right,
        sf::Keyboard::Key::Left
    );
    handler->deployActionMappingList(1,
        sf::Mouse::Button::Right
    );
}