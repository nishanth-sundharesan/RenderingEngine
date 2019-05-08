#pragma once
#include "Pch.h"
#include <vector>
#include "GameEntity.h"

namespace Library
{
	//class GameEntity;

	class Game
	{
	public:
		Game(HINSTANCE instance, const std::wstring& windowClassName, const std::wstring& windowTitle, int showCommand);
		virtual ~Game() = default;

		Game(const Game& rhs) = delete;
		Game& operator=(const Game& rhs) = delete;

		Game(const Game&& rhs) = delete;
		Game& operator=(const Game&& rhs) = delete;

		// Windows related
		HINSTANCE GetInstance() const;
		HWND GetWindowHandle() const;
		const WNDCLASSEX& GetWindowClass() const;
		const std::wstring& WindowClassName() const;
		const std::wstring& WindowTitle() const;
		int GetScreenWidth() const;
		int GetScreenHeight() const;

		// Direct3D related
		ID3D11Device* GetDirect3DDevice() const;
		ID3D11DeviceContext* GetDirect3DDeviceContext() const;
		//bool IsDepthStencilBufferEnabled() const;
		ID3D11RenderTargetView* GetRenderTargetView() const;
		//ID3D11DepthStencilView* GetDepthStencilView() const;
		float GetAspectRatio() const;
		bool IsFullScreen() const;
		const D3D11_TEXTURE2D_DESC& GetBackBufferDescription() const;
		const D3D11_VIEWPORT& GetViewport() const;
		bool IsMultiSamplingEnabled() const;
		UINT GetMultiSamplingCount() const;
		UINT GetMultiSamplingQualityLevels() const;

		/*const std::vector<GameComponent*>& Components() const;
		const ServiceContainer& Services() const;*/

		virtual void Run();
		virtual void Exit();
		virtual void Initialize();
		//virtual void Update(const GameTime& gameTime);
		virtual void Draw();

		virtual void ResetRenderTargets();
		virtual void UnbindPixelShaderResources(UINT startSlot, UINT count);

	protected:
		virtual void Begin();
		virtual void End();
		virtual void InitializeWindow();
		virtual void InitializeDirectX();
		virtual void Shutdown();

		static const UINT sDefaultScreenWidth;
		static const UINT sDefaultScreenHeight;
		static const UINT sDefaultFrameRate;
		static const UINT sDefaultMultiSamplingCount;

		HINSTANCE mInstance;
		std::wstring mWindowClassName;
		std::wstring mWindowTitle;
		int mShowCommand;

		HWND mWindowHandle;			// Handle for the window, filled by the function CreateWindowEx()
		WNDCLASSEX mWindowClass;	// The struct that holds information for the window class

		LONG mScreenWidth;
		LONG mScreenHeight;

		//GameClock mGameClock;
		//GameTime mGameTime;
		std::vector<GameEntity*> mEntities;
		//ServiceContainer mServices;

		D3D_FEATURE_LEVEL mFeatureLevel;
		ID3D11Device* mDirect3DDevice;
		ID3D11DeviceContext* mDirect3DDeviceContext;
		IDXGISwapChain1* mSwapChain;

		UINT mRefreshRate;
		bool mIsFullScreen;
		//bool mDepthStencilBufferEnabled;
		bool mMultiSamplingEnabled;
		UINT mMultiSamplingCount;
		UINT mMultiSamplingQualityLevels;

		//ID3D11Texture2D* mDepthStencilBuffer;
		D3D11_TEXTURE2D_DESC mBackBufferDesciption;
		ID3D11RenderTargetView* mRenderTargetView;
		//ID3D11DepthStencilView* mDepthStencilView;
		D3D11_VIEWPORT mViewport;

	private:
		void CenterWindow(std::int32_t windowWidth, std::int32_t windowHeight, POINT& outPoint) const;
		static LRESULT CALLBACK WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);	// This is the main message handler for the program
	};
}

// TODO
// 1. Check all the places where UINT is present and check if we can replace them