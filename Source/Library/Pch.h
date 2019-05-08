#pragma once

// Windows libraries
#include <windows.h>

// DirectX library
#include <d3d11_1.h>

#include <string>
#include <cstdint>

#include "GameException.h"

#define DeleteObject(object) if((object) != nullptr) { delete object; object = nullptr; }
#define DeleteObjects(objects) if((objects) != nullptr) { delete[] objects; objects = nullptr; }
#define ReleaseObject(object) if((object) != nullptr) { object->Release(); object = nullptr; }