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
void Print(const Type& _value, const bool _endl = true)
{
    cout << _value;
    if (_endl) cout << endl;
}

