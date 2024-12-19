#include "InputManager.h"

bool InputManager::PollEvents(Event& _event)
{
	if (!allEvents.empty())
	{
		_event = allEvents.front();
		allEvents.pop();
		return true;
	}

	return false;
}
