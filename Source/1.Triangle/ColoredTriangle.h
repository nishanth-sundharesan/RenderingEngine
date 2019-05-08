#pragma once
#include "DrawableGameEntity.h"

namespace Rendering
{
	class ColoredTriangle : public Library::DrawableGameEntity
	{
	public:
		ColoredTriangle(Library::Game& game);
		~ColoredTriangle() = default;

		ColoredTriangle() = delete;

		ColoredTriangle(const ColoredTriangle& rhs) = delete;
		ColoredTriangle& operator=(const ColoredTriangle& rhs) = delete;

		ColoredTriangle(const ColoredTriangle&&rhs) = delete;
		ColoredTriangle& operator=(const ColoredTriangle&& rhs) = delete;

		virtual void Initialize() override;
		virtual void Draw() override;
		virtual void Shutdown() override;

	private:
		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader* mPixelShader;
		ID3D11InputLayout* mInputLayout;
		ID3D11Buffer* mVertexBuffer;
	};
}