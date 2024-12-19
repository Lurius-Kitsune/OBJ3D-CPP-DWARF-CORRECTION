#include "ControlsMenu.h"
#include "Macro.h"

ControlsMenu::ControlsMenu() : Menu("Controls Menu")
{
	

}

void ControlsMenu::Show(const bool _toAdd)
{
	Super::Show(_toAdd);
}

void ControlsMenu::Interact()
{
	ChangeKey(gameInputs.GetInputByIndex(0));
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

	if (gameInputs.inputs.find(_input) != gameInputs.inputs.end()) return;

	gameInputs.inputs.erase(_inputToChange.first);
	_inputToChange.first = _input;

	gameInputs.inputs.insert(_inputToChange);
}