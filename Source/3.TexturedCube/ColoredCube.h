#pragma once
#include "DrawableGameEntity.h"

namespace Rendering
{
	class ColoredCube final: public Library_3::DrawableGameEntity
	{
	public:
		ColoredCube(Library_3::Game& game);
		~ColoredCube() = default;

		ColoredCube() = delete;

		ColoredCube(const ColoredCube& rhs) = delete;
		ColoredCube& operator=(const ColoredCube& rhs) = delete;

		ColoredCube(const ColoredCube&&rhs) = delete;
		ColoredCube& operator=(const ColoredCube&& rhs) = delete;

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