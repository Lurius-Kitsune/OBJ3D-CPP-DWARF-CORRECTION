#include "VideoMenu.h"
#include "Macro.h"

VideoMenu::VideoMenu() : Menu("Video")
{

}

void VideoMenu::Show(const bool _toAdd)
{
	// Clear l'affichage et laisser que le menu
	system("cls");
	Interact();
}

void VideoMenu::DisplayMenu(int _selectedIndex, int& _brightness, int& _contrast)
{
	const int _progressBarMax = 20;
	string _options[3] = {
		"Modifier la luminosite",
		"Modifier le contraste",
		"Quitter"
	};

	system("cls");

	double _brightnessFactor = _brightness / 50.0; // 50% = 1.0
	double _contrastFactor = _contrast / 50.0;

	Color _testColor = Color(23, 183, 191);
	_testColor.AdjustBrightness(_brightnessFactor);
	_testColor.CalculateSaturation(_contrastFactor);

	for (int _index = 0; _index < 3; _index++)
	{
		if (_index == _selectedIndex)
		{
			cout << "> " << _options[_index] << " <" << endl;

			if (_index == 0)
			{
				cout << "      " << _testColor.ToString(false) << "TEST" << RESET << " ";
				DisplayProgressBar("Luminosite", _brightness, _progressBarMax);
			}
			else if (_index == 1)
			{
				cout << "      " << _testColor.ToString(false) << "TEST" << RESET << " ";
				DisplayProgressBar("Contraste", _contrast, _progressBarMax);
			}
		}
		else
		{
			cout << "  " << _options[_index] << endl;
		}
	}
}

void VideoMenu::DisplayProgressBar(const string& _label, int& _value, int _maxLength)
{
	cout << _label << ": [";
	int _filled = (_value * _maxLength) / 100;

	for (int _index = 0; _index < _maxLength; _index++)
	{
		cout << (_index < _filled ? "=" : " ");
	}
	cout << "] " << _value << "%" << endl;
}

void VideoMenu::AdjustValue(u_int& _value, const u_int& _delta)
{
	_value = Clamp<u_int>(_value + _delta, 0, 100);
}

void VideoMenu::Interact()
{
	int _selectedIndex = 0;
	int _brightness = 50; // 0 == on voit rien, 100 = surbrillance, 50 = parfait
	int _contrast = 50;   // pareil


	DisplayMenu(_selectedIndex, _brightness, _contrast);

	while (true)
	{
		//if (_kbhit())
		//{
		//	InputActionType _inputAction = gameInput->GetInputActionType(_getch());

		//	switch (_inputAction)
		//	{
		//	case IAT_UP:
		//		_selectedIndex = (_selectedIndex - 1 + 3) % 3;
		//		break;
		//	case IAT_DOWN:
		//		_selectedIndex = (_selectedIndex + 1) % 3;
		//		break;
		//	case IAT_RIGHT:
		//		if (_selectedIndex == 0)
		//			AdjustValue(_brightness, 5);
		//		else if (_selectedIndex == 1)
		//			AdjustValue(_contrast, 5);
		//		break;
		//	case IAT_LEFT:
		//		if (_selectedIndex == 0)
		//			AdjustValue(_brightness, -5);
		//		else if (_selectedIndex == 1)
		//			AdjustValue(_contrast, -5);
		//		break;
		//	case IAT_VALIDATE:
		//		if (_selectedIndex == 2)
		//			return; // Quitter
		//		break;
		//	case IAT_PAUSE:
		//		return; // Revenir au jeu
		//	default:
		//		break;
		//	}
		//	DisplayMenu(_selectedIndex, _brightness, _contrast);
		//}
	}
}