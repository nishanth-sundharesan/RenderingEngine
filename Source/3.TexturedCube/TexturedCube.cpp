#include "Pch.h"
#include "TexturedCube.h"

#include "Game.h"
#include "Utility.h"
#include "VertexDeclarations.h"
#include "ColorHelper.h"

using namespace Library_3;

namespace Rendering
{
	TexturedCube::TexturedCube(Game& game) :
		DrawableGameEntity(game),
		mVertexShader(nullptr),
		mPixelShader(nullptr),
		mInputLayout(nullptr),
		mVertexBuffer(nullptr),
		mCubeTextureSRV(nullptr),
		mIndexCount(0)
	{
	}

	void TexturedCube::Initialize()
	{
		// Load a compiled vertex shader
		std::vector<char> compiledVertexShader;
		Utility::LoadBinaryFile("Shaders\\TexturedCube_VS.cso", compiledVertexShader);
		ThrowIfFailed(
			mGame->GetDirect3DDevice()->CreateVertexShader(
				&compiledVertexShader[0],
				compiledVertexShader.size(),
				nullptr,
				&mVertexShader),
			"ID3D11Device::CreatedVertexShader() failed.");

		// Load a compiled pixel shader
		std::vector<char> compiledPixelShader;
		Utility::LoadBinaryFile("Shaders\\TexturedCube_PS.cso", compiledPixelShader);
		ThrowIfFailed(
			mGame->GetDirect3DDevice()->CreatePixelShader(
				&compiledPixelShader[0],
				compiledPixelShader.size(),
				nullptr,
				&mPixelShader),
			"ID3D11Device::CreatedPixelShader() failed.");

		// Create the input layout
		D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		ThrowIfFailed(
			mGame->GetDirect3DDevice()->CreateInputLayout(
				inputElementDescriptions,
				ARRAYSIZE(inputElementDescriptions),
				&compiledVertexShader[0],
				compiledVertexShader.size(),
				&mInputLayout),
			"ID3D11Device::CreateInputLayout() failed.");


		// Create a vertex buffer and initialize data
		VertexPositionTexture vertices[] =
		{
			VertexPositionTexture(XMFLOAT3(-1.0f, -1.0f, 1.0f),  XMFLOAT2(  0.0f, 0.0f)),    // Side 1
			VertexPositionTexture(XMFLOAT3(1.0f, -1.0f, 1.0f),   XMFLOAT2(  0.0f, 1.0f)),
			VertexPositionTexture(XMFLOAT3(-1.0f, 1.0f, 1.0f),   XMFLOAT2(  1.0f, 0.0f)),
			VertexPositionTexture(XMFLOAT3(1.0f, 1.0f, 1.0f),    XMFLOAT2(  1.0f, 1.0f)),
															
			VertexPositionTexture(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(  0.0f, 0.0f)),    // Side 2
			VertexPositionTexture(XMFLOAT3(-1.0f, 1.0f, -1.0f),  XMFLOAT2(  0.0f, 1.0f)),
			VertexPositionTexture(XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT2(  1.0f, 0.0f)),
			VertexPositionTexture(XMFLOAT3(1.0f, 1.0f, -1.0f),   XMFLOAT2(  1.0f, 1.0f)),
															
			VertexPositionTexture(XMFLOAT3(-1.0f, 1.0f, -1.0f),  XMFLOAT2(  0.0f, 0.0f)),    // Side 3
			VertexPositionTexture(XMFLOAT3(-1.0f, 1.0f, 1.0f),   XMFLOAT2(  0.0f, 1.0f)),
			VertexPositionTexture(XMFLOAT3(1.0f, 1.0f, -1.0f),   XMFLOAT2(  1.0f, 0.0f)),
			VertexPositionTexture(XMFLOAT3(1.0f, 1.0f, 1.0f),    XMFLOAT2(  1.0f, 1.0f)),
															
			VertexPositionTexture(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(  0.0f, 0.0f)),    // Side 4
			VertexPositionTexture(XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT2(  0.0f, 1.0f)),
			VertexPositionTexture(XMFLOAT3(-1.0f, -1.0f, 1.0f),  XMFLOAT2(  1.0f, 0.0f)),
			VertexPositionTexture(XMFLOAT3(1.0f, -1.0f, 1.0f),   XMFLOAT2(  1.0f, 1.0f)),
															
			VertexPositionTexture(XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT2(  0.0f, 0.0f)),    // Side 5
			VertexPositionTexture(XMFLOAT3(1.0f, 1.0f, -1.0f),   XMFLOAT2(  0.0f, 1.0f)),
			VertexPositionTexture(XMFLOAT3(1.0f, -1.0f, 1.0f),   XMFLOAT2(  1.0f, 0.0f)),
			VertexPositionTexture(XMFLOAT3(1.0f, 1.0f, 1.0f),    XMFLOAT2(  1.0f, 1.0f)),
															
			VertexPositionTexture(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(  0.0f, 0.0f)),    // Side 6
			VertexPositionTexture(XMFLOAT3(-1.0f, -1.0f, 1.0f),  XMFLOAT2(  0.0f, 1.0f)),
			VertexPositionTexture(XMFLOAT3(-1.0f, 1.0f, -1.0f),  XMFLOAT2(  1.0f, 0.0f)),
			VertexPositionTexture(XMFLOAT3(-1.0f, 1.0f, 1.0f),   XMFLOAT2(  1.0f, 1.0f)),
		};
		
		D3D11_BUFFER_DESC vertexBufferDescription;
		ZeroMemory(&vertexBufferDescription, sizeof(vertexBufferDescription));
		vertexBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;									// Not providing any write access to GPU or CPU. Read access only to GPU
		vertexBufferDescription.ByteWidth = sizeof(VertexPositionTexture) * ARRAYSIZE(vertices);
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;							// Bind as a vertex buffer		

		D3D11_SUBRESOURCE_DATA vertexSubResourceData;
		ZeroMemory(&vertexSubResourceData, sizeof(vertexSubResourceData));
		vertexSubResourceData.pSysMem = vertices;

		ThrowIfFailed(mGame->GetDirect3DDevice()->CreateBuffer(&vertexBufferDescription, &vertexSubResourceData, &mVertexBuffer), "ID3D11Device::CreateBuffer() failed.");
		
		// Create an index buffer and initialize data		
		const uint16_t indices[] =
		{
			0, 1, 2,		// Side 1
			2, 1, 3,

			4, 5, 6,		// Side 2
			6, 5, 7,

			8, 9, 10,       // Side 3
			10, 9, 11,

			12, 13, 14,		// Side 4
			14, 13, 15,

			16, 17, 18,     // Side 5
			18, 17, 19,

			20, 21, 22,     // Side 6
			22, 21, 23,
		};

		mIndexCount = ARRAYSIZE(indices);

		D3D11_BUFFER_DESC indexBufferDescription { 0 };
		indexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDescription.ByteWidth = sizeof(uint16_t) * mIndexCount;
		indexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexSubresourceData;
		indexSubresourceData.pSysMem = indices;
		ThrowIfFailed(mGame->GetDirect3DDevice()->CreateBuffer(&indexBufferDescription, &indexSubresourceData, &mIndexBuffer), "ID3D11Device::CreateBuffer() failed.");


		// Create a constant buffer
		D3D11_BUFFER_DESC constantBufferDescription;
		ZeroMemory(&constantBufferDescription, sizeof(constantBufferDescription));
		constantBufferDescription.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDescription.ByteWidth = 64;								// 64 bytes is the size of 4x4 matrix
		constantBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		

		ThrowIfFailed(mGame->GetDirect3DDevice()->CreateBuffer(&constantBufferDescription, nullptr, &mConstantBuffer), "ID3D11Device::CreateBuffer() failed.");	

		// Load a texture
		const std::wstring textureName = L"Content\\Textures\\BrickWall.jpg";
		ThrowIfFailed(CreateWICTextureFromFile(mGame->GetDirect3DDevice(), textureName.c_str(), nullptr, &mCubeTextureSRV), "CreateWICTextureFromFile() failed.");
	}

	void TexturedCube::Draw()
	{
		ID3D11DeviceContext* direct3DDeviceContext = mGame->GetDirect3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		direct3DDeviceContext->IASetInputLayout(mInputLayout);
		
		// Bind the vertex buffer array to input assembly.
		UINT stride = sizeof(VertexPositionTexture);
		UINT offset = 0;
		direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

		// Bind the index buffer array to input assembly.
		direct3DDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);		

		// Set the shader objects
		direct3DDeviceContext->VSSetShader(mVertexShader, 0, 0);
		direct3DDeviceContext->PSSetShader(mPixelShader, 0, 0);

		// Set the constant buffer used by the vertex shader pipeline stage.
		direct3DDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);

		// Set the texture SRV
		direct3DDeviceContext->PSSetShaderResources(0, 1, &mCubeTextureSRV);
		
		// World Matrix
		XMMATRIX worldMatrix = XMMatrixIdentity();

		// View Matrix
		XMVECTOR cameraPosition = XMVectorSet(5.0f, 5.0f, -10.f, 0);
		XMVECTOR cameraLookAt = XMVectorReplicate(0.0f);
		XMVECTOR cameraUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		XMMATRIX viewMatrix = XMMatrixLookAtLH(cameraPosition, cameraLookAt, cameraUp);

		// (We are using left-handed coordinate system LH, and hence the camera position is set to -ve value because we are pulling it 
		// away from the screen. This perspective camera should also set the depth values from 0 to 1. For the depth to be inversed a different
		// perspective function should be called, but I don't think that is available from DirectX Math library.)
		// Read https://developer.nvidia.com/content/depth-precision-visualized regarding inverse z values.

		// Projection Matrix
		XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(45), static_cast<float>(mGame->GetScreenWidth()) / mGame->GetScreenHeight(), 0.1f, 100.0f);

		XMMATRIX worldViewProjectionMatrix = worldMatrix * viewMatrix * projectionMatrix;
		mGame->GetDirect3DDeviceContext()->UpdateSubresource(mConstantBuffer, 0, 0, &worldViewProjectionMatrix, 0, 0);
		direct3DDeviceContext->DrawIndexed(mIndexCount, 0, 0);
	}

	void TexturedCube::Shutdown()
	{
		ReleaseObject(mVertexBuffer)
		ReleaseObject(mPixelShader)
		ReleaseObject(mInputLayout)
		ReleaseObject(mVertexShader)
		ReleaseObject(mCubeTextureSRV)
	}
}