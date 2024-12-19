#pragma once
#include "CoreMinimal.h"
#include <map>

enum InputActionType
{
	IAT_UP,
	IAT_DOWN,
	IAT_LEFT,
	IAT_RIGHT,
	IAT_INTERACT,
	IAT_VALIDATE,
	IAT_PAUSE,
	IAT_TAB, // TO DO CHANGE NAME

	IAT_INVALID
};

struct GameInput
{
	map<char, InputActionType> inputs;
	map<InputActionType, string> inputsName;

	pair<char, InputActionType> GetInputByIndex(const int _index)const
	{
		InputActionType _inputActionType = InputActionType(_index);
		for (pair<char, InputActionType> _input : inputs)
		{
			if (_input.second == _inputActionType)
			{
				return _input;
			}
		}
	}

	GameInput()
	{
		inputs =
		{
			{72, IAT_UP},
			{80, IAT_DOWN},
			{75, IAT_LEFT},
			{77, IAT_RIGHT},
			{32, IAT_INTERACT},
			{13, IAT_VALIDATE},
			{27, IAT_PAUSE},
			{9, IAT_TAB},
		};

		inputsName =
		{
			{IAT_UP, "Haut"},
			{IAT_DOWN, "Bas"},
			{IAT_LEFT, "Gauche"},
			{IAT_RIGHT, "Droite"},
			{IAT_INTERACT, "Int�ragir"},
			{IAT_VALIDATE, "Valider"},
			{IAT_PAUSE, "Mettre en pause"},
			{IAT_TAB, "TAB ?"},
		};
	}

	InputActionType GetInputActionType(const char _input)
	{
		return inputs.find(_input) != inputs.end() ? inputs[_input] : IAT_INVALID;
	}

	char GetInputKeyByInputType(const InputActionType& _inputActionType)
	{
		for (pair<char, InputActionType> _input : inputs)
		{
			if (_input.second == _inputActionType)
			{
				return _input.first;
			}
		}

		return 0;
	}
};