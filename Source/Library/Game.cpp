#include "Pch.h"
#include "Game.h"

using namespace std;

namespace Library
{
	const UINT Game::sDefaultScreenWidth = 1024;
	const UINT Game::sDefaultScreenHeight = 768;
	const UINT Game::sDefaultFrameRate = 60;
	const UINT Game::sDefaultMultiSamplingCount = 4;

	Game::Game(HINSTANCE instance, const wstring& windowClassName, const wstring& windowTitle, int showCommand):
		mInstance(instance),
		mWindowClassName(windowClassName),
		mWindowTitle(windowTitle),
		mShowCommand(showCommand),
		mWindowHandle(),
		mWindowClass(),
		mScreenWidth(sDefaultScreenWidth),
		mScreenHeight(sDefaultScreenHeight),
		//mGameClock(),
		//mGameTime(),
		//mFeatureLevel(D3D_FEATURE_LEVEL_9_1),
		mDirect3DDevice(nullptr),
		mDirect3DDeviceContext(nullptr),
		mSwapChain(nullptr),
		mFrameRate(sDefaultFrameRate),
		mIsFullScreen(false),
		//mDepthStencilBufferEnabled(true), 
		mMultiSamplingEnabled(true),
		mMultiSamplingCount(sDefaultMultiSamplingCount),
		mMultiSamplingQualityLevels(0),
		//mDepthStencilBuffer(nullptr),
		mRenderTargetView(nullptr),
		//mDepthStencilView(nullptr),
		mViewport()
		//mComponents(),
		//mServices()
	{

	}

	// Windows related
	HINSTANCE Game::GetInstance() const
	{
		return mInstance;
	}

	HWND Game::GetWindowHandle() const
	{
		return mWindowHandle;
	}

	const WNDCLASSEX& Game::GetWindowClass() const
	{
		return mWindowClass;
	}

	const wstring& Game::WindowClassName() const
	{
		return mWindowClassName;
	}

	const wstring & Game::WindowTitle() const
	{
		return mWindowTitle;
	}

	int Game::GetScreenWidth() const
	{
		return mScreenWidth;
	}

	int Game::GetScreenHeight() const
	{
		return mScreenHeight;
	}


	// Direct3D related
	ID3D11Device* Game::GetDirect3DDevice() const
	{
		return mDirect3DDevice;
	}

	ID3D11DeviceContext* Game::GetDirect3DDeviceContext() const
	{
		return mDirect3DDeviceContext;
	}

	/*bool Game::IsDepthStencilBufferEnabled() const
	{
		return mDepthStencilBufferEnabled;
	}*/

	ID3D11RenderTargetView* Game::GetRenderTargetView() const
	{
		return mRenderTargetView;
	}

	/*ID3D11DepthStencilView* Game::GetDepthStencilView() const
	{
		return nullptr;
	}*/

	float Game::GetAspectRatio() const
	{
		return static_cast<float>(mScreenWidth) / mScreenHeight;
	}

	bool Game::IsFullScreen() const
	{
		return mIsFullScreen;
	}

	const D3D11_TEXTURE2D_DESC& Game::GetBackBufferDescription() const
	{
		return mBackBufferDesciption;
	}

	const D3D11_VIEWPORT& Game::GetViewport() const
	{
		return mViewport;
	}

	bool Game::IsMultiSamplingEnabled() const
	{
		return mMultiSamplingEnabled;
	}

	UINT Game::GetMultiSamplingCount() const
	{
		return mMultiSamplingCount;
	}

	UINT Game::GetMultiSamplingQualityLevels() const
	{
		return mMultiSamplingQualityLevels;
	}

	void Game::Run()
	{
		InitializeWindow();
		InitializeDirectX();
		Initialize();
	}

	void Game::Exit()
	{
	}

	void Game::Initialize()
	{
	}

	void Game::ResetRenderTargets()
	{
	}

	void Game::UnbindPixelShaderResources(UINT startSlot, UINT count)
	{
	}

	void Game::InitializeWindow()
	{
		// Clear out the window class for use
		ZeroMemory(&mWindowClass, sizeof(WNDCLASSEX));

		// Fill in the struct with the needed information
		mWindowClass.cbSize = sizeof(WNDCLASSEX);
		// mWindow.style = CS_CLASSDC;
		mWindowClass.style = CS_HREDRAW | CS_VREDRAW;	// Draw if a window is moved horizontally or vertically.
		mWindowClass.lpfnWndProc = WindowProc;
		mWindowClass.hInstance = mInstance;
		// mWindow.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		// mWindow.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		mWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		//wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
		mWindowClass.lpszClassName = mWindowClassName.c_str();

		// Register the window class
		RegisterClassEx(&mWindowClass);


		// Set the size of the client area
		RECT windowRectangle = { 0, 0, mScreenWidth, mScreenHeight };
		AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW, FALSE);    // Fill the size of the window rectangle.

		POINT center;
		CenterWindow(mScreenWidth, mScreenHeight, center);

		// Create the window and use the result as the handle
		mWindowHandle = CreateWindow(
							  mWindowClassName.c_str(),							// Name of the window class
							  mWindowTitle.c_str(),								// Title of the window
							  WS_OVERLAPPEDWINDOW,								// Window style
							  center.x,											// X-position of the window
							  center.y,											// Y-position of the window
							  windowRectangle.right - windowRectangle.left,		// Width of the window
							  windowRectangle.bottom - windowRectangle.top,		// Height of the window
							  nullptr,											// We have no parent window, so set nullptr
							  nullptr,											// We aren't using menus, so set nullptr
							  mInstance,										// The application handle
							  nullptr);											// This is used with multiple windows, so set nullptr

		// Display the window on the screen
		ShowWindow(mWindowHandle, mShowCommand);
		UpdateWindow(mWindowHandle);
	}

	void Game::InitializeDirectX()
	{

	}

	void Game::Shutdown()
	{
	}

	void Game::CenterWindow(int32_t windowWidth, int32_t windowHeight, POINT& outPoint) const
	{
		int32_t screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int32_t screenHeight = GetSystemMetrics(SM_CYSCREEN);
		
		outPoint.x = (screenWidth - windowWidth) / 2;
		outPoint.y = (screenHeight - windowHeight) / 2;		
	}

	LRESULT __stdcall Game::WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return LRESULT __stdcall();
	}

	const vector<GameComponent*>& Game::Components() const
	{
		// TODO: insert return statement here
	}

	const ServiceContainer& Game::Services() const
	{
		// TODO: insert return statement here
	}

}