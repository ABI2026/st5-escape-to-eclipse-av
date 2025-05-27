#pragma once

#include "UIEngine.hpp"

/*
UIComponents::UICContainer::UICContainer(std::string id, sf::Vector2f relPos, sf::Vector2f dims,
                            Alignment::Margin margin, Alignment::Margin padding,
                            Alignment::SelfAlign selfAlign, Alignment::InnerAlignment innerAlignmentMode)

    Hello World, I love to program C++. Test Test Test. Keyboard test
                            */

using namespace UIEngine;

class Dialog : public UIComponents::UICContainer {
    public:
        Dialog() : UIComponents::UICContainer("Hello-Dialog", 
                                              sf::Vector2f(200, 100), 
                                              sf::Vector2f(600, 400), Alignment::Margin(20, 20, 20, 20),
                                              Alignment::Margin(0, 0, 0, 0),
                                              Alignment::SelfAlign::SA_NO_OVERRIDE,
                                              Alignment::InnerAlignment::IA_GRID) {
            this->setFillColor(sf::Color(0, 0, 0));
            this->setOutlineColor(sf::Color(0, 140, 255));
            this->setOutlineThickness(1.f);
            
            Alignment::GridTemplate grid(3, 2);
            grid.setGridRows(3, 50.f, 200.f, 50.f);
            grid.setGridColumns(3, 50.f, 200.f, 50.f);
            
            
        }

        ~Dialog() = default;
};