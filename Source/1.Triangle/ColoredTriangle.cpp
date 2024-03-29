#include "Pch.h"
#include "ColoredTriangle.h"

#include "Game.h"
#include "Utility.h"
#include "VertexDeclarations.h"
#include "ColorHelper.h"

using namespace Library;

namespace Rendering
{
	ColoredTriangle::ColoredTriangle(Game& game) :
		DrawableGameEntity(game),
		mVertexShader(nullptr),
		mPixelShader(nullptr),
		mInputLayout(nullptr),
		mVertexBuffer(nullptr)
	{
	}

	void ColoredTriangle::Initialize()
	{
		// Load a compiled vertex shader
		std::vector<char> compiledVertexShader;
		Utility::LoadBinaryFile("Shaders\\ColoredTriangle_VS.cso", compiledVertexShader);
		ThrowIfFailed(
			mGame->GetDirect3DDevice()->CreateVertexShader(
				&compiledVertexShader[0],
				compiledVertexShader.size(),
				nullptr,
				&mVertexShader),
			"ID3D11Device::CreatedVertexShader() failed.");

		// Load a compiled pixel shader
		std::vector<char> compiledPixelShader;
		Utility::LoadBinaryFile("Shaders\\ColoredTriangle_PS.cso", compiledPixelShader);
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
			VertexPositionColor(XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(ColorHelper::Red)),
			VertexPositionColor(XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(ColorHelper::Green)),
			VertexPositionColor(XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(ColorHelper::Blue))
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
	}

	void ColoredTriangle::Draw()
	{
		ID3D11DeviceContext* direct3DDeviceContext = mGame->GetDirect3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		direct3DDeviceContext->IASetInputLayout(mInputLayout);

		// Bind the vertex buffer array to input assembly.
		UINT stride = sizeof(VertexPositionColor);
		UINT offset = 0;
		direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

		// Set the shader objects
		direct3DDeviceContext->VSSetShader(mVertexShader, 0, 0);
		direct3DDeviceContext->PSSetShader(mPixelShader, 0, 0);		

		direct3DDeviceContext->Draw(3, 0);	// 3 is the total number of vertices.		
	}

	void ColoredTriangle::Shutdown()
	{
		ReleaseObject(mVertexBuffer)
		ReleaseObject(mPixelShader)
		ReleaseObject(mInputLayout)
		ReleaseObject(mVertexShader)
	}
}