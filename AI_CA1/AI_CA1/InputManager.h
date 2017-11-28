#pragma once
#include "stdafx.h"
#include "EventListener.h"
#include "RenderSystem.h"

using namespace sf;

class InputManager
{
private:
	map<EventListener::Event, vector<EventListener*>*> EventListeners;

public:
	InputManager();
	~InputManager();

	void AddListener(EventListener::Event, EventListener*);
	void Dispatch(EventListener::Event);

	void ProcessInput(RenderSystem * Renderer);
};