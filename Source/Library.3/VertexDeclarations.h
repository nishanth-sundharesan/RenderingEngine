#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Library_3
{
	struct VertexPosition
	{
		XMFLOAT3 Position;

		VertexPosition() = default;

		VertexPosition(const XMFLOAT3& position)
			: Position(position) { }
	};

	struct VertexPositionColor
	{
		XMFLOAT3 Position;
		XMFLOAT4 Color;

		VertexPositionColor() = default;

		VertexPositionColor(const XMFLOAT3& position, const XMFLOAT4& color)
			: Position(position), Color(color) { }
	};

	struct VertexPositionTexture
	{
		XMFLOAT3 Position;
		XMFLOAT2 UV;

		VertexPositionTexture() = default;

		VertexPositionTexture(const XMFLOAT3& position, const XMFLOAT2& uv)
			: Position(position), UV(uv) { }
	};
}