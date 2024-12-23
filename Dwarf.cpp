#include "Dwarf.h"
#include "MovementComponent.h"

Dwarf::Dwarf(const string& _appearance) : Entity("Dwarf", _appearance)
{
	AddComponent(new MovementComponent(1));
}