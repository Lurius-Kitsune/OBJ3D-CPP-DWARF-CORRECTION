#pragma once
#include "CoreMinimal.h"
#include "Color.h"
#include "Cursor.h"
#include <type_traits>

#include <any>

enum AnimDirectionType
{
	ADT_FORWARD,
	ADT_BACKWARD,
	ADT_PINGPONG,
};

class Animation
{
	bool isPlaying;
	vector<vector<string>> animLists;
	Gradient color;
	float playRate;
	bool useGradient;
	Coords padding;

public:
	void SetColor(const Color& _color)
	{
		color.gradA = _color;
	}
	void SetColor(const Color& _colorA, const Color& _colorB)
	{
		color.gradA = _colorA;
		color.gradB = _colorB;
	}

	//template <typename ColorType>
	void SetColor(const any& _color)
	{
		bool _hasSuccess = true;
		try
		{
			color = any_cast<Gradient>(_color);
			useGradient = true;
		}
		catch (const std::bad_any_cast&)
		{
			bool _hasSuccess = true;
			useGradient = false;
			color.gradA = any_cast<Color>(_color);
		}
		useGradient = _hasSuccess;
	}

	void SetPlayRate(const float _playRate)
	{
		playRate = _playRate;
	}
	void SetPadding(const Coords& _padding)
	{
		padding = _padding;
	}

private:
	vector<string> LoadAnimationFrame(const string& _file);
	void PlayForwardAnimation(const bool _loop, Cursor _cursor, const int _size);
	void PlayBackwardAnimation(const bool _loop, Cursor _cursor, const int _size);
	void PlayPingPongAnimation(const bool _loop, Cursor _cursor, const int _size);

public:
	void LoadAnimation(const string& _filepath, const string& _extension, const int _count);
	void StopAnimation();
	void PlayAnimation(const bool _loop = false, const AnimDirectionType& _direction = ADT_FORWARD);
	void PaddingForSmolLoadingScreen();
};