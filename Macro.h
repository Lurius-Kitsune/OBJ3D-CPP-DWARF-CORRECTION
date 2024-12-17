#pragma once
#include "CoreMinimal.h"
#include "Macro.h"

#define CLEAR_CIN cin.clear(); \
                cin.ignore((numeric_limits<streamsize>::max)(), '\n'); \
                cin.seekg(cin.beg);

#define SPACE DISPLAY("", true);
#define DISPLAY_LINE DISPLAY("=========================", true);

#define CLEAR_SCREEN system("cls");

void ChangeEncoding();

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

