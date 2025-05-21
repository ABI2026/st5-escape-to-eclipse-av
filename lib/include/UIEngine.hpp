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
                            Alignment::SelfAlign selfAlign)

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

                inline void setGridArea(std::string areaID) {
                    this->m_gridArea = areaID;
                }

                inline void setID(std::string id) {
                    this->m_id = id;
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

                [[nodiscard]] inline sf::Vector2f getDims() const {
                    return this->m_dims;
                }
                
                virtual void update_(GlobalEvents::GlobalHandler*) = 0;
                virtual void render() = 0;
            
            protected:
                sf::Vector2f m_relativePosition;
                sf::Vector2f m_dims;
                Alignment::Margin m_margin;
                Alignment::Margin m_padding;
                Alignment::SelfAlign m_selfAlignment;
                
                std::string m_gridArea{""};
                std::string m_id;

                bool visibillity{true};
                bool isInteractible{true};
        };

        class UICContainer : public UIComponent, public sf::RectangleShape {
            public:
                UICContainer() = default;

                UICContainer(std::string id, sf::Vector2f relPos, sf::Vector2f dims,
                            Alignment::Margin margin, Alignment::Margin padding,
                            Alignment::SelfAlign selfAlign, Alignment::InnerAlignment innerAlignmentMode)

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

                [[nodiscard]] inline UICContainer* getParent() const {
                    return this->m_parent;
                }

                [[nodiscard]] inline UICContainer* getChild() const {
                    return this->m_child;
                }

                inline void setParent(UICContainer* parent) const {
                    this->m_parent = parent;
                }

                

                [[nodiscard]] UIComponent& getUIItem(std::string id) const {
                    for (UIComponent& comp : this->m_uiItems) {
                        if (comp.id == id) {
                            return comp;
                        }
                    }
                }

                [[nodiscard]] std::vector<UIComponent>* getUIItems() const {
                    return this->m_uiItems;
                }

            protected:
                Alignment::InnerAlignment m_innerAlignmentMode;
                Alignment::GridTemplate m_alignmentMatrix;
                Alignment::FlexDirection m_flexDirection;
                Alignment::FlexJustifyContent m_justifyContentMode;
                Alignment::FlexAlignItems m_itemAlignment;

                UIComponent* m_parent;
                UIComponent* m_child[100]; // Maximum amount of childs


        };

    }
}

#endif