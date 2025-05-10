#ifndef UI_ENGINE
#define UI_ENGINE

#include "framework_env.hpp"
#include "EventSystem.hpp"

#include "Utillity.hpp"

namespace UIEngine {

    typedef enum UIItemEventAction : unsigned int {
        MOUSEOVER = 0,
        MOUSEOUT = 1,
        MOUSEDOWN = 2,
        MOUSEUP = 3,
    } UIItemEventAction;

    namespace Alignment {
        template <typename Numeric>
        struct Vector {
            Numeric x;
            Numeric y;

            Vector(Numeric x, Numeric y) : x(x), y(y) {};
            Vector() = default;
        };

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
            Alignment::Vector<float>* gridTemplateRows{nullptr};
            Alignment::Vector<float>* gridTemplateColumns{nullptr};
            std::string** gridTemplateAreas{nullptr};

            //#-- Return value may be unused
            [[maybe_unused]] bool setGridRows(unsigned int, Alignment::Vector<float> ...);
            [[maybe_unused]] bool setGridColumns(unsigned int, Alignment::Vector<float>  ...);
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
                virtual ~Interactible() = default;

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
        class UIComponent : public sf::Drawable {
            public:
                UIComponent() = default;

                virtual ~UIComponent() = default;

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
                
                //virtual void update(GlobalEvents::GlobalHandler*) = 0;
            
            protected:
                sf::Vector2f m_relativePosition;
                Alignment::Margin m_margin;
                Alignment::Margin m_padding;
                Alignment::SelfAlign m_selfAlignment;

                std::string m_gridArea{""};

                UIComponent* m_parent{nullptr};

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
        };

        class UICContainer : public UIComponent {
            public:

                virtual ~UICContainer() = default;

                [[nodiscard]] inline Alignment::GridTemplate getAlignmentMatrix() const {
                    return this->m_alignmentMatrix;
                }

                [[nodiscard]] inline Alignment::FlexDirection getFlexDirection() const {
                    return this->m_flexDirection;
                }  

                [[nodiscard]] inline Alignment::FlexJustifyContent getContentJustification() const {
                    return this->m_justifyContentMode;
                }

                [[nodiscard]] inline Alignment::FlexAlignItems getItemAlignment() const {
                    return this->m_itemAlignment;
                }

                [[nodiscard]] inline sf::RectangleShape getShape() const {
                    return this->m_shape;
                }

            protected:
                Alignment::GridTemplate m_alignmentMatrix;
                Alignment::FlexDirection m_flexDirection;
                Alignment::FlexJustifyContent m_justifyContentMode;
                Alignment::FlexAlignItems m_itemAlignment;

                sf::RectangleShape m_shape;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        };

        class UIItem : public UIComponent {

        };
    }
}

#endif