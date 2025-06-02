#include "UIEngine.hpp"
#include <iomanip>

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
        }
    }
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
UIComponents::UIComponent::UIComponent(std::string id, sf::Vector2f relPos, UIConfig::UIStyleClass class_) :
m_id(id), m_relativePosition(relPos), m_defaultStyleClass(class_), m_overrideStyleClass(class_) {}

//#-- Definitions of UICContainer

UIComponents::UICContainer::UICContainer(std::string id, sf::Vector2f relPos, UIConfig::UIStyleClass class_) :
UIComponent(id, relPos, class_) {
    this->m_isContainer = true;
}

void UIComponents::UICContainer::appendChild(UIComponent* child) {
    //#-- get amount of childs
    size_t size = 0;
    UIComponent* curr_child = *this->m_childs;
    while (curr_child != nullptr) size++;
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

//#-- Definitions of UIConfig
UIConfig::UITheme::UITheme(std::string identifier, sf::Color primary, sf::Color secondary, std::tuple<unsigned int, unsigned int> scaleRange) {
    this->m_primaryAccentColorScales = new sf::Color[std::get<1>(scaleRange)];
    this->m_secondaryAccentColorScales = new sf::Color[std::get<1>(scaleRange)];
    this->m_grayscales = new sf::Color[std::get<1>(scaleRange)];
    //#-- generate scales
    this->m_generateScales(scaleRange, primary, this->m_primaryAccentColorScales);
    this->m_generateScales(scaleRange, secondary, this->m_secondaryAccentColorScales);
    this->m_generateScales(std::make_tuple(0, 10), sf::Color(255, 255, 255), this->m_grayscales);
    //#--
    this->m_identifier = identifier;
    this->m_scaleRange = scaleRange;

}

UIConfig::UITheme::~UITheme() {
    delete[] this->m_primaryAccentColorScales;
    delete[] this->m_secondaryAccentColorScales;
    delete[] this->m_grayscales;
}

bool UIConfig::UITheme::m_generateScales(std::tuple<unsigned int, unsigned int> range, sf::Color baseColor,  sf::Color* destination) {
    if (std::get<0>(range) > std::get<1>(range)) return false;
    unsigned int min = std::get<0>(range);
    unsigned int max = std::get<1>(range);
    for (int i = 1; i <= (max - min); i++) {
        float percentage = (static_cast<float>((max - min)) / 100) * i;
        int scaled_r_channel = std::floor(static_cast<float>(baseColor.r) * percentage);
        int scaled_g_channel = std::floor(static_cast<float>(baseColor.g) * percentage);
        int scaled_b_channel = std::floor(static_cast<float>(baseColor.b) * percentage);
        destination[i -1] = sf::Color(scaled_r_channel, 
                                      scaled_g_channel, 
                                      scaled_b_channel);

    }
    return true;
}

sf::Color UIConfig::UITheme::getPrimaryAccentColor(unsigned int scaleIndex) const {
    return this->m_primaryAccentColorScales[scaleIndex];
}

sf::Color UIConfig::UITheme::getSecondaryAccentColor(unsigned int scaleIndex) const {
    return this->m_secondaryAccentColorScales[scaleIndex];
}

sf::Color UIConfig::UITheme::getGrayScale(unsigned int scaleIndex) const {
    return this->m_grayscales[scaleIndex];
};

void UIConfig::UITheme::m_setDefaultColor(std::string id, UIThemeClrSet set, unsigned int scale) {
    sf::Color* colorSet{nullptr};
    switch (set) {
        case UIThemeClrSet::GRAYSCALES:
            colorSet = this->m_grayscales;
            break;
        case UIThemeClrSet::PRIM_C:
            colorSet = this->m_primaryAccentColorScales;
            break;
        case UIThemeClrSet::SECN_C:
            colorSet = this->m_secondaryAccentColorScales;
            break;
        default:
            colorSet = this->m_grayscales;
            break;
    }
    this->m_defaultColors.insert(std::make_pair(id, *(colorSet + scale)));
}

void UIConfig::UITheme::setDefaultBorderColor(UIThemeClrSet set, unsigned int scale) {
    this->m_setDefaultColor("border", set, scale);
}

void UIConfig::UITheme::setDefaultBackgroundColor(UIThemeClrSet set, unsigned int scale) {
    this->m_setDefaultColor("container-background", set, scale);
}

void UIConfig::UITheme::setDefaultFontColor(UIThemeClrSet set, unsigned int scale) {
    this->m_setDefaultColor("font", set, scale);
}

const std::unordered_map<std::string, sf::Color>& UIConfig::UITheme::getDefaultColors() const {
    return this->m_defaultColors;
}

void UIConfig::UITheme::represent() const {
    std::cout << std::endl << "[Representing UITheme]: " << this->m_identifier << std::endl;
    std::cout << std::left << std::setw(30) << "Primary Color"
              << std::left << std::setw(34) << "Secondary Color"
              << std::left << std::setw(24) << "Grayscales";
    std::cout << std::flush << "\n\n";
    
    for (int i = 0; i < (std::get<1>(this->m_scaleRange) - std::get<0>(this->m_scaleRange)); i++) {
        std::string pct = "( " + std::to_string(static_cast<unsigned int>((this->m_primaryAccentColorScales + i)->r)) + " | " + std::to_string(static_cast<unsigned int>((this->m_primaryAccentColorScales +i)->g)) + " | " + std::to_string(static_cast<unsigned int>((this->m_primaryAccentColorScales + i)->b)) + " )";
        std::string sct = "( " + std::to_string(static_cast<unsigned int>((this->m_secondaryAccentColorScales + i)->r)) + " | " + std::to_string(static_cast<unsigned int>((this->m_secondaryAccentColorScales +i)->g)) + " | " + std::to_string(static_cast<unsigned int>((this->m_secondaryAccentColorScales + i)->b)) + " )";
        std::string gcct = "( " + std::to_string(static_cast<unsigned int>((this->m_grayscales + i)->r)) + " | " + std::to_string(static_cast<unsigned int>((this->m_grayscales +i)->g)) + " | " + std::to_string(static_cast<unsigned int>((this->m_grayscales + i)->b)) + " )";
        std::cout << std::left << std::setw(30) << std::setfill(' ') << pct;
        std::cout << std::left << std::setw(34) << std::setfill(' ') << sct;
        std::cout << std::left << std::setw(24) << std::setfill(' ') << gcct << std::endl;
    }
    
}

//#-- Definitions of UIConfigurator
void UIConfig::UIConfigurator::addTheme(UITheme theme) {
    this->m_uiThemes.push_back(theme);
}

void UIConfig::UIConfigurator::addUIStyleClass(UIConfig::UIStyleClass uiStyleClass) {
    this->m_uiStyleClasses.push_back(uiStyleClass);
}

bool UIConfig::UIConfigurator::removeThemeByID(std::string id) {
    int idx{0};
    bool success{false};
    for (UITheme& themeObj : this->m_uiThemes) {
        if (themeObj.getName() == id) {
            success{true};
            break;
        }
        idx++;
    }
    this->m_uiThemes.erase(this->m_uiThemes.begin() + idx);
    return success;
}

bool UIConfig::UIConfigurator::removeUIStyleClassByID(std::string id) {
    int idx{0};
    bool success{false};
    for (UIStyleClass& styleClass : this->m_uiStyleClasses) {
        if (styleClass.name == id) {
            success{true};
            break;
        }
        idx++
    }
    this->m_uiStyleClasses.erase(this->m_uiStyleClasses.begin() + idx);
    return success;
}