#include "EventSystem.hpp"

//#-- Explicit template types definition
template class GlobalEvents::SubTypeHandler<sf::Event::EventType>;
template class GlobalEvents::SubTypeHandler<sf::Keyboard::Key>;
template class GlobalEvents::SubTypeHandler<sf::Mouse::Button>;

//#-- SubTypeHandler Definitions
template <typename EvtSubType>
GlobalEvents::SubTypeHandler<EvtSubType>::SubTypeHandler(std::function<EvtSubType(const sf::Event&)> eventDeconstructor) 
	: m_eventDeconstructor(eventDeconstructor) {};

template <typename EvtSubType>
void GlobalEvents::SubTypeHandler<EvtSubType>::addCallback(EvtSubType subtype, ECallbackAttechment callback) {
	this->m_callmap.insert(std::make_pair(subtype, callback));
}

template <typename EvtSubType>
void GlobalEvents::SubTypeHandler<EvtSubType>::addCallbackToMultiSet(EvtSubType subtype, ECallbackAttechment callback) {
	this->m_callmapSet[subtype].push_back(callback);
}

template <typename EvtSubType>
void GlobalEvents::SubTypeHandler<EvtSubType>::removeCallback(EvtSubType subtype) {
	this->m_callmap.erase(subtype);
}

template <typename EvtSubType>
void GlobalEvents::SubTypeHandler<EvtSubType>::processEvents(const sf::Event& ev) {
	EvtSubType subval = this->m_eventDeconstructor(ev);
	auto attachtedCallbackPair = this->m_callmap.find(subval);
	if (attachtedCallbackPair != this->m_callmap.end())
		(attachtedCallbackPair->second)(ev);
	//#-- Also execute all functions from callback multiset
	auto attachedCallbackFunctionSet = this->m_callmapSet.find(subval);
	if (attachedCallbackFunctionSet != this->m_callmapSet.end()) {
		for (auto& callback : attachedCallbackFunctionSet->second) {
			(callback)(ev);
		}
	}
}

template<typename EvtSubType>
void GlobalEvents::SubTypeHandler<EvtSubType>::reset() {
	this->m_callmap.clear();
	this->m_callmapSet.clear();
}

template<typename EvtSubType>
void GlobalEvents::SubTypeHandler<EvtSubType>::resetCallbackMultiset() {
	this->m_callmapSet.clear();
}

template <typename EvtSubType>
void GlobalEvents::SubTypeHandler<EvtSubType>::resetCallbackSingleSet() {
	this->m_callmap.clear();
}

template <typename EvtSubType>
void GlobalEvents::SubTypeHandler<EvtSubType>::removeCallbackSet(EvtSubType subtype) {
	this->m_callmapSet.erase(subtype);
}

//#-- GlobalHandler Definitions
static std::function<sf::Keyboard::Key(const sf::Event&)> keyActionEventDeconstructorCallback = [](const sf::Event& ev) -> sf::Keyboard::Key {
	return ev.key.code;
};

static std::function<sf::Mouse::Button(const sf::Event&)> mouseButtonActionEventDeconstructorCallback = [](const sf::Event& ev) -> sf::Mouse::Button {
	return ev.mouseButton.button;
};

GlobalEvents::GlobalHandler::GlobalHandler(sf::RenderWindow* window)
	: m_keyPressedSTHandler(GlobalEvents::SubTypeHandler<sf::Keyboard::Key>(keyActionEventDeconstructorCallback)),
	m_keyReleasedSTHandler(GlobalEvents::SubTypeHandler<sf::Keyboard::Key>(keyActionEventDeconstructorCallback)),
	m_mouseButtonPressedSTHandler(GlobalEvents::SubTypeHandler<sf::Mouse::Button>(mouseButtonActionEventDeconstructorCallback)),
	m_mouseButtonReleasedSTHandler(GlobalEvents::SubTypeHandler<sf::Mouse::Button>(mouseButtonActionEventDeconstructorCallback)),
	m_window(window)
{
	this->m_wrapperCallmap.insert({ sf::Event::KeyPressed, [&](const sf::Event& ev) -> void { this->m_keyPressedSTHandler.processEvents(ev); } });
	this->m_wrapperCallmap.insert({ sf::Event::KeyReleased, [&](const sf::Event& ev) -> void { this->m_keyReleasedSTHandler.processEvents(ev); } });
	this->m_wrapperCallmap.insert({ sf::Event::MouseButtonPressed, [&](const sf::Event& ev) -> void { this->m_mouseButtonPressedSTHandler.processEvents(ev); } });
	this->m_wrapperCallmap.insert({ sf::Event::MouseButtonReleased, [&](const sf::Event& ev) -> void { this->m_mouseButtonReleasedSTHandler.processEvents(ev); } });
}

void GlobalEvents::GlobalHandler::pollAndExecuteEvents() {
	sf::Event uniqueEvent{};
	while (this->m_window->pollEvent(uniqueEvent)) {
		if (this->m_wrapperCallmap.find(uniqueEvent.type) != this->m_wrapperCallmap.end()) {
			(this->m_wrapperCallmap[uniqueEvent.type])(uniqueEvent);
		}
	}
}
void GlobalEvents::GlobalHandler::attachStandardWindowEventCallback(sf::Event::EventType evt, ECallbackAttechment callback) {
	if (evt == sf::Event::EventType::Closed || evt == sf::Event::EventType::Resized ||
		evt == sf::Event::EventType::GainedFocus || evt == sf::Event::EventType::LostFocus)
	{
		this->m_wrapperCallmap.insert(std::make_pair(evt, callback));
	}
}

void GlobalEvents::GlobalHandler::attachKeyCallback(sf::Event::EventType specificAction, sf::Keyboard::Key key, ECallbackAttechment callback) {
	auto* subtypehandler = this->m_evaluateSubTypeHandler<sf::Keyboard::Key>(specificAction);
	subtypehandler->addCallback(key, callback);
}

void GlobalEvents::GlobalHandler::attachMouseButtonCallback(sf::Event::EventType specificAction, sf::Mouse::Button btn, ECallbackAttechment callback) {
	auto* subtypehandler = this->m_evaluateSubTypeHandler<sf::Mouse::Button>(specificAction);
	subtypehandler->addCallback(btn, callback);
}

void GlobalEvents::GlobalHandler::reset() {
	this->m_keyPressedSTHandler.reset();
	this->m_keyReleasedSTHandler.reset();
	this->m_mouseButtonPressedSTHandler.reset();
	this->m_mouseButtonReleasedSTHandler.reset();
}

void GlobalEvents::GlobalHandler::deleteSpecificEvent(sf::Event::EventType specificAction, sf::Keyboard::Key key) {
	auto* subtypehandler = this->m_evaluateSubTypeHandler<sf::Keyboard::Key>(specificAction);
	subtypehandler->removeCallback(key);
}

void GlobalEvents::GlobalHandler::deleteSpecificEvent(sf::Event::EventType specificAction, sf::Mouse::Button btn) {
	auto* subtypehandler = this->m_evaluateSubTypeHandler<sf::Mouse::Button>(specificAction);
	subtypehandler->removeCallback(btn);
}

void GlobalEvents::GlobalHandler::attachToKeyCallbackMultiset(sf::Event::EventType specificAction, sf::Keyboard::Key key, ECallbackAttechment callback) {
	auto* subtypehandler = this->m_evaluateSubTypeHandler<sf::Keyboard::Key>(specificAction);
	subtypehandler->addCallbackToMultiSet(key, callback);
}

void GlobalEvents::GlobalHandler::attachToMouseCallbackMultiset(sf::Event::EventType specificAction, sf::Mouse::Button btn, ECallbackAttechment callback) {
	auto* subtypehandler = this->m_evaluateSubTypeHandler<sf::Mouse::Button>(specificAction);
	subtypehandler->addCallbackToMultiSet(btn, callback);
}

void GlobalEvents::GlobalHandler::deleteCallbackSet(sf::Event::EventType specificAction, sf::Keyboard::Key key) {
	auto* subtypehandler = this->m_evaluateSubTypeHandler<sf::Keyboard::Key>(specificAction);
	subtypehandler->removeCallbackSet(key);
}

void GlobalEvents::GlobalHandler::deleteCallbackSet(sf::Event::EventType specificAction, sf::Mouse::Button btn) {
	auto* subtypehandler = this->m_evaluateSubTypeHandler<sf::Mouse::Button>(specificAction);
	subtypehandler->removeCallbackSet(btn);
}