#include "ControlsMenu.h"
#include "Macro.h"

ControlsMenu::ControlsMenu(GameInput* _gameInput) : Menu ("Controls Menu", _gameInput->inputs.size())
{
	gameInputs = _gameInput;
  
}

void ControlsMenu::Show()
{
	int _i = 0;
	for(pair<InputActionType, string> _inputName : gameInputs->inputsName)
	{
		cout << (_i == currentIndex ? "> " : "") + _inputName.second << " : " << int(gameInputs->GetInputKeyByInputType(_inputName.first));
		cout << endl;
		_i++;
	}
}

void ControlsMenu::Hide()
{
	system("cls");
}

void ControlsMenu::Interact()
{
	ChangeKey(gameInputs->GetInputByIndex(currentIndex));
}

void ControlsMenu::ChangeKey(pair<char, InputActionType> _inputToChange)
{
	system("cls");
	cout << "Veuillez appuyer sur un bouton...";
	int _input = 0;
	while (!_kbhit());
	_input = _getch();
	// TODO Optimise
	if (_input == 224)
	{
		_input = _getch();
	}

	if (gameInputs->inputs.find(_input) != gameInputs->inputs.end()) return;

	gameInputs->inputs.erase(_inputToChange.first);
	_inputToChange.first = _input;

	gameInputs->inputs.insert(_inputToChange);
}
