#pragma once
#include <string>
#include "Helper/SigScanner.h"
#include <map>

inline std::string GWorldSig = "48 89 05 ? ? ? ? 0F 28 D7";
inline std::string StaticFindObjectSig = "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8B EC 48 83 EC 60 33 DB 4C 8B F9 48 8D 4D";


struct SigData {
    std::string Signature;
    int RVA;
    uintptr_t Value;
};

inline std::map<std::string, SigData> Sigs = {
        {"GWorld", {GWorldSig, 7, 0}},
        {"StaticFindObject", {StaticFindObjectSig, 0, 0}}
};

void FetchSigs();