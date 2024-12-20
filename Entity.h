#pragma once
#include "CoreMinimal.h"
#include "Component.h"
#include "Coordinates.h"

class Entity
{
protected:
	string name;
	float life;
	vector<Component*> components;
	Coords location;

public:
	INLINE void SetLocation(const Coords& _location)
	{
		location = _location;
	}

public:
	Entity(const string& _name);
	~Entity();

public:

	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);

	template <typename Type>
	Type* GetComponent()
	{
		for (Component* _component : components)
		{
			if (Type* _value = dynamic_cast<Type>(_component)) return _value;
		}

		return nullptr;
	}

	void Update();
};