#include "UIEngine.hpp"

using namespace UIEngine;

//#-- Definitions of UIAlignment Tools

Alignment::GridTemplate::GridTemplate(unsigned int rowDiv, unsigned int columnDiv) {
    (rowDiv == 0) ? this->m_rowDiv = 1 : this->m_rowDiv = rowDiv+1;
    (columnDiv == 0) ? this->m_columnDiv = 1 : this->m_columnDiv = columnDiv+1;
    //#-- Fill with zeros for 1d models
    this->m_gridTemplateRows = new float[this->m_rowDiv];
    this->m_gridTemplateColumns = new float[this->m_columnDiv];
    for (int i = 0; i < this->m_rowDiv; i++) *(this->m_gridTemplateRows + i) = 0;
    for (int i = 0; i < this->m_columnDiv; i++) *(this->m_gridTemplateColumns + i) = 0;
}

Alignment::GridTemplate::~GridTemplate() {
    delete[] this->m_gridTemplateColumns;
    delete[] this->m_gridTemplateRows;
    for (int i = 0; i < this->m_rowDiv; i++) {
        delete[] *(this->m_representationMatrix + i);
    }
}

void Alignment::GridTemplate::setGridRows(unsigned int rowDiv, ...) {
    rowDiv = rowDiv +1;
    this->m_rowDiv = rowDiv;
    va_list args;
    va_start(args, rowDiv);

    delete[] this->m_gridTemplateRows;
    this->m_gridTemplateRows = nullptr;

    this->m_gridTemplateRows = new float[this->m_rowDiv];
    this->m_gridTemplateRows[0] = 0.f;
    
    float sum = 0;
    for (int i = 1; i < this->m_rowDiv; i++) {
        float curr_rowdiv_lp = va_arg(args, double);
        sum += curr_rowdiv_lp;
        *(this->m_gridTemplateRows + i) = sum;
    }

    this->mf_generateReprMatrix();
    va_end(args);
}

void Alignment::GridTemplate::setGridColumns(unsigned int columnDiv, ...) {
    columnDiv = columnDiv+1;
    this->m_columnDiv = columnDiv;
    va_list args;
    va_start(args, columnDiv);

    delete[] this->m_gridTemplateColumns;
    this->m_gridTemplateColumns = nullptr;

    this->m_gridTemplateColumns = new float[this->m_columnDiv];
    this->m_gridTemplateColumns[0] = 0.f;
    
    float sum = 0;
    for (int i = 1; i < this->m_columnDiv; i++) {
        float curr_columndiv_lp = va_arg(args, double);
        sum += curr_columndiv_lp;
        *(this->m_gridTemplateColumns +i) = sum;
    }

    this->mf_generateReprMatrix();
    va_end(args);
}

void Alignment::GridTemplate::mf_generateReprMatrix() {
    this->m_representationMatrix = new sf::Vector2f*[this->m_rowDiv];
    int i = 0;
    do {
        *(this->m_representationMatrix +i) = new sf::Vector2f[this->m_columnDiv];
        int j = 0;
        do {
            sf::Vector2f v = sf::Vector2f(*(this->m_gridTemplateRows + i), *(this->m_gridTemplateColumns + j));
            *(*(this->m_representationMatrix + i) + j) = v;
            j++;
        } while (j < this->m_columnDiv);
        i++;
    } while (i < this->m_rowDiv);

    for (int i = 0; i < this->m_rowDiv; i++) {
        for (int j = 0; j < this->m_columnDiv; j++) {
            sf::Vector2f v = *(*(this->m_representationMatrix + i) + j);
            //std::cout << '(' << v.x << " | " << v.y << ") ";
        }
        //std::cout << std::endl;
    }
    //std::cout << "\n" << "<------------------->" << std::endl;
}

std::array<sf::Vector2f, 2> Alignment::GridTemplate::getLimitPointForArea(int row, int column) const {
    //#-- Todo: Out of index error handling
    //...........
    std::array<sf::Vector2f, 2> area_lpts = {*(*(this->m_representationMatrix + row) + column),
                                             *(*(this->m_representationMatrix + (row+1)) + (column+1))};
    return area_lpts;
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

//#-- Definition of abstract UIComponent
UIComponents::UIComponent::UIComponent(std::string id, sf::Vector2f relPos, sf::Vector2f dims,
                            Alignment::Margin margin, Alignment::Margin padding,
                            Alignment::SelfAlign selfAlign) {
    setID(id);
    setRelativePosition(relPos);
    setDimensions(dims);
    setMargin(margin);
    setPadding(padding);
    setSelfAlign(selfAlign);
}

//#-- Definitions of UICContainer

UIComponents::UICContainer::UICContainer(std::string id, sf::Vector2f relPos, sf::Vector2f dims,
                            Alignment::Margin margin, Alignment::Margin padding,
                            Alignment::SelfAlign selfAlign, Alignment::InnerAlignment innerAlignmentMode) :

UIComponent(id, relPos, dims, margin, padding, selfAlign) {
    this->m_innerAlignmentMode = innerAlignmentMode;
    this->setSize(dims);
    this->m_isContainer = true;
    this->setPosition(this->m_relativePosition);
}

void UIComponents::UICContainer::appendChild(UIComponent* child) {
    //#-- get amount of childs
    size_t size = 0;
    UIComponent* curr_child = *this->m_childs;
    while (curr_child != nullptr) count++;
    //#-- append child
    *(this->m_childs + (size-1)) = child;
}

void UIComponents::UICContainer::render(sf::RenderWindow* window) {
    /*if (this->m_isContainer) {
        switch (this->m_innerAlignmentMode) {
            case UIEngine::Alignment::InnerAlignment::IA_FLEX:
                this->m_justifyFlex();
                break;
            case UIEngine::Alignment::InnerAlignment::IA_GRID:
                this->m_justifyGrid();
                break;
            case UIEngine::Alignment::InnerAlignment::IA_RELATIVE:
                this->m_justifyRelative();
                break;
            default:
                this->m_justifyRelative();
                break;
        }
    }*/
    if (this->m_visibillity) window->draw(*this);
    //#-- call render method of childs
    /*UIComponent* nextChild = this->m_childs;
    while (nextChild != nullptr) {
        nextChild->render();
        nextChild = nextChild +1;
    }*/
}

