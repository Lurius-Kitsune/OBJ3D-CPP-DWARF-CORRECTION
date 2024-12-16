#include "Color.h"

// ==== COLOR ====
string Color::RainbowEveryChar(const string& _word)
{
	string _newWord = "";
	for (u_int _i = 0; _i < _word.length(); _i++)
	{
		_newWord += GetRandomColor() + _word[_i];
	}

	return _newWord + RESET;
}

string Color::RainbowString(const string& _word)
{
	return GetRandomColor() + _word + RESET;
}

void Color::DisplayRainbow(const string& _text)
{
	while (!_kbhit())
	{
		CLEAR_SCREEN;
		cout << RainbowString(_text) << endl;
		const auto _start = high_resolution_clock::now();
		sleep_for(200ms);
		const auto _end = high_resolution_clock::now();
		const duration<double, milli> _elapsed = _end - _start;
	}
}

string Color::GetRandomColor()
{
	const string _rainbowTable[] =
	{
		WHITE,
		DARK_RED,
		RED ,
		DARK_ORANGE ,
		ORANGE,
		DARK_YELLOW,
		YELLOW,
		LIME,
		GREEN,
		BLUE,
		LIGHT_BLUE,
		CYAN,
		PINK,
		MAGENTA,
		PURPLE,
		BROWN
	};

	const u_int _rainbowSize = size(_rainbowTable) - 1;

	return _rainbowTable[RandomInt(0, _rainbowSize)];
}

// ==== GRADIENT ====
string Gradient::GradientString(const string _text, const bool _textOnly)
{
	const int _size = static_cast<int>(_text.size());
	Color _color;
	string _newWord = "";
	for (int _index = 0; _index < _size; _index++)
	{
		_color = ClampGradient(_index, _size);
		_newWord += _color.ToString(_textOnly) + _text[_index];
	}
	return _newWord + RESET;
}

Color Gradient::ClampGradient(const int _index, const int _maxDisplayChar) const
{
	float _normalizer;
	float _valueRed = 0;
	float _valueGreen = 0;
	float _valueBlue = 0;


	float _rangeRed = static_cast<float>(gradB.r - gradA.r);
	_normalizer = _index * (_rangeRed / _maxDisplayChar);
	_valueRed += (gradA.r + _normalizer);

	float _rangeGreen = static_cast<float>(gradB.g - gradA.g);
	_normalizer = _index * (_rangeGreen / _maxDisplayChar);
	_valueGreen += (gradA.g + _normalizer);

	float _rangeBlue = static_cast<float>(gradB.b - gradA.b);
	_normalizer = _index * (_rangeBlue / _maxDisplayChar);
	_valueBlue += (gradA.b + _normalizer);

	return { (int)_valueRed, (int)_valueGreen, (int)_valueBlue };
}
