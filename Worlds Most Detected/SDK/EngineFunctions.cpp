#include "EngineFunctions.h"
#include "Addresses/Sigs.h"
#include <Windows.h>


uintptr_t StaticFindObject(const wchar_t* name)
{
	return (uintptr_t)reinterpret_cast<void* (*)(uintptr_t, uintptr_t, const wchar_t*, bool)>(Sigs["StaticFindObject"].Value)(0, 0, name, false);
}

bool ProcessEvent(uintptr_t address, void* fnobject, void* parms) {
	if (!address) 
		return false;

	auto index = *reinterpret_cast<void***>(address); if (!index) return false;
	auto fProcessEvent = static_cast<void(*)(void* address, void* fnobject, void* parms)>(index[0x4D]); if (!fProcessEvent) return false;
	fProcessEvent((void*)address, (void*)fnobject, (void*)parms);
	return true;
}
FString GetObjectName(class UObject* Object) {
	if (!(uintptr_t)Object)
		return {};

	struct {
		class UObject* Object;                                                   // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
		struct FString                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
	} params;

	params.Object = Object;
	ProcessEvent(Objects["KismetSystemLibrary"].Object, (UObject*)Objects["GetObjectName"].Object, &params);
	return params.ReturnValue;
}

int GetNumPlayerControllers(UObject* WorldContextObject) {
	if (!(uintptr_t)WorldContextObject)
		return 0;

	struct {
		class UObject* WorldContextObject;                                       // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
		int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
	} params;
	params.WorldContextObject = WorldContextObject;
	ProcessEvent(Objects["GameplayStatics"].Object, (UObject*)Objects["GetNumPlayerControllers"].Object, &params);
	return params.ReturnValue;
}

void GetAllActorsOfClass(class UObject* WorldContextObject, class AActor* ActorClass, TArray<class AActor*>* OutActors) {
	if (!(uintptr_t)WorldContextObject or !(uintptr_t)ActorClass)
		return;

	struct {
		class UObject* WorldContextObject;                                       // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
		class AActor* ActorClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
		TArray<class AActor*>                              OutActors;                                                // (Parm, OutParm, ZeroConstructor)
	} params;
	params.WorldContextObject = WorldContextObject;
	params.ActorClass = ActorClass;
	ProcessEvent(Objects["GameplayStatics"].Object, (UObject*)Objects["GetAllActorsOfClass"].Object, &params);
	*OutActors = params.OutActors;
}

void GetActorBounds(class AActor* Actor, struct Vector3* Origin, struct Vector3* BoxExtent) {
	if (!(uintptr_t)Actor)
		return;

	struct {
		class AActor* Actor;                                                    // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
		struct Vector3                                     Origin;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
		struct Vector3                                     BoxExtent;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	} params;
	params.Actor = Actor;
	ProcessEvent(Objects["GameplayStatics"].Object, (UObject*)Objects["GetActorBounds"].Object, &params);
	*Origin = params.Origin;
	*BoxExtent = params.BoxExtent;
}

void AActor::Get_Highest_Priority_Highlight(class UObject** Source, struct FPawnHighlight* Top_Priority) {
	if (!(uintptr_t)this)
		return;

	struct {
		class UObject* Source;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
		struct FPawnHighlight                              Top_Priority;                                             // (Parm, OutParm, IsPlainOldData)
	} params;
	ProcessEvent((uintptr_t)this, (UObject*)Objects["Get_Highest_Priority_Highlight"].Object, &params);
	*Source = params.Source;
	*Top_Priority = params.Top_Priority;
}

void AActor::ApplyPawnHighlight(void* Source, const struct FPawnHighlight& HitGlow) {
	if (!(uintptr_t)this)
		return;

	struct {
		void* Source;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
		struct FPawnHighlight                              HitGlow;                                             // (Parm, OutParm, IsPlainOldData)
	} params;
	params.Source = Source;
	params.HitGlow = HitGlow;
	ProcessEvent((uintptr_t)this, (UObject*)Objects["ApplyPawnHighlight"].Object, &params);
}

Vector2 APlayerController::ProjectWorldLocationToScreen(const struct Vector3& WorldLocation)
{
	if (!(uintptr_t)this)
		return {};

	struct {
		struct Vector3                                     WorldLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
		struct Vector2                                   ScreenLocation;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
		bool                                               bPlayerViewportRelative;                                  // (Parm, ZeroConstructor, IsPlainOldData)
		bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
	} params;
	params.WorldLocation = WorldLocation;
	params.bPlayerViewportRelative = false;
	ProcessEvent((uintptr_t)this, (UObject*)Objects["ProjectWorldLocationToScreen"].Object, &params);
	return params.ScreenLocation;
}

APlayerController* ULocalPlayer::PlayerController() {
	if (!(uintptr_t)this)
		return 0;
	return *(APlayerController**)((uintptr_t)this + 0x30);
}

ULocalPlayer* UGameInstance::LocalPlayer() {
	if (!(uintptr_t)this)
		return 0;
	return *(ULocalPlayer**)(*(ULocalPlayer**)((uintptr_t)this + 0x38));
}

UGameInstance* UWorld::OwningGameInstance() {
	if (!(uintptr_t)this)
		return 0;

	struct {
		class UObject* WorldContextObject;                                       
		class UGameInstance* ReturnValue;                                              
	} params;
	params.WorldContextObject = (UObject*)this;
	ProcessEvent(Objects["GameplayStatics"].Object, (UObject*)Objects["GetGameInstance"].Object, &params);
	return params.ReturnValue;
}

TArray<ULevel*> UWorld::Levels() {
	if (!(uintptr_t)this)
		return {};
	return *(TArray<ULevel*>*)((uintptr_t)this + 0x170);
}

ULevel* UWorld::PersistentLevel() {
	if (!(uintptr_t)this)
		return 0;
	return *(ULevel**)((uintptr_t)this + 0x30);
}