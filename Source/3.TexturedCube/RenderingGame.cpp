#include "Pch.h"
#include "RenderingGame.h"
#include "GameException.h"
#include "ColorHelper.h"
#include "ColoredCube.h"

using namespace std;
using namespace Library_3;

namespace Rendering
{
	RenderingGame::RenderingGame(HINSTANCE instance, const wstring& windowClassName, const wstring& windowTitle, int32_t showCommand) :
		Game(instance, windowClassName, windowTitle, showCommand),
		mColoredCube(nullptr)
	{
	}

	void RenderingGame::Initialize()
	{
		mColoredCube = make_unique<ColoredCube>(*this);	

		mEntities.push_back(mColoredCube.get());

		Game::Initialize();
	}

	void RenderingGame::Draw()
	{
		mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Library_3::ColorHelper::CornflowerBlue));
		mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		
		Game::Draw();

		ThrowIfFailed(mSwapChain->Present(0, 0), "IDXGISwapChain::Present() failed.");
	}

	void RenderingGame::Shutdown()
	{
		Game::Shutdown();
	}
}