#pragma once
#include <string>
#include <locale>
#include <cstdint>
#include <corecrt_wstring.h>
#include <iostream>
#include <Windows.h>

inline int screen_width = GetSystemMetrics(SM_CXSCREEN);
inline int screen_height = GetSystemMetrics(SM_CYSCREEN);

class Vector2
{
public:
	Vector2() : x(0.f), y(0.f)
	{

	}

	Vector2(double _x, double _y) : x(_x), y(_y)
	{

	}
	~Vector2()
	{

	}

	double x;
	double y;
	Vector2 operator-(const Vector2& Other) const
	{
		return Vector2(x - Other.x, y - Other.y);
	}
	double magnitude() const {
		return std::sqrt(x * x + y * y);
	}
	inline double distance(Vector2 v)
	{
		return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0)));
	}
	/*inline ImVec2 ConvImVec2()
	{
		return ImVec2(x, y);
	}*/
	inline bool valid_location() {
		if (x > screen_width or y > screen_height)
			return false;
		else if (x <= 0 or y <= 0)
			return false;
		else if (std::isnan(x) or std::isnan(y))
			return false;
		else
			return true;

	}

};

class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	double x;
	double y;
	double z;

	inline double dot(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline double distance(Vector3 v)
	{
		return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline double length() {
		return sqrt(x * x + y * y + z * z);
	}

	Vector3 operator+(const Vector3& Other) const
	{
		return Vector3(x + Other.x, y + Other.y, z + Other.z);
	}

	Vector3 operator-(const Vector3& Other) const
	{
		return Vector3(x - Other.x, y - Other.y, z - Other.z);
	}

	Vector3 operator*(const Vector3& Other) const
	{
		return Vector3(x * Other.x, y * Other.y, z * Other.z);
	}

	Vector3 operator/(const Vector3& Other) const
	{
		return Vector3(x / Other.x, y / Other.y, z / Other.z);
	}

	Vector3 operator*(float Scalar) const
	{
		return Vector3(x * Scalar, y * Scalar, z * Scalar);
	}

	Vector3 operator/(float Scalar) const
	{
		return Vector3(x / Scalar, y / Scalar, z / Scalar);
	}
	static Vector3 multiplyMat3(const Vector3& c0, const Vector3& c1, const Vector3& c2, const Vector3& v) {
		return Vector3(c0.dot(v), c1.dot(v), c2.dot(v));
	}

};
struct FMatrix
{
	double M[4][4];


};
static FMatrix* myMatrix = new FMatrix();

template<class T>
struct TArray
{
	friend struct FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline bool IsValidIndex(int i) const
	{
		return i >= 0 && i < Num() && Data != nullptr;
	}

private:
	T* Data;
	int32_t Count;
	int32_t Max;
};

struct FString : private TArray<wchar_t>
{
public:
	FString();
	FString(const wchar_t* other);
	bool IsValid() const;
	const wchar_t* c_str() const;
	std::string ToString() const;
};

struct FName
{
	uint32_t ComparisonIndex;
	uint32_t DisplayIndex;
};

struct FKey
{
	FName KeyName;
	unsigned char Padding_00[0x10];
};

// ScriptStruct CoreUObject.LinearColor
// 0x0010
struct FLinearColor
{
	float                                              R;                                                        // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              G;                                                        // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              B;                                                        // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              A;                                                        // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	inline FLinearColor()
		: R(0), G(0), B(0), A(0)
	{ }

	inline FLinearColor(float r, float g, float b, float a)
		: R(r),
		G(g),
		B(b),
		A(a)
	{ }

};
struct FRotator
{
	double Pitch;
	double Yaw;
	double Roll;
};
struct Quat
{
	double                                             X;                                                        // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             Y;                                                        // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             Z;                                                        // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             W;                                                        // 0x0018(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
};
struct FMinimalViewInfo {
	Vector3 Location;
	Vector3 Rotation;
	float FOV;
	float OrthoWidth;
	float OrthoNearClipPlane;
	float OrthoFarClipPlane;
	float AspectRatio;
};


class FTextData {
public:
	char pad_0x0000[0x38];      // 0x0000
	wchar_t* Name;              // 0x0038
	__int32 Length;             // 0x0040

};

struct FText {
	FTextData* Data;
	char UnknownData[0x10];
	wchar_t* Get();
};
class UClass {
public:
	BYTE _padding_0[0x40];
	UClass* SuperClass;
};

class UObject {
public:
	PVOID VTableObject;
	DWORD ObjectFlags;
	DWORD InternalIndex;
	UClass* Class;
	BYTE _padding_0[0x8];
	UObject* Outer;

	inline BOOLEAN IsA(PVOID parentClass)
	{
		for (auto super = this->Class; super; super = super->SuperClass)
			if (super == parentClass)
				return true;

		return false;
	}
};
struct FPawnHighlight
{
	float                                              Priority;                                                 // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                Inner;                                                    // 0x0004(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                Outer;                                                    // 0x0014(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              FresnelBrightness;                                        // 0x0024(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              FresnelExponent;                                          // 0x0028(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              UsesPulse;                                                // 0x002C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};