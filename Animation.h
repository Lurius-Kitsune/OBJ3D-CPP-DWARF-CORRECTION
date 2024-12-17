#pragma once
#include "CoreMinimal.h"

struct Animation
{
	vector<string> LoadStartUpAnimationFrame(const string& _file);
	void PlayAnimation(const vector<string>& _animation, const bool _loop = false);
	void LoadStartUpAnimation(const string& _filepath, const string& _extension, const int _count);
};