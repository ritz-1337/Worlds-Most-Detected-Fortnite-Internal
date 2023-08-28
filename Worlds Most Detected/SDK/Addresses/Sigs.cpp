#include "Sigs.h"
#include "Helper/SigScanner.h"
#include <iostream>
#include <Windows.h>

void FetchSigs() {
    auto base = (uintptr_t)GetModuleHandleA(0);
    for (auto& Sig : Sigs) {
        Sig.second.Value = PatternScan(Sig.second.Signature.c_str(), Sig.second.RVA);
        std::cout << Sig.first << ": " << std::hex <<  Sig.second.Value - base << std::endl;
        auto ErrorCode = "Error Failed to Find: " + Sig.first;
        if (!Sig.second.Value)
            MessageBoxA(0, ErrorCode.c_str(), 0, 0);
        
    }
}
