#include "UI/Config.hpp"

using namespace EscapeToEclipse;

//#-- Definitions of ETE-UIConfig

void UI::GameUIConfig::init() {
    //#-- Define UIThemes for Escape to Eclipse
    UIEngine::UIConfig::UITheme marsDirtTheme("Mars Dirt", sf::Color(235, 119, 52), sf::Color(255, 0, 0));
    UIEngine::UIConfig::UITheme hologramTheme("Hologram", sf::Color(0, 255, 255), sf::Color(0, 255, 165));
    UIEngine::UIConfig::UITheme darkRedTheme("Dark Red", sf::Color(255, 0, 0), sf::Color(255, 0, 98));
    UIEngine::UIConfig::UITheme uvHoloTheme("UV Hologram", sf::Color(132, 0, 255), sf::Color(0, 0, 255));

    marsDirtTheme.setDefaultBackgroundColor(UIEngine::UIConfig::UIThemeClrSet::SECN_C, 5);
    marsDirtTheme.setDefaultBorderColor(UIEngine::UIConfig::UIThemeClrSet::PRIM_C, 10);
    marsDirtTheme.setDefaultFontColor(UIEngine::UIConfig::UIThemeClrSet::GRAYSCALES, 10);

    hologramTheme.setDefaultBackgroundColor(UIEngine::UIConfig::UIThemeClrSet::SECN_C, 5);
    hologramTheme.setDefaultBorderColor(UIEngine::UIConfig::UIThemeClrSet::PRIM_C, 10);
    hologramTheme.setDefaultFontColor(UIEngine::UIConfig::UIThemeClrSet::PRIM_C, 7);

    darkRedTheme.setDefaultBackgroundColor(UIEngine::UIConfig::UIThemeClrSet::SECN_C, 2);
    darkRedTheme.setDefaultBorderColor(UIEngine::UIConfig::UIThemeClrSet::PRIM_C, 8);
    darkRedTheme.setDefaultFontColor(UIEngine::UIConfig::UIThemeClrSet::GRAYSCALES, 4);

    uvHoloTheme.setDefaultBackgroundColor(UIEngine::UIConfig::UIThemeClrSet::PRIM_C, 4);
    uvHoloTheme.setDefaultBorderColor(UIEngine::UIConfig::UIThemeClrSet::PRIM_C, 10);
    uvHoloTheme.setDefaultFontColor(UIEngine::UIConfig::UIThemeClrSet::PRIM_C, 7);
    
    this->addTheme(marsDirtTheme);
    this->addTheme(hologramTheme);
    this->addTheme(darkRedTheme);
    this->addTheme(uvHoloTheme);
    
}