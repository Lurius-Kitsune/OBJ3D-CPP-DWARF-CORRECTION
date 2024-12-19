#include "Animation.h"

vector<string> Animation::LoadAnimationFrame(const string& _file)
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

void Animation::PlayForwardAnimation(const bool _loop, Cursor _cursor, const int _size)
{

	for (int _frameIndex = 0; _frameIndex < _size; _frameIndex++)
	{
		vector<string> _temp;
		const int _frameSize = (int)animLists[_frameIndex].size();
		for (int _index = 0; _index < _frameSize; _index++)
		{
			if (!isPlaying) return;
			if (useGradient) _temp.push_back(color.GradientString(animLists[_frameIndex][_index]));
			else _temp.push_back(color.gradA.ToString(true) + animLists[_frameIndex][_index]);
		}
		_cursor.DisplayOnceCenterMultiLine(_temp, _frameSize, padding);
		if (_loop && _frameIndex == _size - 1) _frameIndex = 0;
		Sleep((DWORD)playRate);
	}
}

void Animation::PlayBackwardAnimation(const bool _loop, Cursor _cursor, const int _size)
{
	for (int _frameIndex = _size - 1; _frameIndex >= 0; _frameIndex--)
	{
		vector<string> _temp;
		const int _frameSize = (int)animLists[_frameIndex].size();
		for (int _index = 0; _index < _frameSize; _index++)
		{
			if (!isPlaying) return;

			if (useGradient) _temp.push_back(color.GradientString(animLists[_frameIndex][_index]));
			else _temp.push_back(color.gradA.ToString(true) + animLists[_frameIndex][_index]);
		}
		_cursor.DisplayOnceCenterMultiLine(_temp, _frameSize, padding);
		if (_loop && _frameIndex == 0) _frameIndex = _size - 1;
		Sleep((DWORD)playRate);
	}
}

void Animation::PlayPingPongAnimation(const bool _loop, Cursor _cursor, const int _size)
{
	while (!_loop || isPlaying)
	{
		PlayForwardAnimation(false, _cursor, _size);
		PlayBackwardAnimation(false, _cursor, _size);
	}
}

void Animation::LoadAnimation(const string& _filepath, const string& _extension, const int _count)
{
	animLists.clear();
	for (int _index = 0; _index <= _count; _index++)
	{
		vector<string> _temp = LoadAnimationFrame(_filepath + to_string(_index) + _extension);
		animLists.push_back(_temp);
	}
}

void Animation::StopAnimation()
{
	isPlaying = false;
	system("cls");
}

void Animation::PlayAnimation(const bool _loop, const AnimDirectionType& _direction)
{
	isPlaying = true;
	system("cls");
	Cursor _cursor = Cursor();
	const int _size = (int)animLists.size();
	switch (_direction)
	{
	case ADT_FORWARD:
		PlayForwardAnimation(_loop, _cursor, _size);
		break;
	case ADT_BACKWARD:
		PlayBackwardAnimation(_loop, _cursor, _size);
		break;
	case ADT_PINGPONG:
		PlayPingPongAnimation(_loop, _cursor, _size);
		break;
	}
	StopAnimation();
}

void Animation::PaddingForSmolLoadingScreen()
{
	Cursor _cursor;
	padding.x = _cursor.GetCenterConsole().x - (int)animLists[0].size() - 8;
	padding.y = _cursor.GetCenterConsole().y;
}
