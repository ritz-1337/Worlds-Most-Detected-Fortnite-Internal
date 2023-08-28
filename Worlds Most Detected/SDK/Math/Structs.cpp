#include "Structs.h"


FString::FString()
{
}

FString::FString(const wchar_t* other)
{
	Max = Count = *other ? wcslen(other) + 1 : 0;

	if (Count)
	{
		Data = const_cast<wchar_t*>(other);
	}
}

bool FString::IsValid() const
{
	return Data != nullptr;
}

const wchar_t* FString::c_str() const
{
	return Data;
}

std::string FString::ToString() const
{
	auto length = std::wcslen(Data);

	std::string str(length, '\0');

	std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

	return str;
}

wchar_t* FText::Get() {
	if (Data) {
		return Data->Name;
	}

	return nullptr;
}
