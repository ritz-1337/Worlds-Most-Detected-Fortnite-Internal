#include "VTableHook.h"

void VTableHook::Hook(void* instance, int functionIndex, void* hookFunction) {
    if (!instance)
        return;

    HookData& hookData = hookedInstances[instance];
    if (hookData.isHooked)
        return;

    hookData.originalVtable = *(void***)instance;
    size_t vtableSize = GetVTableSize(hookData.originalVtable);
    hookData.hookedVtable = new void* [vtableSize];

    // Copy original vtable
    std::copy(hookData.originalVtable, hookData.originalVtable + vtableSize, hookData.hookedVtable);

    // Hook the desired function
    hookData.hookedVtable[functionIndex] = hookFunction;

    // Replace vtable pointer
    *(void***)instance = hookData.hookedVtable;

    hookData.isHooked = true;
}
void VTableHook::Unhook(void* instance) {
    auto it = hookedInstances.find(instance);
    if (it == hookedInstances.end())
        return;

    HookData& hookData = it->second;
    if (!hookData.isHooked)
        return;

    // Restore the original vtable
    *(void***)instance = hookData.originalVtable;
    delete[] hookData.hookedVtable;

    hookData.originalVtable = nullptr;
    hookData.hookedVtable = nullptr;
    hookData.isHooked = false;

    hookedInstances.erase(it);
}
size_t VTableHook::GetVTableSize(void** vtable) {
    size_t count = 0;
    while (vtable[count])
        count++;
    return count;
}