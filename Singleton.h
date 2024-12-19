#pragma once
#include "CoreMinimal.h"

template <typename Class>
class Singleton
{
protected:
	static Class instance;

public: 
	static INLINE Class& GetInstance()
	{
		return instance;
	}
};

template <typename Class>
Class Singleton<Class>::instance;

