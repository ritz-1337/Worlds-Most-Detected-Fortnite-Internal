#pragma once
#include <Windows.h>
#include "SDK/Math/Structs.h"

typedef struct final {
	bool ShowMenu = true;
	FPawnHighlight PawnHighlight;
} SETTINGS;

inline SETTINGS Settings;

VOID LoadSavedConfig();
VOID SaveConfig();