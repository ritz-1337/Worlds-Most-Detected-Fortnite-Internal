#include "SigScanner.h"
//#include <libloaderapi.h>
#include <vector>
//#include <processthreadsapi.h>
#include <Psapi.h>
#define RELATIVE(addr, size) ((uintptr_t)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))
uintptr_t PatternScan(const char* sSignature, int pIndex)
{
	//static auto pModuleBaseAddress = GetModuleHandleA(0);
    static bool bIsSetted = false;

    static MODULEINFO info = { 0 };

    if (!bIsSetted)
    {
        GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info));
        bIsSetted = true;
    }
    auto pModuleBaseAddress = (uintptr_t)info.lpBaseOfDll;
	/*static auto patternToByte = [](const char* pattern) { auto bytes = std::vector<int>{}; const auto start = const_cast<char*>(pattern); const auto end = const_cast<char*>(pattern) + strlen(pattern); for (auto current = start; current < end; ++current) { if (*current == '?') { ++current; if (*current == '?') ++current; bytes.push_back(-1); } else bytes.push_back(strtoul((const char*)current, &current, 16)); } return bytes; };

	const auto dosHeader = (PIMAGE_DOS_HEADER)pModuleBaseAddress;
	const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)pModuleBaseAddress + dosHeader->e_lfanew);

	const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = patternToByte(sSignature);
	const auto scanBytes = reinterpret_cast<std::uint8_t*>(pModuleBaseAddress);

	const auto s = patternBytes.size();
	const auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i) {
		bool found = true; for (auto j = 0ul; j < s; ++j) { if (scanBytes[i + j] != d[j] && d[j] != -1) { found = false; break; } }
		if (found)
		{
			if (pIndex > 0)
			{
				return ((uintptr_t)((UINT_PTR)(reinterpret_cast<uintptr_t>(&scanBytes[i])) + *(PINT)((UINT_PTR)(reinterpret_cast<uintptr_t>(&scanBytes[i])) + ((pIndex)-sizeof(INT))) + (pIndex)));
			}
			else
			{
				return reinterpret_cast<uintptr_t>(&scanBytes[i]);
			}
		}
	}*/
    static auto patternToByte = [](const char* pattern)
    {
        auto       bytes = std::vector<int>{};
        const auto start = const_cast<char*>(pattern);
        const auto end = const_cast<char*>(pattern) + strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    const auto dosHeader = (PIMAGE_DOS_HEADER)pModuleBaseAddress;
    const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)pModuleBaseAddress + dosHeader->e_lfanew);

    const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto       patternBytes = patternToByte(sSignature);
    const auto scanBytes = reinterpret_cast<std::uint8_t*>(pModuleBaseAddress);

    const auto s = patternBytes.size();
    const auto d = patternBytes.data();

    size_t nFoundResults = 0;

    for (auto i = 0ul; i < sizeOfImage - s; ++i)
    {
        bool found = true;

        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            auto resilt = reinterpret_cast<uintptr_t>(&scanBytes[i]);
            if (pIndex > 0)
                resilt = RELATIVE(resilt, pIndex);
            return resilt;      // Default/First Result.
        }
    }
    return 0;
}