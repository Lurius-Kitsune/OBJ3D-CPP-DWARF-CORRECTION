#include "Entity.h"

Entity::Entity(const string& _name)
{
	name = _name;
	life = 100.0f;
}

Entity::~Entity()
{
	for (Component* _component : components)
	{
		delete _component;
	}
}


void Entity::AddComponent(Component* _component)
{
	_component->SetOwner(this);
	components.push_back(_component);
}

void Entity::RemoveComponent(Component* _component)
{
	const u_int& _componentsCount = static_cast<const u_int&>(components.size());
	vector<Component*>::const_iterator _it = components.begin();
	for (; _it != components.end(); _it++)
	{
		if (*_it == _component)
		{
			components.erase(_it);
			delete *_it;
		}
	}
}

void Entity::Update()
{
	for (Component* _component : components)
	{
		_component->Update();
	}
}