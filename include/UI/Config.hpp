#pragma once
#include "UIEngine.hpp"

namespace EscapeToEclipse {
    namespace UI {
        class GameUIConfig : public UIEngine::UIConfig::UIConfigurator {
            public:
                GameUIConfig() { 
                    this->init(); 
                }
                ~GameUIConfig() = default;

                GameUIConfig operator=(const GameUIConfig&) = delete;

                static GameUIConfig getSingleton() {
                    static GameUIConfig instance;
                    return instance;
                }
            
                virtual void init() override;
        };

        
    }
}