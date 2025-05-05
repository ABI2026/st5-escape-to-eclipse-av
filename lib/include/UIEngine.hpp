#ifndef UI_ENGINE
#define UI_ENGINE

namespace UIEngine {
    /*namespace UIConfig {
        typedef std::array<std::array<sf::Color, 2>, 3> accentColorArray;
        typedef struct GeneralTheme {
            private:
                static sf::Color grayScaleLevels[8];
                sf::Color primaryAccentColors[2];
                sf::Color accentColorsScalesSolid[2][3];
                sf::Color accentColorsScalesTransparent[2][3];
                std::unordered_map<std::string, sf::Font> fontConfigList;
                float downScaleFactors[3] = { 0.7f, 0.5f, 0.3f };
            public:
                inline void addFontFamily(std::string, sf::Font);
                inline sf::Font getFontFamily(std::string identifier) { return this->fontConfigList[identifier]; }
                inline sf::Color getPrimaryAccentColor0() const { return this->primaryAccentColors[0]; }
                inline sf::Color getPrimaryAccentColor1() const { return this->primaryAccentColors[1]; }
                const accentColorArray getSolidAccentColorScales() const;
                const accentColorArray getTransparentAccentColorScales() const;
        
                GeneralTheme() = default;
                GeneralTheme(sf::Color firstPrimaryAccentColor, sf::Font headlineFont, 
                             sf::Font primaryFont, sf::Color secondPrimaryAccentColor = sf::Color(0x0)) 
                {
                    //#-- Set grayscale color scales
                    this->grayScaleLevels[0] = sf::Color(0, 0, 0, 255);
                    this->grayScaleLevels[1] = sf::Color(51, 51, 51, 255);
                    this->grayScaleLevels[2] = sf::Color(89, 89, 89, 255);
                    this->grayScaleLevels[3] = sf::Color(128, 128, 128, 255);
                    this->grayScaleLevels[4] = sf::Color(145, 145, 145, 255);
                    this->grayScaleLevels[5] = sf::Color(180, 180, 180, 255);
                    this->grayScaleLevels[6] = sf::Color(220, 220, 220, 255);
                    this->grayScaleLevels[7] = sf::Color(255, 255, 255, 255);
                    //#-- Set primary accent colors
                    this->primaryAccentColors[0] = firstPrimaryAccentColor;
                    this->primaryAccentColors[1] = secondPrimaryAccentColor;
                    //#-- Downscale brightness of colors for specific color scales
                    //#- solid
                    for (int accentColorIdx = 0; accentColorIdx < 2; accentColorIdx++) {
                        for (int colorScaleIdx = 0; colorScaleIdx < 3; colorScaleIdx++) {
                            this->accentColorsScalesSolid[accentColorIdx][colorScaleIdx] = sf::Color(
                                (this->primaryAccentColors[accentColorIdx].r * this->downScaleFactors[colorScaleIdx]),
                                (this->primaryAccentColors[accentColorIdx].g * this->downScaleFactors[colorScaleIdx]),
                                (this->primaryAccentColors[accentColorIdx].b * this->downScaleFactors[colorScaleIdx])
                            );
                        }
                    }
                    //#- transparent
                    for (int accentColorIdx = 0; accentColorIdx < 2; accentColorIdx++) {
                        for (int colorScaleIdx = 0; colorScaleIdx < 3; colorScaleIdx++) {
                            sf::Color currentAccentColor = this->primaryAccentColors[accentColorIdx];
                            currentAccentColor.a *= downScaleFactors[colorScaleIdx];
                            this->accentColorsScalesTransparent[accentColorIdx][colorScaleIdx] = currentAccentColor;
                        }
                    }
                    //#- set primary fonts
                    this->fontConfigList.insert({ "headline-font", headlineFont });
                    this->fontConfigList.insert({ "primary-font", primaryFont });
                }
            } GeneralTheme;
            
        class UIConfigurator {
            public:
                UIConfigurator() = default;
                UIConfigurator(const UIConfigurator&) = delete;
                UIConfigurator& operator=(const UIConfigurator&) = delete;
        
                bool loadFonts();

                static UIConfigurator* getSingleton() {
                    UIConfigurator* singletonInstance = new UIConfigurator();
                    return singletonInstance;
                }
        
                inline void addNewTheme(std::string, GeneralTheme*);
                inline void setCurrentTheme(std::string);
        
                [[nodiscard]] inline GeneralTheme* getCurrentTheme() const { return this->m_currentUITheme; }
                [[nodiscard]] inline sf::Font* getFontByID(std::string id) { return this->m_UIFonts[id]; }
        
            private:
                std::unordered_map<std::string, GeneralTheme*> m_uiThemes;
                std::unordered_map<std::string, sf::Font*> m_UIFonts;
                bool initSuccess = false;
                GeneralTheme* m_currentUITheme;
        };
    }*/
}

#endif UI_ENGINE