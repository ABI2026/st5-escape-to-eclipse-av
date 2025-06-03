#ifndef ESCAPE_TO_ECLIPSE
#define ESCAPE_TO_ECLIPSE

#include "UIEngine.hpp"

namespace EscapeToEclipse {
    class GameUIConfig : public UIEngine::UIConfig::UIConfigurator {
        public:
            GameUIConfig() { 
                this.init(); 
            }
            ~GameUIConfig() = default;

            GameUIConfig operator=(GameUIConfig&) = delete;

            const GameUIConfig* getSingleton() {
                if (this->m_singletonInstance == nullptr)
                    this->m_singletonInstance = new GameUIConfig();
                
                return this->m_singletonInstance;
            }
            
            virtual void init() override;
        private:
            GameUIConfig* m_singletonInstance{nullptr};
    }
}

#endif //!ESCAPE_TO_ECLIPSE