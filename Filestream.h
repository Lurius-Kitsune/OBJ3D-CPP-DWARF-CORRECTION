#pragma once
#include "CoreMinimal.h"

class FileStream
{
	using openMode = ios_base::openmode;

public:
	static vector<string> ReadAll(const string& _path);
	static bool Write(const string& _path, const vector<string>& _content);
};