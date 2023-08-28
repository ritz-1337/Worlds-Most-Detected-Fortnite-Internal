#include "PlayerEsp.h"
#include "../../SDK/EngineFunctions.h"
#include "../../SDK/Addresses/Sigs.h"
#include "../../Render/ImGui/imgui.h"
#include "../../Util.h"
#include "../../Settings.h"

void DrawAllAPlayerBounds(UWorld* World) {
	auto PlayerController = World->OwningGameInstance()->LocalPlayer()->PlayerController();
	if (!(uintptr_t)PlayerController)
		return;

	TArray<AActor*> Actors = {};
	auto StaticClass = (AActor*)Objects["FortPlayerPawn"].Object;
	if (!(uintptr_t)StaticClass)
		return;

	GetAllActorsOfClass((UObject*)World, StaticClass, &Actors);

	for (int i = 0; i < Actors.Num(); i++) {
		auto Actor = Actors[i];
		if (!(uintptr_t)Actor)
			continue;

		Vector3 BoxExtent;
		Vector3 Orgin;
		GetActorBounds(Actor, &Orgin, &BoxExtent);

		Draw3dBox(PlayerController, BoxExtent, Orgin, 1, ImColor(200, 50, 200));
	}
}