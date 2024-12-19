#pragma once
#include "CoreMinimal.h"
#include "Color.h"

template <typename Type>
void Print(const string& _separator, const Type& _value)
{
	cout << _value << _separator;
}

template <typename Type, typename ...Args>
void Print(const string& _separator, const Type& _value, const Args&... _args)
{
	cout << _value << _separator;
	Print(_separator, _args...);
}

void ResetColor();
void JumpLine();

template <typename Type>
Type Clamp(const Type& _value, const Type& _min, const Type& _max)
{
	return (_value < _min) ? _min : (_value > _max ? _max : _value);
}