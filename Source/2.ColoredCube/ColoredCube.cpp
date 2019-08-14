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
		mTime(0.0f)
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


		D3D11_BUFFER_DESC constantBufferDescription;
		ZeroMemory(&constantBufferDescription, sizeof(constantBufferDescription));

		constantBufferDescription.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDescription.ByteWidth = 64;
		constantBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		


		mGame->GetDirect3DDevice()->CreateBuffer(&constantBufferDescription, nullptr, &mConstantBuffer);
		mGame->GetDirect3DDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	}

	void ColoredCube::Draw()
	{
		mTime += 0.005f;


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

		
		// World Matrix		
		XMMATRIX worldMatrix1 = XMMatrixRotationY(180.0f);// *XMMatrixTranslation(1.0f, 1.0f, 0.5f);
		XMMATRIX translationMatrix2 = XMMatrixTranslation(0.0f, 0.0f, -5.0f);
		
		 

		XMMATRIX rotationMatrix = XMMatrixRotationY(mTime);
		XMMATRIX translationMatrix = XMMatrixTranslation(0.0f, 0.0f, -10.0f);

		XMMATRIX worldMatrix2 = rotationMatrix * translationMatrix;

		// View Matrix
		XMVECTOR cameraPosition = XMVectorSet(0.0f, 0.0f, 0.1f, 0);
		XMVECTOR cameraLookAt = XMVectorReplicate(0.0f);
		XMVECTOR cameraUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		XMMATRIX viewMatrix = XMMatrixLookAtLH(cameraPosition, cameraLookAt, cameraUp);

		// Projection Matrix
		XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(45), static_cast<float>(mGame->GetScreenWidth()) / mGame->GetScreenHeight(), 0.1f, 100.0f);

		XMMATRIX worldViewProjectionMatrix1 = worldMatrix1 * translationMatrix2 * viewMatrix * projectionMatrix;
		mGame->GetDirect3DDeviceContext()->UpdateSubresource(mConstantBuffer, 0, 0, &worldViewProjectionMatrix1, 0, 0);
		direct3DDeviceContext->Draw(3, 0);	// 3 is the total number of vertices.

		XMMATRIX worldViewProjectionMatrix2 = worldMatrix2  * viewMatrix * projectionMatrix;
		mGame->GetDirect3DDeviceContext()->UpdateSubresource(mConstantBuffer, 0, 0, &worldViewProjectionMatrix2, 0, 0);
		direct3DDeviceContext->Draw(3, 0);	// 3 is the total number of vertices.
	}

	void ColoredCube::Shutdown()
	{
		ReleaseObject(mVertexBuffer)
		ReleaseObject(mPixelShader)
		ReleaseObject(mInputLayout)
		ReleaseObject(mVertexShader)
	}
}