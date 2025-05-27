#include "UIEngine.hpp"

#ifndef UI_TEMPLATES
#define UI_TEMPLATES

namespace UITemplates {
    class UIButton : public UIComponent, public Interactible, public sf::RectangleShape {
        public:
            UIButton() = default;
            UIButton();
        private:

    }
}

#endif //!UI-Templates