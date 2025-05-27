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
        /*template <typename Numeric>
        struct Vector {
            Numeric x;
            Numeric y;

            Vector(Numeric x, Numeric y) : x(x), y(y) {};
            Vector() = default;
        };

        template <typename Numeric>
        struct VectorTuple2d {
            Vector<Numeric> vector1;
            Vector<Numeric> vector2;

            VectorTuple2d(Vector<Numeric> first, Vector<Numeric> second) : vector1(first), vector2(second) {};
            VectorTuple2f() = default;
        }*/

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
        //#-- Todo
    }

    class UIOverlayManager {

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
            

        };
        class UIComponent {
            public:
                UIComponent() = default;
                UIComponent(std::string id, sf::Vector2f relPos, sf::Vector2f dims,
                            Alignment::Margin margin, Alignment::Margin padding,
                            Alignment::SelfAlign selfAlign);

                virtual ~UIComponent() = default;

                inline void setRelativePosition(float x, float y) {
                    this->m_relativePosition.x = x;
                    this->m_relativePosition.y = y;
                };

                inline void setRelativePosition(sf::Vector2f relPos) {
                    this->m_relativePosition = relPos;
                }

                inline void setSelfAlign(Alignment::SelfAlign selfAlignMode) { 
                    this->m_selfAlignment = selfAlignMode;
                }

                inline void setMargin(Alignment::Margin margin) {
                    this->m_margin = margin;
                }

                inline void setPadding(Alignment::Margin padding) {
                    this->m_padding = padding;
                }

                inline void setDimensions(sf::Vector2f dims) {
                    this->m_dims = dims;
                };

                inline void setGridArea(float row, float column) {
                    this->m_gridArea[0] = row;
                    this->m_gridArea[1] = column;
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

                [[nodiscard]] inline Alignment::Margin getMargin() const {
                    return this->m_margin;
                }

                [[nodiscard]] inline Alignment::Margin getPadding() const {
                    return this->m_padding;
                }

                [[nodiscard]] inline Alignment::SelfAlign getSelfAlignMode() const {
                    return this->m_selfAlignment;
                }

                [[nodiscard]] inline const float* getGridArea() const {
                    return this->m_gridArea;
                }

                [[nodiscard]] inline sf::Vector2f getDims() const {
                    return this->m_dims;
                }
                
                //virtual void update_(GlobalEvents::GlobalHandler*) = 0;
                virtual void render(sf::RenderWindow*) = 0;
            
            protected:
                Alignment::Margin m_margin;
                Alignment::Margin m_padding;
                Alignment::SelfAlign m_selfAlignment;
                
                sf::Vector2f m_relativePosition;
                sf::Vector2f m_dims;

                
                float m_gridArea[2];
                std::string m_id;

                bool m_visibillity{true};
                bool m_isContainer{false};
                bool m_isInteractible{false};
        };

        class UICContainer : public UIComponent, public sf::RectangleShape {
            public:
                UICContainer() = default;

                UICContainer(std::string id, sf::Vector2f relPos, sf::Vector2f dims,
                            Alignment::Margin margin, Alignment::Margin padding,
                            Alignment::SelfAlign selfAlign, Alignment::InnerAlignment innerAlignmentMode);

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

                [[nodiscard]] inline UICContainer* getParent() const {
                    return this->m_parent;
                }

                inline void setParent(UICContainer* parent)  {
                    this->m_parent = parent;
                }

                inline void setInnerAlignmentMode(Alignment::InnerAlignment innerAlignmentMode) {
                    this->m_innerAlignmentMode = innerAlignmentMode;
                }

                inline void deployGridTemplate(Alignment::GridTemplate& grid) {
                    this->m_alignmentMatrix = grid;
                }

                void appendChild(UIComponent*);

                void justifyFlex();
                void justifyGrid();
                void justifyRelative();

                virtual void render(sf::RenderWindow*) override;

            protected:
                Alignment::InnerAlignment m_innerAlignmentMode;
                Alignment::GridTemplate m_alignmentMatrix;
                Alignment::FlexDirection m_flexDirection;
                Alignment::FlexJustifyContent m_justifyContentMode;
                Alignment::FlexAlignItems m_itemAlignment;

                UICContainer* m_parent;
                UIComponent* m_childs[100]; // Maximum amount of childs
        };

    }
}

#endif