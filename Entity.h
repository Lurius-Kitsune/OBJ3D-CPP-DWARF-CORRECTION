#pragma once
#include "CoreMinimal.h"
#include "Component.h"
#include "Coordinates.h"

class Entity
{
protected:
	string name;
	string appearance;
	float life;
	vector<Component*> components;
	Coords location;

public:
	INLINE Coords GetLocation() const
	{
		return location;
	}

public:
	Entity(const string& _name, const string& _appearance);
	~Entity();

public:
	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);
	template <typename Type>
	Type* GetComponent()
	{
		for (Component* _component : components)
		{
			if (Type* _value = dynamic_cast<Type*>(_component)) return _value;
		}

		return nullptr;
	}
	void SetLocation(const Coords& _newLocation);
	void Update();
};