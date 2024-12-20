#include "Dwarf.h"
#include "MovementComponent.h"

Dwarf::Dwarf(const string& _appearance) : Entity("Dwark", _appearance)
{
	AddComponent(new MovementComponent(1));
}