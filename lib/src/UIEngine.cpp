#include "UIEngine.hpp"

using namespace UIEngine;

//#-- Definitions of UIAlignment Tools
Alignment::GridTemplate::~GridTemplate() {
    delete[] gridTemplateColumns;
    delete[] gridTemplateRows;
    for 

}

bool Alignment::GridTemplate::setGridRows(int diff, sf::Vector2f ...) {
    va_list args;
    va_start(args, diff);

    (!diff) ? this->m_diff = diff : this->m_diff;

    if (!this->gridTemplateRows && this->m_diff == diff) {
        this->gridTemplateRows = new sf::Vector2f[this->m_diff];
        for (int i = 0; i < this->m_diff; i++) {
            sf::Vector2f limitPoint = va_arg(args, int);
            *(this->m_gridTemplateRows + i) = limitPoint;
        }
        va_end(args);
        return true;
    }

    va_end(args);
    return false;
}

//#-- Definitions of UIComponents::Interactible
UIComponents::Interactible::Interactible(GlobalEvents::GlobalHandler* hnd) : m_hnd(hnd) {
    for (unsigned int i = 0; i < 4; i++) {
        this->m_callbackMap.insert(std::make_pair(static_cast<UIItemEventAction>(i), [&] (const sf::Event&) -> void {}));
    }
};
void UIComponents::Interactible::setOnMouseOver(GlobalEvents::ECallbackAttechment cb) 
{ this->m_callbackMap[UIItemEventAction::MOUSEOVER] = cb; }

void UIComponents::Interactible::setOnMouseOut(GlobalEvents::ECallbackAttechment cb)
{ this->m_callbackMap[UIItemEventAction::MOUSEOUT] = cb; }

void UIComponents::Interactible::setOnMouseDown(GlobalEvents::ECallbackAttechment cb)
{ this->m_callbackMap[UIItemEventAction::MOUSEDOWN] = cb; }

void UIComponents::Interactible::setOnMouseUp(GlobalEvents::ECallbackAttechment cb)
{ this->m_callbackMap[UIItemEventAction::MOUSEUP] = cb; }