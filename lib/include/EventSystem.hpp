#ifndef GlobalEventHandler
#define GlobalEventHander

#include "framework_env.hpp"

namespace GlobalEvents {
	using ECallbackAttechment = std::function<void(const sf::Event&)>;

	template <typename evt_type>
	using EventCallMapSet = std::unordered_map<evt_type, std::vector<ECallbackAttechment>>;

	template <typename evt_type>
	using EventCallMap = std::unordered_map<evt_type, ECallbackAttechment>;

	typedef enum UIEventAction : unsigned char {
		NONE,
		PRESSED,
		RELEASED
	} UIEventAction;
	
	/*
		@brief class "SubTypeHandler"
		----------------------------------
		SubTypeHandler class is a subclass to handle sub events of 
		an upper event class. Example: sf::Keyboard::KeyPressed -> sf::Keyboard::Key

		Also supporting a set of callback functions for a single 
		event sub type
		----------------------------------
	*/
	template <typename EvtSubType>
	class SubTypeHandler {
	public:
		SubTypeHandler(std::function<EvtSubType(const sf::Event&)>);
		SubTypeHandler() = default;
		~SubTypeHandler() = default;

		void addSingleCallback(EvtSubType, ECallbackAttechment);
		void addCallbackToMultiSet(EvtSubType, ECallbackAttechment);
		void removeSingleCallback(EvtSubType);
		void resetCallbackMultiset();
		void resetCallbackSingleSet();
		void removeCallbackSet(EvtSubType);
		void processEvents(const sf::Event&);
		void reset();

	private:
		EventCallMap<EvtSubType> m_callmap{};
		EventCallMapSet<EvtSubType> m_callmapSet{};
		std::function<EvtSubType(const sf::Event&)> m_eventDeconstructor;
	};
	/*
		@brief class "GlobalHandler"
		------------------------------
		GlobalEvents::GlobalHandler is used to add new callbacks to
		specific subevents
		------------------------------
	*/
	class GlobalHandler {
	public:
		GlobalHandler(sf::RenderWindow*);
		~GlobalHandler() = default;

		void pollAndExecuteEvents();
		void attachStandardWindowEventCallback(sf::Event::EventType, ECallbackAttechment);

		void attachToKeyCallbackMultiset(sf::Event::EventType, sf::Keyboard::Key, ECallbackAttechment);
		void attachToMouseCallbackMultiset(sf::Event::EventType, sf::Mouse::Button, ECallbackAttechment);

		void reset();

		void deleteCallbackSet(sf::Event::EventType, sf::Keyboard::Key);
		void deleteCallbackSet(sf::Event::EventType, sf::Mouse::Button);

		void deployActionMappingList(unsigned int, sf::Keyboard::Key ...);
		void deployActionMappingList(unsigned int, sf::Mouse::Button ...);

		[[nodiscard]] inline UIEventAction getUIActionState(sf::Keyboard::Key key) {
			return this->m_keyActionMap[key];
		}

		[[nodiscard]] inline UIEventAction getUIActionState(sf::Mouse::Button btn) {
			return this->m_mouseButtonActionMap[btn];
		}

	private:
		sf::RenderWindow* m_window = nullptr;
		SubTypeHandler<sf::Keyboard::Key> m_keyPressedSTHandler;
		SubTypeHandler<sf::Keyboard::Key> m_keyReleasedSTHandler;
		SubTypeHandler<sf::Mouse::Button> m_mouseButtonPressedSTHandler;
		SubTypeHandler<sf::Mouse::Button> m_mouseButtonReleasedSTHandler;
		EventCallMap<sf::Event::EventType> m_wrapperCallmap;
		
		sf::Vector2f m_currentMousePosition{};
		std::unordered_map<sf::Mouse::Button, UIEventAction> m_mouseButtonActionMap;
		std::unordered_map<sf::Keyboard::Key, UIEventAction> m_keyActionMap;

		template <typename EvtCallbackType>
		SubTypeHandler<EvtCallbackType>* m_evaluateSubTypeHandler(sf::Event::EventType action) {
			void* subtypehandler = nullptr;
			if (typeid(EvtCallbackType) == typeid(sf::Mouse::Button)) {
				switch (action) {
				case sf::Event::EventType::MouseButtonPressed:
					subtypehandler = &this->m_mouseButtonPressedSTHandler;
					break;
				case sf::Event::EventType::MouseButtonReleased:
					subtypehandler = &this->m_mouseButtonReleasedSTHandler;
					break;
				default:
					break;
				}
			}
			else if (typeid(EvtCallbackType) == typeid(sf::Keyboard::Key)) {
				switch (action) {
				case sf::Event::EventType::KeyPressed:
					subtypehandler = &this->m_keyPressedSTHandler;
					break;
				case sf::Event::EventType::KeyReleased:
					subtypehandler = &this->m_keyReleasedSTHandler;
					break;
				default:
					break;
				}
			}
			if (subtypehandler) {
				return reinterpret_cast<SubTypeHandler<EvtCallbackType>*>(subtypehandler);
			}
			return nullptr;
		}

		void m_attachSingleKeyCallback(sf::Event::EventType, sf::Keyboard::Key, ECallbackAttechment);
		void m_attachSingleMouseButtonCallback(sf::Event::EventType, sf::Mouse::Button, ECallbackAttechment);
		void m_deleteSingleEvent(sf::Event::EventType, sf::Keyboard::Key);
		void m_deleteSingleEvent(sf::Event::EventType, sf::Mouse::Button);
	};
}

//#-- Explicit template types definition
extern template class GlobalEvents::SubTypeHandler<sf::Event::EventType>;
extern template class GlobalEvents::SubTypeHandler<sf::Keyboard::Key>;
extern template class GlobalEvents::SubTypeHandler<sf::Mouse::Button>;

#endif // !GlobalEventHandler