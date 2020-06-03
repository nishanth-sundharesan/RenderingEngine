#pragma once
#include "DrawableGameEntity.h"

namespace Rendering
{
	class ColoredCubeCube final: public Library::DrawableGameEntity
	{
	public:
		ColoredCubeCube(Library::Game& game);
		~ColoredCubeCube() = default;

		ColoredCubeCube() = delete;

		ColoredCubeCube(const ColoredCubeCube& rhs) = delete;
		ColoredCubeCube& operator=(const ColoredCubeCube& rhs) = delete;

		ColoredCubeCube(const ColoredCubeCube&&rhs) = delete;
		ColoredCubeCube& operator=(const ColoredCubeCube&& rhs) = delete;

		virtual void Initialize() override;
		virtual void Draw() override;
		virtual void Shutdown() override;

	private:
		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader* mPixelShader;
		ID3D11InputLayout* mInputLayout;
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mConstantBuffer;
		ID3D11Buffer* mIndexBuffer;
		
		std::uint16_t mIndexCount;
	};
}