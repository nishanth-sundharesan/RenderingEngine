#include "Pch.h"
#include "RenderingGame.h"
#include "GameException.h"
#include "ColorHelper.h"
#include "TexturedCube.h"
#include "KeyboardEntity.h"

using namespace std;
using namespace Library_3;

namespace Rendering
{
	RenderingGame::RenderingGame(HINSTANCE instance, const wstring& windowClassName, const wstring& windowTitle, int32_t showCommand) :
		Game(instance, windowClassName, windowTitle, showCommand),
		mTexturedCube(nullptr)
	{		
	}

	void RenderingGame::Initialize()
	{
		mTexturedCube = make_unique<TexturedCube>(*this);
		mEntities.push_back(mTexturedCube.get());

		mKeyboardEntity = make_unique<Library_3::KeyboardEntity>(*this);
		mEntities.push_back(mKeyboardEntity.get());

		Game::Initialize();
	}

	void RenderingGame::Update()
	{
		if (mKeyboardEntity->WasKeyPressedThisFrame(Keys::Escape))
		{
			Game::Exit();
		}

		Game::Update();
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