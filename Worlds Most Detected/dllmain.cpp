#include <Windows.h>

#include "SDK/Addresses/Sigs.h"
#include "Util.h"
#include "SDK/Addresses/Objects.h"
#include "SDK/EngineFunctions.h"
#include "Render/Render.h"

#pragma comment(lib, "Libraries/PolyHook_2.lib")
#pragma comment(lib, "Libraries/capstone.lib")
#pragma comment(lib, "Libraries/Zycore.lib")
#pragma comment(lib, "Libraries/Zydis.lib")

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "Winmm.lib")

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	if (reason != DLL_PROCESS_ATTACH) return FALSE;
	CreateConsole();
	FetchSigs();
	FetchObjects();
	StartInitDX11();

	return TRUE;
}

