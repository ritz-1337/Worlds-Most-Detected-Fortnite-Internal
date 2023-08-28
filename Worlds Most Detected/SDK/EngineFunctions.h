#pragma once
#include "Math/Structs.h"
#include "Addresses/Objects.h"
class AFortWeapon {
public:

};
class USkeletalMeshComponent {
public:

};
class USceneComponent {
public:

};
class APlayerState {
public:

};
class APlayerCameraManager {
public:

};
class AActor {
public:
	void Get_Highest_Priority_Highlight(class UObject** Source, struct FPawnHighlight* Top_Priority);
	void ApplyPawnHighlight(void* Source, const struct FPawnHighlight& HitGlow);
};
class APlayerPawn_Athena_C : public AActor {
public:
	//void Get_Highest_Priority_Highlight(class UObject** Source, struct FPawnHighlight* Top_Priority);
	//void ApplyPawnHighlight(class UObject* Source, const struct FPawnHighlight& HitGlow);
};
class APlayerController {
public:
	AActor* AcknowledgedPawn();
	APlayerCameraManager* PlayerCameraManager();
	Vector2 ProjectWorldLocationToScreen(const struct Vector3& WorldLocation);
};

class ULocalPlayer {
public:
	APlayerController* PlayerController();
};

class ULevel {
public:
	
};

class UGameInstance {
public:
	ULocalPlayer* LocalPlayer();
};

class UWorld {
public:
	UGameInstance* OwningGameInstance();
	TArray<ULevel*> Levels();
	ULevel* PersistentLevel();
};

FString GetObjectName(class UObject* Object);
uintptr_t StaticFindObject(const wchar_t* name);
bool ProcessEvent(uintptr_t address, void* fnobject, void* parms);
int GetNumPlayerControllers(UObject* WorldContextObject);
void GetAllActorsOfClass(class UObject* WorldContextObject, class AActor* ActorClass, TArray<class AActor*>* OutActors);
void GetActorBounds(class AActor* Actor, struct Vector3* Origin, struct Vector3* BoxExtent);