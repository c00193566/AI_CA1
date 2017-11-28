#pragma once

class EventListener
{
public:
	enum class Event
	{
		UP,
		UPR,
		DOWN,
		DOWNR,
		LEFT,
		LEFTR,
		RIGHT,
		RIGHTR,
		QUIT
	};

	virtual void onEvent(Event) = 0;
};