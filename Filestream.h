#pragma once
#include "CoreMinimal.h"

class FileStream
{
	string fullPath;
	string cryptageKey;
	u_int cryptageKeySize;
	bool isCrypt;
	fstream stream;
	ios_base::openmode openMode;

public:
	inline string GetFullPath() const
	{
		return fullPath;
	}


public:

	FileStream() = default;

	FileStream(const string& _fullPath,
		const ios_base::openmode& _openMode = ios_base::in | ios_base::out | ios_base::binary);

public:
	bool IsValid()const
	{
		return stream.is_open();
	}
	void SetCryptageKey(const string& _newKey)
	{
		if (isCrypt) return;
		cryptageKey = _newKey;
	}
	void SetIsCryptFile(const bool _isCrypt = true)
	{
		isCrypt = _isCrypt;
	}
	void SetCryptFileWithKey(const string& _newKey)
	{
		SetIsCryptFile();
		SetCryptageKey(_newKey);
	}

public:

	// operator == 
	bool operator==(const FileStream& _file)const
	{
		return fullPath == _file.fullPath;
	}

	void operator << (const ostringstream& _stream)
	{
		stream.write(_stream.str().c_str(), _stream.str().size());
	}

	// Afficher un nombre n de lignes à partir d'un index
	vector<string> ReadAll();

	string ReadLine(const u_int& _lineIndex = 0);

	streampos GetOffset(const u_int& _horizontal, const u_int& _vertical);

	int ComputeLineOfFile();
};

