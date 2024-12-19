#pragma once
#include "CoreMinimal.h"

template <typename Class>
class Singleton
{
protected:
	static Class instance;

public: 
	static Inline Class& GetInstance()
	{
		return instance;
	}
public:
	Singleton();
	~Singleton();

private:
};

