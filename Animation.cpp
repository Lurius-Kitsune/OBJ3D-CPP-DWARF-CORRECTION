#include "Animation.h"
#include "Cursor.h"

vector<string> Animation::LoadStartUpAnimationFrame(const string& _file)
{
	ifstream _stream = ifstream(_file, ios::in);
	string _line;
	vector<string> _grid;

	while (getline(_stream, _line))
	{
		_grid.push_back(_line);
	}

	return _grid;
}

void Animation::PlayAnimation(const vector<string>& _animation, const bool _loop)
{
	int _size = (int)_animation.size();
	for (int _index = 0; _index < _size; _index++)
	{
		if (_loop && _index == _size) _index = 0;
		string* _temp = nullptr;
		int _size = 0;
		for (int _index2 = 0; _index2 < _animation.size(); _index2++)
		{
			//AddValueToArray(_temp, _size, _animation[_index2]);
		}
		//DisplayOnceCenterMultiLine(_temp, _size);
		delete[] _temp;
	}
}

void Animation::LoadStartUpAnimation(const string& _filepath, const string& _extension, const int _count)
{
	system("cls");
	vector<vector<string>> _texts;
	for (int _index = 0; _index <= _count; _index++)
	{
		vector<string> _temp = LoadStartUpAnimationFrame(_filepath + to_string(_index) + _extension);
		_texts.push_back(_temp);
	}
	for (int _index = 0; _index <= _count; _index++)
	{
		PlayAnimation(_texts[_index]);
	}
}