#pragma once
#include "CoreMinimal.h"
#include "Cursor.h"
#include "Macro.h"
#include "Color.h"

class Menu
{
	string title;
	queue<Menu*> queue;

public:
	INLINE string GetTitle() const
	{
		return title;
	}

public:
	Menu(const string& _title);
	virtual ~Menu() = default;

private:
	template <typename Type>
	void InitMenuText(vector<string>& _menuText, const vector<Type>& _options, const int _currentIndex, const string& _question, const string& _selectedColor) const
	{
		const u_int& _size = CAST(const u_int&, _options.size());
		_menuText.push_back("========== ACTION ==========");
		for (u_int _i = 0; _i < _size; _i++)
		{
			string _firstSymbol = " ", _secondSymbol = "" RESET;
			if (_i == _currentIndex)
			{
				_firstSymbol = _selectedColor + "[";
				_secondSymbol = _selectedColor + "]" + RESET;
			}
			stringstream _ss;
			_ss << _options[_i];
			_menuText.push_back(_firstSymbol + RED + _ss.str() + _secondSymbol);
		}
		_menuText.push_back("==========================");
	}

	template <typename Type>
	void DisplayMenu(const vector<Type>& _options, const int _currentIndex, const string& _question, const bool _center) const
	{
		vector<string> _menu;
		const string& _selectedColor = MAGENTA;
		InitMenuText(_menu, _options, _currentIndex, _question, _selectedColor);
		if (_center)
		{
			Cursor _cursor;
			_cursor.DisplayOnceCenterMultiLine(_menu, CAST(const u_int&, _menu.size()), { 0, 0 });
		}
		else
		{
			for (const string& _line : _menu)
			{
				Print("\n", _line);
			}
		}
	}

protected:
	template <typename Elem, typename Param, typename RetType>
	RetType OpenMenu(const vector<Elem>& _options, const string& _question, const function<RetType(Param)>& _callback, const bool _center = false)
	{
		u_int _currentIndex = 0;
		const u_int& _size = (u_int)_options.size();
		DisplayMenu(_options, _currentIndex, _question, _center);
		do
		{

			if (_kbhit())
			{
				// Attendre une touche
				u_int _input = 0;
				_input = _getch();
				if (_input == 224)
				{
					_input = _getch();
				}

				// Si la touche est entrée, alors _isChoiceMade = true
				switch (_input)
				{
				case 13:
					system("cls");
					return _callback(_currentIndex);
				case 72:
					// Si la touche est fleche du haut, alors _choiceIndex--
					_currentIndex = (_currentIndex <= 0 ? _size - 1 : _currentIndex - 1);
					break;
				case 80:
					// Si la touche est fleche du bas, alors _choiceIndex++
					_currentIndex = (_currentIndex >= _size - 1 ? 0 : _currentIndex + 1);
					break;
				default:
					break;
				}
				system("cls");
				DisplayMenu(_options, _currentIndex, _question, _center);
			}

		} while (true);
	}

public:
	virtual void Show(const bool _toAdd = true);
	virtual void Hide();
	virtual void Interact() {};

public:
	void Close();
	friend ostream& operator << (ostream& _stream, Menu* _other);
};