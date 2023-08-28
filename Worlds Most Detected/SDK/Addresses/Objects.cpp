#include "Objects.h"
#include "../EngineFunctions.h"
#include <Windows.h>

void FetchObjects() {
	for (auto& Object : Objects) {
		std::string temp_string(Object.second.Name.c_str());
		std::wstring temp_wstring(temp_string.begin(), temp_string.end());
		Object.second.Object = StaticFindObject(temp_wstring.c_str());
		std::cout << Object.first << ": " << Object.second.Object << std::endl;
	}
}