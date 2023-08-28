#pragma once

#include <unordered_map>
class VTableHook {
private:
    struct HookData {
        void** originalVtable;
        void** hookedVtable;
        bool isHooked;
    };

    std::unordered_map<void*, HookData> hookedInstances;

public:
    void Hook(void* instance, int functionIndex, void* hookFunction);
    void Unhook(void* instance);

private:
    size_t GetVTableSize(void** vtable);
};
inline VTableHook* VTableHooker = new VTableHook;
