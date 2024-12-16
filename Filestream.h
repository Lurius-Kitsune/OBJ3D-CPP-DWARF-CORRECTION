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
    FileStream(const string& _fullPath, const bool _autoCreate = false,
        const string& _cryptageKey = "LaCleeDesP1", const bool _isCrypt = false,
        const ios_base::openmode& _openMode = ios_base::in | ios_base::out | ios_base::binary);

    static vector<string> ReadAll(const string& _path);

    static bool Write(const string& _path, const vector<string>& _content);
};