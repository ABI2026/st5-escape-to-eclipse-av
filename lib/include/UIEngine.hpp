#ifndef UI_ENGINE
#define UI_ENGINE

#include "framework_env.hpp"
#include "EventSystem.hpp"

#include "Utillity.h"

namespace UIEngine {

    typedef enum UIItemEventAction : unsigned int {
        MOUSEOVER = 0,
        MOUSEOUT = 1,
        MOUSEDOWN = 2,
        MOUSEUP = 3,
    } UIItemEventAction;

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
            IA_RELATIVE,
        } InnerAlignment;

        typedef enum SelfAlign : unsigned int {
            SA_RELATIVE
            SA_CENTER,
            SA_START,
            SA_END
        } SelfAlign;
        
        //#-- Flex settings
        typedef enum FlexDirection : unsigned int {
            D_ROW,
            D_COLUMN
        } FlexDirection;

        typedef enum FlexJustifyContent: unsigned int {
            J_SPACE_AROUND,
            J_SPACE_BETWEEN,
            J_CENTER,
            J_FLEXSTART,
            J_FLEXEND
        } FlexJustifyContent;

        typedef enum FlexAlignItems: unsigned int {
            AL_CENTER,
            AL_FLEXSTART,
            AL_FLEXEND
        } FlexAlignItems;

        //#-- Grid Settings
        typedef struct GridTemplate {
            sf::Vector2f* gridTemplateRows{nullptr};
            sf::Vector2f* gridTemplateColumns{nullptr};
            std::string** gridTemplateAreas{nullptr};

            //#-- Return value may be unused
            [[maybe_unused]] bool setGridRows(unsigned int, sf::Vector2f ...);
            [[maybe_unused]] bool setGridColumns(unsigned int, sf::Vector2f ...);
            [[maybe_unused]] bool setGridAreaIDs(std::string);

            [[nodiscard]] inline bool usable() const { return this->m_completed; }
            
            GridTemplate() = default;
            ~GridTemplate();
            private:

                [[nodiscard]] bool m_checkUsabillity() const;

                unsigned int m_rowDiff{0};
                unsigned int m_columnDiff{0};
                bool m_completed{false};

        } GridTemplate;
    }

    namespace UIConfig {
        //#-- Todo
    }
    namespace UIComponents {
        class Interactible {
            public:
                Interactible();
                Interactible& operator=(Interactible&) = delete;
                ~Interactible() = default;

                void setOnMouseOver(GlobalEvents::ECallbackAttechment);
                void setOnMouseOut(GlobalEvents::ECallbackAttechment);
                void setOnMouseDown(GlobalEvents::ECallbackAttechment);
                void setOnMouseUp(GlobalEvents::ECallbackAttechment);

            protected:
                std::unordered_map<UIItemEventAction, GlobalEvents::ECallbackAttechment> m_eventCallbackMap;
                GlobalEvents::GlobalHandler* m_hnd;

                virtual void m_onMouseOver() = 0;
                virtual void m_onMouseOut() = 0;
                virtual void m_onMouseDown() = 0;
                virtual void m_onMouseUp() = 0;

        };
        class UIComponent : public sf::Drawable, public sf::Transformable {
            public:
                UIComponent() = default;
                UIComponent() : Interactible(), Transformable() {};

                inline void setRelativePosition(float x, float y) {
                    this->m_relativePosition.x = x;
                    this->m_relativePosition.y = y;
                };

                inline void setSelfAlign(Alignment::SelfAlign selfAlignMode) { 
                    this->m_selfAlignment = selfAlignMode;
                }

                inline void setMargin(Alignment::Margin margin) {
                    this->m_margin = margin;
                }

                inline void setPadding(Alignment::Margin padding) {
                    this->m_padding = padding;
                }

                inline void setRelativePosition(sf::Vector2f relativePos) {
                    this->m_relativePosition = relativePos;
                }

                inline void setGridArea(std::string areaID) {
                    this->m_gridArea = areaID;
                }

                inline void setParentComponent(UIComponent* parent) {
                    this->m_parent = parent;
                }

                [[nodiscard]] inline sf::Vector2f getRelativePosition() const {
                    return this->m_relativePosition;
                }

                [[nodiscard]] inline Alignment::Margin getMargin() const {
                    return this->m_margin;
                }

                [[nodiscard]] inline Alignment::Margin getPadding() const {
                    return this->m_padding;
                }

                [[nodiscard]] inline Alignment::SelfAlign getSelfAlignMode() const {
                    return this->m_selfAlignment;
                }

                [[nodiscard]] inline std::string getGridArea() const {
                    return this->m_gridArea;
                }

                [[nodiscard]] inline UIComponent* getParentComponent() const {
                    return this->m_parent;
                }
            
            protected:
                sf::Vector2f m_relativePosition;
                Alignment::Margin m_margin;
                Alignment::Margin m_padding;
                Alignment::SelfAlign m_selfAlignment;

                std::string m_gridArea{""};

                UIComponent* m_parent{nullptr};

            private:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

        };

        class UIContainer : public UIComponent {

        }

        class UIItem : public UIComponent {

        }
    }
}

#endif UI_ENGINE