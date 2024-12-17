#pragma once
#include "CoreMinimal.h"
#include "Component.h"

class Entity
{
protected:
	string name;
	float life;
	vector<Component*> components;

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