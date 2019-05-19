#pragma once

// Windows libraries
#include <windows.h>

// DirectX library
#include <d3d11_1.h>

// DirectX SIMD math library
#include <DirectXMath.h>

// Std libraries
#include <vector>
#include <cstdint>

using namespace DirectX;	// For DirectXMath library

#define DeleteObject(object) if((object) != nullptr) { delete object; object = nullptr; }
#define DeleteObjects(objects) if((objects) != nullptr) { delete[] objects; objects = nullptr; }
#define ReleaseObject(object) if((object) != nullptr) { object->Release(); object = nullptr; }