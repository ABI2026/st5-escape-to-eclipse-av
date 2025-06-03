#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

#include "EventSystem.hpp"
#include "UIEngine.hpp"
#include "UI/Config.hpp"

sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1700, 1000), "Escape To Eclipse", sf::Style::Default);
GlobalEvents::GlobalHandler* hnd = new GlobalEvents::GlobalHandler(window);

//#-- Inits
void initBasicEventFunctionallity(GlobalEvents::GlobalHandler*);

int main() {    
    window->setFramerateLimit(60);
    initBasicEventFunctionallity(hnd);

    EscapeToEclipse::UI::GameUIConfig UICONF = EscapeToEclipse::UI::GameUIConfig::getSingleton();

    UICONF.setCurrentTheme("Mars Dirt");
    std::cout << UICONF.getCurrentTheme().getName() << std::endl;
    UIEngine::UIConfig::UITheme t = UICONF.getCurrentTheme();
    t.represent();

    while (window->isOpen()) {
        window->clear(sf::Color::Black);
        hnd->pollAndExecuteEvents();
        window->display();    
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