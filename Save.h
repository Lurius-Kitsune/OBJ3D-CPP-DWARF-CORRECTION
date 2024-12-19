#pragma once
#include "CoreMinimal.h"

struct Save
{
	string title;
	string path;
	Save()
	{
		title = "Empty";
		path = "";
	}

	Save(const string& _title, const string& _path)
	{
		title = _title;
		path = _path;
	}

	friend ostream& operator << (ostream& _stream, Save _save)
	{
		return _stream << _save.title;
	}
};

