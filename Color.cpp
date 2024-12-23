#include "Color.h"
#include "Macro.h"
#include "Random.h"

#pragma region Color

Color::Color()
{
    r = g = b = 0;
}

Color::Color(const int _r, const int _g, const int _b)
{
    r = _r;
    g = _g;
    b = _b;
}

string Color::ToString(const bool _textOnly) const
{
    if (_textOnly) return TEXT_RGB(r, g, b);
    return BG_RGB(r, g, b);
}


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
        system("cls");
        Print("", RainbowString(_text));
        const auto& _start = high_resolution_clock::now();
        sleep_for(200ms);
        const auto& _end = high_resolution_clock::now();
        const duration<double, milli>& _elapsed = _end - _start;
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

    const u_int& _rainbowSize = size(_rainbowTable) - 1;
    return _rainbowTable[GetRandom(0, _rainbowSize)];
}

void Color::CalculateSaturation(double _factor)
{
    // Calcul de l'intensit�
    double _gray = (r + g + b) / 3.0;

    // Ajuste chaque composante en fonction de la saturation
    r = Clamp(static_cast<int>(_gray + (r - _gray) * _factor), 0, 255);
    g = Clamp(static_cast<int>(_gray + (g - _gray) * _factor), 0, 255);
    b = Clamp(static_cast<int>(_gray + (b - _gray) * _factor), 0, 255);

}

void Color::AdjustBrightness(double _factor)
{
    ClampColor(r, _factor);
    ClampColor(g, _factor);
    ClampColor(b, _factor);
}

void Color::ClampColor(int& _value, double _factor)
{
    _value = Clamp(CAST(int, _value * _factor), 0, 255);
}

#pragma endregion

#pragma region Gradient

string Gradient::GradientString(const string& _text, const bool _textOnly) const
{
    const int _size = static_cast<int>(_text.size());
    string _newWord = "";

    for (int _index = 0; _index < _size; _index++)
    {
        const Color& _color = ClampGradient(_index, _size);
        if (_text[_index] == ' ') _newWord += _text[_index];
        else _newWord += _color.ToString(_textOnly) + _text[_index];
    }
    return _newWord + RESET;
}

Color Gradient::GradientColor(const int _length, const int _colorIndex) const
{
    vector<Color> _colorGradient;
    for (int _index = 0; _index < _length; _index++)
    {
        _colorGradient.push_back(ClampGradient(_index, _length));
    }
    return _colorGradient[_colorIndex];
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

#pragma endregion