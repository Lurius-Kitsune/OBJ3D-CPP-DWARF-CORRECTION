#pragma once
#include "CoreMinimal.h"

static int RandomInt(const int _min, const int _max)
{
	random_device _rSeed; // Obtient un graine aléatoire
	mt19937 _gen(_rSeed()); // Initialise le générateur avec la graine
	uniform_int_distribution<> _distr(_min, _max); // Définit la distribution (les limites)

	return _distr(_gen); // Génération du nombre
}
