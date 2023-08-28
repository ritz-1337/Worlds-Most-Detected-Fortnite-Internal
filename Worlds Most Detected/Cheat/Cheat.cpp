#include "Cheat.h"
#include "../SDK/EngineFunctions.h"
#include "../SDK/Addresses/Sigs.h"
#include "Esp/WorldEsp.h"
#include "Esp/PlayerEsp.h"

void CheatTick() {
	auto World = *(UWorld**)(Sigs["GWorld"].Value);
	if (!(uintptr_t)World)
		return;

	DrawAllActorBounds(World);
	DrawAllAPlayerBounds(World);
}