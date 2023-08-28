#pragma once
#include "../Math/Structs.h"
#include <string>
#include <map>

struct ObjectData {
    std::string Name;
    uintptr_t Object;
};

inline std::map<std::string, ObjectData> Objects = {
        {"KismetSystemLibrary", {"Engine.KismetSystemLibrary", 0}},
        {"GetObjectName", {"Engine.KismetSystemLibrary.GetObjectName", 0}},
        {"GameplayStatics", {"Engine.GameplayStatics", 0}},
        {"GetGameInstance", {"Engine.GameplayStatics.GetGameInstance", 0}},
        {"GetAllActorsOfClass", {"Engine.GameplayStatics.GetAllActorsOfClass", 0}},
        {"GetNumPlayerControllers", {"Engine.GameplayStatics.GetNumPlayerControllers", 0}},
        {"Actor", {"Engine.Actor", 0}},
        {"GetActorBounds", {"Engine.KismetSystemLibrary.GetActorBounds", 0}},
        {"ProjectWorldLocationToScreen", {"Engine.PlayerController.ProjectWorldLocationToScreen", 0}},
        {"FortPlayerPawnAthena", {"FortniteGame.FortPlayerPawnAthena", 0}},
        {"FortEngine_", {"FortEngine_", 0}},
};

void FetchObjects();