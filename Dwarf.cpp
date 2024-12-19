#include "Dwarf.h"
#include "MovementComponent.h"

Dwarf::Dwarf() : Entity("Dwark")
{
	components.push_back(new MovementComponent(1));
}