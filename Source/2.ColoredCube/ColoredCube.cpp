#include "Pch.h"
#include "ColoredCube.h"

#include "Game.h"
#include "Utility.h"
#include "VertexDeclarations.h"
#include "ColorHelper.h"

using namespace Library;

namespace Rendering
{
	ColoredCube::ColoredCube(Game& game) :
		DrawableGameEntity(game),
		mVertexShader(nullptr),
		mPixelShader(nullptr),
		mInputLayout(nullptr),
		mVertexBuffer(nullptr),		
		mIndexCount(0)
	{
	}

	void ColoredCube::Initialize()
	{
		// Load a compiled vertex shader
		std::vector<char> compiledVertexShader;
		Utility::LoadBinaryFile("Shaders\\VertexShader.cso", compiledVertexShader);
		ThrowIfFailed(
			mGame->GetDirect3DDevice()->CreateVertexShader(
				&compiledVertexShader[0],
				compiledVertexShader.size(),
				nullptr,
				&mVertexShader),
			"ID3D11Device::CreatedVertexShader() failed.");

		// Load a compiled pixel shader
		std::vector<char> compiledPixelShader;
		Utility::LoadBinaryFile("Shaders\\PixelShader.cso", compiledPixelShader);
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
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
		VertexPositionColor vertices[] =
		{
			VertexPositionColor(XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(ColorHelper::Green)),
			VertexPositionColor(XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(ColorHelper::Yellow)),
			VertexPositionColor(XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(ColorHelper::White)),
			VertexPositionColor(XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(ColorHelper::BlueGreen)),

			VertexPositionColor(XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(ColorHelper::Blue)),
			VertexPositionColor(XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(ColorHelper::Purple)),
			VertexPositionColor(XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(ColorHelper::Red)),
			VertexPositionColor(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(ColorHelper::Black))
		};
		
		D3D11_BUFFER_DESC vertexBufferDescription;
		ZeroMemory(&vertexBufferDescription, sizeof(vertexBufferDescription));
		vertexBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;									// Not providing any write access to GPU or CPU. Read access only to GPU
		vertexBufferDescription.ByteWidth = sizeof(VertexPositionColor) * ARRAYSIZE(vertices);
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;							// Bind as a vertex buffer		

		D3D11_SUBRESOURCE_DATA vertexSubResourceData;
		ZeroMemory(&vertexSubResourceData, sizeof(vertexSubResourceData));
		vertexSubResourceData.pSysMem = vertices;

		ThrowIfFailed(mGame->GetDirect3DDevice()->CreateBuffer(&vertexBufferDescription, &vertexSubResourceData, &mVertexBuffer), "ID3D11Device::CreateBuffer() failed.");


		// Create an index buffer and initialize data		
		const uint16_t indices[] =
		{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			3, 2, 5,
			3, 5, 4,

			2, 1, 6,
			2, 6, 5,

			1, 7, 6,
			1, 0, 7,

			0, 3, 4,
			0, 4, 7
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
	}

	void ColoredCube::Draw()
	{
		ID3D11DeviceContext* direct3DDeviceContext = mGame->GetDirect3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		direct3DDeviceContext->IASetInputLayout(mInputLayout);
		
		// Bind the vertex buffer array to input assembly.
		UINT stride = sizeof(VertexPositionColor);
		UINT offset = 0;
		direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

		// Bind the index buffer array to input assembly.
		direct3DDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		// Set the constant buffer used by the vertex shader pipeline stage.
		mGame->GetDirect3DDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);

		// Set the shader objects
		direct3DDeviceContext->VSSetShader(mVertexShader, 0, 0);
		direct3DDeviceContext->PSSetShader(mPixelShader, 0, 0);
		
		// World Matrix
		XMMATRIX worldMatrix = XMMatrixIdentity();

		// View Matrix
		XMVECTOR cameraPosition = XMVectorSet(2.0f, 0.0f, 10.f, 0);
		XMVECTOR cameraLookAt = XMVectorReplicate(0.0f);
		XMVECTOR cameraUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		XMMATRIX viewMatrix = XMMatrixLookAtLH(cameraPosition, cameraLookAt, cameraUp);

		// Projection Matrix
		XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(45), static_cast<float>(mGame->GetScreenWidth()) / mGame->GetScreenHeight(), 0.1f, 100.0f);

		XMMATRIX worldViewProjectionMatrix1 = worldMatrix * viewMatrix * projectionMatrix;
		mGame->GetDirect3DDeviceContext()->UpdateSubresource(mConstantBuffer, 0, 0, &worldViewProjectionMatrix1, 0, 0);
		direct3DDeviceContext->DrawIndexed(mIndexCount, 0, 0);
	}

	void ColoredCube::Shutdown()
	{
		ReleaseObject(mVertexBuffer)
		ReleaseObject(mPixelShader)
		ReleaseObject(mInputLayout)
		ReleaseObject(mVertexShader)
	}
}