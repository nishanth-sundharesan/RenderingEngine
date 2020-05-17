#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Library_3
{
	struct VertexPosition
	{
		XMFLOAT3 Position;

		VertexPosition() { }

		VertexPosition(const XMFLOAT3& position)
			: Position(position) { }
	};

	struct VertexPositionColor
	{
		XMFLOAT3 Position;
		XMFLOAT4 Color;

		VertexPositionColor() { }

		VertexPositionColor(const XMFLOAT3& position, const XMFLOAT4& color)
			: Position(position), Color(color) { }
	};
}