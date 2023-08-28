
#include "Polyhook2/Detour/x64Detour.hpp"
#include "Polyhook2/ZydisDisassembler.hpp"
#include "Polyhook2/CapstoneDisassembler.hpp"


inline PLH::ZydisDisassembler dis(PLH::Mode::x64);

inline bool PolyHookDetour(char* fnAddress, char* fnCallback,
	uint64_t* userTrampVar)
{
	auto Detour = std::make_unique<PLH::x64Detour>(
		fnAddress, fnCallback, userTrampVar,
		dis);

	return Detour->hook();
}