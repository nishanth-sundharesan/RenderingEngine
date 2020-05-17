#pragma once

#include <DirectXMath.h>

namespace Library_3
{
	class ColorHelper final
	{
	public:
		static const DirectX::XMVECTORF32 Black;
		static const DirectX::XMVECTORF32 White;
		static const DirectX::XMVECTORF32 Red;
		static const DirectX::XMVECTORF32 Green;
		static const DirectX::XMVECTORF32 Blue;
		static const DirectX::XMVECTORF32 Yellow;
		static const DirectX::XMVECTORF32 BlueGreen;
		static const DirectX::XMVECTORF32 Purple;
		static const DirectX::XMVECTORF32 CornflowerBlue;
		static const DirectX::XMVECTORF32 Wheat;
		static const DirectX::XMVECTORF32 LightGray;

		/*static XMFLOAT4 RandomColor();*/

		ColorHelper() = delete;
		~ColorHelper() = delete;

		ColorHelper(const ColorHelper& rhs) = delete;
		ColorHelper& operator=(const ColorHelper& rhs) = delete;

		ColorHelper(const ColorHelper&& rhs) = delete;
		ColorHelper& operator=(const ColorHelper&& rhs) = delete;
	};
}