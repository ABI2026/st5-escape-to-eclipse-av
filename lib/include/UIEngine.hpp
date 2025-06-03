#ifndef UI_ENGINE
#define UI_ENGINE

#include "framework_env.hpp"

//#-- Foreward
namespace GlobalEvents {
    using ECallbackAttechment = std::function<void(const sf::Event&)>;
}

#include "Utillity.hpp"

namespace UIEngine {

    typedef enum UIItemEventAction : unsigned int {
        MOUSEOVER = 0,
        MOUSEOUT = 1,
        MOUSEDOWN = 2,
        MOUSEUP = 3,
    } UIItemEventAction;

    //#-- Foreward
    namespace UIComponents {
        class UIOverlay;
    }

    namespace Alignment {
        typedef struct Margin {
            float left;
            float right;
            float top;
            float bottom;

            Margin(float t, float r, float b, float l) :
            left(l), right(r), top(t), bottom(b) {};
            Margin() = default;
        } Margin;
    
        typedef enum InnerAlignment : unsigned int {
            IA_FLEX,
            IA_GRID,
            IA_RELATIVE
        } InnerAlignment;

        typedef enum SelfAlign : unsigned int {
            SA_RELATIVE,
            SA_CENTER,
            SA_START,
            SA_END,
            SA_NO_OVERRIDE
        } SelfAlign;
        
        //#-- Flex settings
        typedef enum FlexDirection : unsigned int {
            D_ROW,
            D_COLUMN,
            D_DEFAULT,
        } FlexDirection;

        typedef enum FlexJustifyContent: unsigned int {
            J_SPACE_AROUND,
            J_SPACE_BETWEEN,
            J_CENTER,
            J_FLEXSTART,
            J_FLEXEND,
            J_DEFAULT,
        } FlexJustifyContent;

        typedef enum FlexAlignItems: unsigned int {
            AL_CENTER,
            AL_FLEXSTART,
            AL_FLEXEND,
            AL_DEFAULT,
        } FlexAlignItems;

        //#-- Grid Settings
        typedef struct GridTemplate {
            public:                
                
                GridTemplate() = default;
                GridTemplate(unsigned int, unsigned int);
                ~GridTemplate();

                void setGridRows(unsigned int, ...);
                void setGridColumns(unsigned int, ...);

                [[nodiscard]] std::array<sf::Vector2f, 2> getLimitPointForArea(int, int) const;
            
            private:
                float* m_gridTemplateRows{nullptr};
                float* m_gridTemplateColumns{nullptr};

                sf::Vector2f** m_representationMatrix{nullptr};

                void mf_generateReprMatrix();

                unsigned int m_rowDiv{1};
                unsigned int m_columnDiv{1};

        } GridTemplate;
    }

    namespace UIConfig {
        typedef enum UIThemeClrSet {
            GRAYSCALES,
            PRIM_C,
            SECN_C
        } UIThemeClrSet;

        typedef struct UIStyleClass {
            sf::Vector2f dims;
            UIEngine::Alignment::Margin margin = Alignment::Margin(0, 0, 0, 0);
            UIEngine::Alignment::Margin padding = Alignment::Margin(0, 0, 0, 0);
            UIEngine::Alignment::SelfAlign selfAlign = UIEngine::Alignment::SelfAlign::SA_NO_OVERRIDE;
            
            sf::Color borderColor = sf::Color(0, 0, 0);
            sf::Color backgroundColor = sf::Color(0, 0, 0);
            sf::Color textColor = sf::Color(0, 0, 0);

            unsigned int gridArea[2];

            std::string name;

            UIStyleClass(std::string name) : name(name) {}
            UIStyleClass() = default;
        } UIStyleClass;

        typedef struct UICContainerStyleClass : public UIStyleClass {
            UIEngine::Alignment::InnerAlignment innerAlignmentMode = UIEngine::Alignment::InnerAlignment::IA_RELATIVE;
            UIEngine::Alignment::FlexDirection flexDirection = UIEngine::Alignment::FlexDirection::D_DEFAULT;
            UIEngine::Alignment::FlexJustifyContent justifyContent = UIEngine::Alignment::FlexJustifyContent::J_DEFAULT;
            UIEngine::Alignment::FlexAlignItems alignItems = UIEngine::Alignment::FlexAlignItems::AL_DEFAULT;

            UIEngine::Alignment::GridTemplate grid{};

            UICContainerStyleClass() = default;
            UICContainerStyleClass(std::string name) : UIStyleClass(name) {}
        } UICContainerStyleClass;

        typedef struct UITheme {
            /*
                @info
                Getting default colors by thw following IDs: 
                    - border
                    - container-background
                    - font
            */
            public:
                UITheme() = default;
                UITheme(std::string, sf::Color, sf::Color, std::tuple<unsigned int, unsigned int> = std::make_tuple(0, 10));

                ~UITheme() = default;

                [[nodiscard]] sf::Color getPrimaryAccentColor(unsigned int) const;
                [[nodiscard]] sf::Color getSecondaryAccentColor(unsigned int) const;
                [[nodiscard]] sf::Color getGrayScale(unsigned int) const;

                void setDefaultBorderColor(UIThemeClrSet, unsigned int);
                void setDefaultBackgroundColor(UIThemeClrSet, unsigned int);
                void setDefaultFontColor(UIThemeClrSet, unsigned int);

                [[nodiscard]] const std::unordered_map<std::string, sf::Color>& getDefaultColors() const;
                void represent() const;

                inline const std::string getName() const {
                    return this->m_identifier;
                }

                static const sf::Color error;
                static const sf::Color warn;
                static const sf::Color success;
                static const sf::Color perimtted;

            private:

                bool m_generateScales(std::tuple<unsigned int, unsigned int>, sf::Color, std::vector<sf::Color>&);
                void m_setDefaultColor(std::string, UIThemeClrSet, unsigned int);

                std::vector<sf::Color> m_primaryAccentColorScales;
                std::vector<sf::Color> m_secondaryAccentColorScales;
                std::vector<sf::Color> m_grayscales;
                std::string m_identifier;
                std::tuple<unsigned int, unsigned int> m_scaleRange;

                std::unordered_map<std::string, sf::Color> m_defaultColors;

        } UITheme;

        class UIConfigurator {
            public:
                UIConfigurator() = default;
                virtual ~UIConfigurator() = default;

                void addTheme(UITheme);
                void setCurrentTheme(std::string);
                
                [[nodiscard]] UITheme getUIThemeByID(std::string);
                [[nodiscard]] UITheme getCurrentTheme();

                virtual void init() = 0;
            protected:
                std::unordered_map<std::string, UITheme> m_uiThemes;

                std::string m_currentTheme{"Hologram"};
        };
    }

    class UIOverlayManager {
        public:
            UIOverlayManager(sf::RenderWindow*, UIConfig::UIConfigurator*);
            ~UIOverlayManager();

            void render();
            void navigate(std::string);

            void appendUIOverlay(UIComponents::UIOverlay*);

            void setRessourcesPath(std::string path) {
                this->m_ressourcesPath = path;
            }

        private:
            sf::RenderWindow* m_window;
            UIConfig::UIConfigurator* m_uiConfig{nullptr};

            UIComponents::UIOverlay* m_uiOverlaysHead;

            std::string m_ressourcesPath;
    };

    namespace UIComponents {
        class Interactible {
            public:
                Interactible();
                virtual ~Interactible() = default;

                void setOnMouseOver(GlobalEvents::ECallbackAttechment);
                void setOnMouseOut(GlobalEvents::ECallbackAttechment);
                void setOnMouseDown(GlobalEvents::ECallbackAttechment);
                void setOnMouseUp(GlobalEvents::ECallbackAttechment);

            protected:
                std::unordered_map<UIItemEventAction, GlobalEvents::ECallbackAttechment> m_eventCallbackMap;

                virtual void m_onMouseOver() = 0;
                virtual void m_onMouseOut() = 0;
                virtual void m_onMouseDown() = 0;
                virtual void m_onMouseUp() = 0;

        };
        class UIOverlay {
            public:
                UIOverlay(std::string, std::string);
                virtual ~UIOverlay() = default;

                void setBackground(std::string);

                virtual void render() = 0;

            private:
                std::string m_navigationID;
                sf::Texture m_background;
                
        };
        class UIComponent {
            public:
                UIComponent() = default;
                UIComponent(std::string, sf::Vector2f, UIConfig::UITheme&);

                virtual ~UIComponent() = default;

                inline void setRelativePosition(float x, float y) {
                    this->m_relativePosition.x = x;
                    this->m_relativePosition.y = y;
                }

                inline void setRelativePosition(sf::Vector2f relPos) {
                    this->m_relativePosition = relPos;
                }

                inline void setID(std::string id) { 
                    this->m_id = id; 
                }

                inline void setVisible() { this->m_visibillity = true; }
                inline void setHidden() { this->m_visibillity = false; }

                [[nodiscard]] inline bool isVisible() {return this->m_visibillity;}

                [[nodiscard]] bool isContainer() { this->m_isContainer; }
                [[nodiscard]] bool isInteractible() { this->m_isInteractible; }

                [[nodiscard]] inline sf::Vector2f getRelativePosition() const {
                    return this->m_relativePosition;
                }
                
                //virtual void update_(GlobalEvents::GlobalHandler*) = 0;
                virtual void render(sf::RenderWindow*) = 0;
            
            protected:
                
                sf::Vector2f m_relativePosition;
                std::string m_id;
                UIConfig::UITheme& m_colorTheme;

                bool m_visibillity{true};
                bool m_isContainer{false};
                bool m_isInteractible{false};
        };

        class UICContainer : public UIComponent, public sf::RectangleShape {
            public:

                UICContainer() = default;
                UICContainer(std::string id, sf::Vector2f relPos, UIConfig::UITheme&);

                virtual ~UICContainer() = default;


                [[nodiscard]] inline UICContainer* getParent() const {
                    return this->m_parent;
                }

                inline void setParent(UICContainer* parent)  {
                    this->m_parent = parent;
                }

                void appendChild(UIComponent*);

                void justifyFlex();
                void justifyGrid();
                void justifyRelative();

                virtual void render(sf::RenderWindow*) override;

            protected:
                UIConfig::UICContainerStyleClass style;
                UICContainer* m_parent;
                UIComponent* m_childs[100]; // Maximum amount of childs
        };

    }
}

#endif