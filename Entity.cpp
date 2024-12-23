#include "Entity.h"
#include "Game.h"

Entity::Entity(const string& _name, const string& _appearance)
{
	name = _name;
	appearance = _appearance;
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

void Entity::SetLocation(const Coords& _newLocation)
{
	Game::GetInstance().GetLevel()->ChangeItemAtLocation(location, appearance, _newLocation);
	location = _newLocation;
}

void Entity::Update()
{
	for (Component* _component : components)
	{
		_component->Update();
	}
}