#include "Pch.h"
#include "RenderingGame.h"
#include "GameException.h"
#include "ColorHelper.h"
#include "ColoredTriangle.h"

using namespace std;
using namespace Library;

namespace Rendering
{
	RenderingGame::RenderingGame(HINSTANCE instance, const wstring& windowClassName, const wstring& windowTitle, int32_t showCommand) :
		Game(instance, windowClassName, windowTitle, showCommand),
		mColoredTriangle(nullptr)
	{
	}

	void RenderingGame::Initialize()
	{
		mColoredTriangle = make_unique<ColoredTriangle>(*this);	

		mEntities.push_back(mColoredTriangle.get());

		Game::Initialize();
	}

	void RenderingGame::Draw()
	{
		mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Library::ColorHelper::CornflowerBlue));

		Game::Draw();

		ThrowIfFailed(mSwapChain->Present(0, 0), "IDXGISwapChain::Present() failed.");
	}

	void RenderingGame::Shutdown()
	{
		Game::Shutdown();
	}
}