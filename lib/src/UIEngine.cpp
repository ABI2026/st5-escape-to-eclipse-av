#include "UIEngine.hpp"

using namespace UIEngine;

//#-- Definitions of UIAlignment Tools
Alignment::GridTemplate::~GridTemplate() { 
    delete[] gridTemplateColumns;
    delete[] gridTemplateRows;
    //#-- interative delete 2d areas areas
    for (int i = 0; i < this->m_rowDiff; i++) {
        delete[] *(this->gridTemplateAreas + i);
    }
    //#-- everything removed!
}

//#- Return value may be unused
bool Alignment::GridTemplate::setGridRows(unsigned int diff, sf::Vector2f ...) {
    va_list args;
    va_start(args, diff);

    (!this->m_rowDiff == 0) ? this->m_rowDiff = diff : this->m_rowDiff;

    this->m_completed = this->m_checkUsabillity();

    if (this->m_rowDiff == diff) {
        delete[] this->gridTemplateRows;
        this->gridTemplateRows = new sf::Vector2f[this->m_rowDiff];
        for (int i = 0; i < this->m_rowDiff; i++) {
            sf::Vector2f limitPoint = va_arg(args, sf::Vector2f);
            *(this->gridTemplateRows + i) = limitPoint;
        }
        for (int i = 0; i < this->m_rowDiff; i++) {
            delete[] *(this->gridTemplateAreas + i);
        }
        this->gridTemplateAreas = nullptr;
        va_end(args);
        return true;
    }

    va_end(args);
    return false;
}
//#- Return value may be unused
bool Alignment::GridTemplate::setGridColumns(unsigned int diff, sf::Vector2f ...) {
    va_list args;
    va_start(args, diff);

    (!this->m_columnDiff == 0) ? this->m_columnDiff = diff : this->m_columnDiff;

    this->m_completed = this->m_checkUsabillity();

    if (this->m_columnDiff == diff) {
        delete[] this->gridTemplateColumns;
        this->gridTemplateColumns = new sf::Vector2f[this->m_columnDiff];
        for (int i = 0; i < this->m_columnDiff; i++) {
            sf::Vector2f limitPoint = va_arg(args, sf::Vector2f);
            *(this->gridTemplateColumns + i) = limitPoint;
        }
        for (int i = 0; i < this->m_rowDiff; i++) {
            delete[] *(this->gridTemplateAreas + i);
        }
        this->gridTemplateAreas = nullptr;
        va_end(args);
        return true;
    }
    va_end(args);
    return false;
}

bool Alignment::GridTemplate::setGridAreaIDs(std::string areasTemplate) {
    /*#-- Passtrough format 2x5 Matrix
        AREA-NAME 0|0;AREA-NAME 0|1;AREA-NAME 0|2;AREA-NAME 0|3;AREA-NAME 0|4; /e
        AREA-NAME 1|0;AREA-NAME 1|1;AREA-NAME 1|2;AREA-NAME 1|3;AREA-NAME 1|4; /e
    */
    for (int i = 0; i < this->m_rowDiff; i++) {
        delete[] *(this->gridTemplateAreas + i);
    }
    this->gridTemplateAreas = new std::string*[this->m_rowDiff];
    for (int i = 0; i < this->m_rowDiff; i++) {
        *(this->gridTemplateAreas + i) = new std::string[this->m_columnDiff];
    }
    std::vector<std::string> rows = Utillity::splitString(areasTemplate, "/e");
    if ((rows.size() +1) == this->m_rowDiff) {
        for (int i = 0; i < this->m_rowDiff; i++) {
            std::vector<std::string> columns = Utillity::splitString(rows[i], ";");
            if ((columns.size() +1) == this->m_columnDiff) {
                for (int j = 0; j < this->m_columnDiff; j++) {
                    *(*(this->gridTemplateAreas + i) + j) = columns[j];
                }
                return true;
            }
            return false;
        }
    }
    return false;
}

bool Alignment::GridTemplate::m_checkUsabillity() const {
    bool usable{false};

    (!((this->m_rowDiff == 0) || (this->m_columnDiff == 0)) && 
     !((this->gridTemplateRows == nullptr) || (this->gridTemplateColumns == nullptr))) ? !usable : usable;

    return usable;
}

//#-- Definitions of UIComponents::Interactible
UIComponents::Interactible::Interactible() {
    for (unsigned int i = 0; i < 4; i++) {
        this->m_eventCallbackMap.insert(std::make_pair(static_cast<UIItemEventAction>(i), [&] (const sf::Event&) -> void {}));
    }
};
void UIComponents::Interactible::setOnMouseOver(GlobalEvents::ECallbackAttechment cb) 
{ this->m_eventCallbackMap[UIItemEventAction::MOUSEOVER] = cb; }

void UIComponents::Interactible::setOnMouseOut(GlobalEvents::ECallbackAttechment cb)
{ this->m_eventCallbackMap[UIItemEventAction::MOUSEOUT] = cb; }

void UIComponents::Interactible::setOnMouseDown(GlobalEvents::ECallbackAttechment cb)
{ this->m_eventCallbackMap[UIItemEventAction::MOUSEDOWN] = cb; }

void UIComponents::Interactible::setOnMouseUp(GlobalEvents::ECallbackAttechment cb)
{ this->m_eventCallbackMap[UIItemEventAction::MOUSEUP] = cb; }