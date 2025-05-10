#pragma once

#include "UIEngine.hpp"

using namespace UIEngine;

//#-- This is supposed to be used as non-abstract class
class DialogTest : public UIComponents::UICContainer {
    public:
        DialogTest() {
            this->m_selfAlignment = Alignment::SelfAlign::SA_RELATIVE;
            this->m_relativePosition = sf::Vector2f(50, 50);
            this->m_shape.setFillColor(sf::Color(50, 50, 50));
            this->m_shape.setSize(sf::Vector2f(300, 300));
            this->m_shape.setPosition(this->m_relativePosition);
        }
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

void DialogTest::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->m_shape, states);
}

