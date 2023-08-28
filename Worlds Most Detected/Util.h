#pragma once
#include "SDK/Math/Structs.h"
#include "Render/Render.h"
#include "SDK/EngineFunctions.h"

void CreateConsole();
void Draw3dBox(APlayerController* PlayerController, Vector3 BoxExtent, Vector3 Origin, float thicky, ImColor color);
void DrawHighlightMenu();