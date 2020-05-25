#pragma once
#include "DrawableGameEntity.h"

namespace Rendering
{
	class TexturedCube final: public Library_3::DrawableGameEntity
	{
	public:
		TexturedCube(Library_3::Game& game);
		~TexturedCube() = default;

		TexturedCube() = delete;

		TexturedCube(const TexturedCube& rhs) = delete;
		TexturedCube& operator=(const TexturedCube& rhs) = delete;

		TexturedCube(const TexturedCube&&rhs) = delete;
		TexturedCube& operator=(const TexturedCube&& rhs) = delete;

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
		ID3D11ShaderResourceView* mCubeTextureSRV;

		std::uint16_t mIndexCount;
	};
}