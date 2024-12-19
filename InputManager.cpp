#include "InputManager.h"

// Fonction pour collecter les événements
void InputManager::CollectEvents()
{
    HANDLE _hConsole = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD _inputRecords[128];
    DWORD _eventsRead;

    // Lire les événements disponibles sans bloquer
    while (PeekConsoleInput(_hConsole, _inputRecords, 128, &_eventsRead) && _eventsRead > 0)
    {
        ReadConsoleInput(_hConsole, _inputRecords, _eventsRead, &_eventsRead);
        for (DWORD _index = 0; _index < _eventsRead; ++_index)
        {
            const INPUT_RECORD& _record = _inputRecords[_index];

            if (_record.EventType == MOUSE_EVENT)
            {
                const MOUSE_EVENT_RECORD& _mouse = _record.Event.MouseEvent;
                const bool _leftButtonClicked = (_mouse.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) != 0;
                const bool _rightButtonClicked = (_mouse.dwButtonState & RIGHTMOST_BUTTON_PRESSED) != 0;
                MouseEvent _mouseEvent = MouseEvent(MET_CLICKED, MouseValue(_mouse.dwMousePosition));
                allEvents.push(Event(ET_MOUSE, _mouseEvent));
            }

            if (_record.EventType == KEY_EVENT)
            {
                const KEY_EVENT_RECORD& _key = _record.Event.KeyEvent;
                KeyEvent _keyEvent = KeyEvent(_key.bKeyDown ? KET_PRESSED : KET_RELEASED, CAST(int, _key.wVirtualKeyCode));
                allEvents.push(Event(ET_KEYBOARD, _keyEvent));
            }
        }
    }
}

void InputManager::PollEventDemo()
{
    // Configurer la console pour capturer les événements
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hConsole, &mode);
    // Activer les événements clavier et souris
    SetConsoleMode(hConsole, mode | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    int frameCounter = 0;

    while (true)
    {
        // Simuler une logique indépendante (non bloquante)
        cout << "Frame: " << frameCounter++ << "\r"; // Écrase la ligne précédente
        this_thread::sleep_for(chrono::milliseconds(16)); // Simule ~60 FPS

        // Collecter les événements
        CollectEvents();

        // Traiter les événements
        Event _event;
        while (PollEvents(_event))
        {
            if (_event.type == ET_KEYBOARD)
            {
                const KeyEvent& _key = _event.keyboard;
            }

            else if (_event.type == ET_MOUSE)
            {
                const MouseEvent& mouse = _event.mouse;
            }
        }
    }
}

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