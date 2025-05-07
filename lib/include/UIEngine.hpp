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
        } Margin;
    
        typedef enum InnerAlignment : unsigned int {
            IA_FLEX,
            IA_GRID,
            IA_ABSOLUTE
        } InnerAlignment;
        
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

        typedef enum FlexAlignContent: unsigned int {
            AL_CENTER,
            AL_FLEXSTART,
            AL_FLEXEND
        } FlexAlignContent;

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
                Interactible(GlobalEvents::GlobalHandler*);
                Interactible& operator=(Interactible&) = delete;
                ~Interactible() = default;

                void setOnMouseOver(GlobalEvents::ECallbackAttechment);
                void setOnMouseOut(GlobalEvents::ECallbackAttechment);
                void setOnMouseDown(GlobalEvents::ECallbackAttechment);
                void setOnMouseUp(GlobalEvents::ECallbackAttechment);

            protected:
                std::unordered_map<UIItemEventAction, GlobalEvents::ECallbackAttechment> m_callbackMap;
                GlobalEvents::GlobalHandler* m_hnd;

                virtual void m_onMouseOver() = 0;
                virtual void m_onMouseOut() = 0;
                virtual void m_onMouseDown() = 0;
                virtual void m_onMouseUp() = 0;

        };
        class UIComponent : public sf::Drawable, public Interactible, public sf::Transformable {
            public:
                UIComponent() = default;
                UIComponent(GlobalEvents::GlobalHandler* p_hnd, sf::Vector2f relPos) : Interactible(p_hnd), Transformable(), m_relativePosition(relPos) {};

                inline void setRelativePosition(float x, float y) {
                    this->m_relativePosition.x = x;
                    this->m_relativePosition.y = y;
                };
            
            protected:
                sf::Vector2f m_relativePosition;
            private:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

        };
        class CascardingDIV : public UIComponent {

        };
    }
}

#endif UI_ENGINE