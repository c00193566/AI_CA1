#include "InputManager.h"

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::AddListener(EventListener::Event evt, EventListener *listener)
{
	if (EventListeners.find(evt) == EventListeners.end())
	{
		//event not in map add it.
		EventListeners[evt] = new std::vector<EventListener*>();
	}
	EventListeners[evt]->push_back(listener);
}

//Send the events to interested objects
void InputManager::Dispatch(EventListener::Event evt)
{
	if (EventListeners.find(evt) != EventListeners.end())
	{
		for (auto const &listener : *EventListeners[evt])
		{ //go through all listeners for this event
			listener->onEvent(evt); //Call on event for the listener
		}
	}
}


//Genereate events
void InputManager::ProcessInput(RenderSystem * Renderer)
{
	Event e;
	while (Renderer->getRenderer().pollEvent(e))
	{
		switch (e.type)
		{
			/* Keyboard event */
		case Event::KeyPressed:
			switch (e.key.code)
			{
			case Keyboard::Right:
				Dispatch(EventListener::Event::RIGHT);
				break;
			case Keyboard::Left:
				Dispatch(EventListener::Event::LEFT);
				break;
			case Keyboard::Up:
				Dispatch(EventListener::Event::UP);
				break;
			case Keyboard::Down:
				Dispatch(EventListener::Event::DOWN);
				break;
			case Keyboard::Space:
				Dispatch(EventListener::Event::SHOOT);
				break;
			}
			break;

		case Event::KeyReleased:
			switch (e.key.code)
			{
			case Keyboard::Right:
				Dispatch(EventListener::Event::RIGHTR);
				break;
			case Keyboard::Left:
				Dispatch(EventListener::Event::LEFTR);
				break;
			case Keyboard::Up:
				Dispatch(EventListener::Event::UPR);
				break;
			case Keyboard::Down:
				Dispatch(EventListener::Event::DOWNR);
				break;
			}
			break;

			/* SFML event Close */
		case Event::Closed:
			Dispatch(EventListener::Event::QUIT);
			break;

		default:
			break;
		}
	}
	//check for exit
}