#pragma once
#include "Singleton.h"

enum KeyEventType
{
	KET_PRESSED,
	KET_RELEASED,
	KET_HOLD,
	KET_REPETED,

	KET_COUNT,
};

struct KeyEvent
{
	KeyEventType type;
	int keyCode;
};

enum MouseEventType
{
	MET_MOVED,
	MET_CLOCKED,
	MET_DRAGGED,

	MET_COUNT,
};

union MouseValue
{
	struct Position
	{
		int x;
		int y;
	} position;

	int code;

	MouseValue(const COORD& _coord)
	{
		position.x = _coord.X;
		position.y = _coord.Y;
	}
	MouseValue(const int _code)
	{
		code = _code;
	}
};

struct MouseEvent
{
	MouseEventType type;
	MouseValue value;

	MouseEvent(const MouseEventType& _type, const MouseValue& _value)
	{
		type = _type;
		value = _value;
	}
};

enum EventType
{
	ET_KEYBOARD,
	ET_MOUSE,

	ET_COUNT
};

struct Event
{
	EventType type;

	union
	{
		KeyEvent keyboard;
		MouseEvent mouse;
	};
	Event() = default;

	Event(const EventType& _type, const KeyEvent& _keyboard)
	{
		type = _type;
		keyboard = _keyboard;
	}

	Event(const EventType& _type, const MouseEvent& _mouse)
	{
		type = _type;
		mouse = _mouse;
	}
};
class InputManager : public Singleton<InputManager>
{
	queue<Event> allEvents;

private:
	void CollectEvents();

public:
	bool PollEvents(Event& _event);
	void PollEventDemo();
};