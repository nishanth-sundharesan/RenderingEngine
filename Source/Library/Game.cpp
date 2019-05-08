#include "Pch.h"
#include "Game.h"

using namespace std;

namespace Library
{
	const UINT Game::sDefaultScreenWidth = 1024;
	const UINT Game::sDefaultScreenHeight = 768;
	const UINT Game::sDefaultFrameRate = 60;
	const UINT Game::sDefaultMultiSamplingCount = 4;

	Game::Game(HINSTANCE instance, const wstring& windowClassName, const wstring& windowTitle, int showCommand) :
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

		// Struct to hold Windows event messages
		MSG message;
		ZeroMemory(&message, sizeof(message));
		
		//mGameClock.Reset();

		while (message.message != WM_QUIT)
		{
			// Check to see if there are any messages in the queue
			if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				// Translate keystroke messages into the correct format
				TranslateMessage(&message);

				// Send the message to the WindowProc function
				DispatchMessage(&message);
			
			}

			//mGameClock.UpdateGameTime(mGameTime);
			//Update(mGameTime);
			//Draw(mGameTime);

			RenderFrame();
		}

		//Shutdown();
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
		HRESULT hr;
		UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)  
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0
		};

		ID3D11Device* direct3DDevice = nullptr;
		ID3D11DeviceContext* direct3DDeviceContext = nullptr;
		if (FAILED(hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &direct3DDevice, &mFeatureLevel, &direct3DDeviceContext)))
		{
			throw GameException("D3D11CreateDevice() failed", hr);
		}

		if (FAILED(hr = direct3DDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&mDirect3DDevice))))
		{
			throw GameException("ID3D11Device::QueryInterface() failed", hr);
		}

		if (FAILED(hr = direct3DDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&mDirect3DDeviceContext))))
		{
			throw GameException("ID3D11Device::QueryInterface() failed", hr);
		}

		ReleaseObject(direct3DDevice);
		ReleaseObject(direct3DDeviceContext);

		mDirect3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, mMultiSamplingCount, &mMultiSamplingQualityLevels);
		if (mMultiSamplingQualityLevels == 0)
		{
			throw GameException("Unsupported multi-sampling quality");
		}

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.Width = mScreenWidth;
		swapChainDesc.Height = mScreenHeight;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		if (mMultiSamplingEnabled)
		{
			swapChainDesc.SampleDesc.Count = mMultiSamplingCount;
			swapChainDesc.SampleDesc.Quality = mMultiSamplingQualityLevels - 1;
		}
		else
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
		}

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		IDXGIDevice* dxgiDevice = nullptr;
		if (FAILED(hr = mDirect3DDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice))))
		{
			throw GameException("ID3D11Device::QueryInterface() failed", hr);
		}

		IDXGIAdapter *dxgiAdapter = nullptr;
		if (FAILED(hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter))))
		{
			ReleaseObject(dxgiDevice);
			throw GameException("IDXGIDevice::GetParent() failed retrieving adapter.", hr);
		}

		IDXGIFactory2* dxgiFactory = nullptr;
		if (FAILED(hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory))))
		{
			ReleaseObject(dxgiDevice);
			ReleaseObject(dxgiAdapter);
			throw GameException("IDXGIAdapter::GetParent() failed retrieving factory.", hr);
		}

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc;
		ZeroMemory(&fullScreenDesc, sizeof(fullScreenDesc));
		fullScreenDesc.RefreshRate.Numerator = mFrameRate;
		fullScreenDesc.RefreshRate.Denominator = 1;
		fullScreenDesc.Windowed = !mIsFullScreen;

		if (FAILED(hr = dxgiFactory->CreateSwapChainForHwnd(dxgiDevice, mWindowHandle, &swapChainDesc, &fullScreenDesc, nullptr, &mSwapChain)))
		{
			ReleaseObject(dxgiDevice);
			ReleaseObject(dxgiAdapter);
			ReleaseObject(dxgiFactory);
			throw GameException("IDXGIDevice::CreateSwapChainForHwnd() failed.", hr);
		}

		ReleaseObject(dxgiDevice);
		ReleaseObject(dxgiAdapter);
		ReleaseObject(dxgiFactory);

		ID3D11Texture2D* backBuffer;
		if (FAILED(hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
		{
			throw GameException("IDXGISwapChain::GetBuffer() failed.", hr);
		}

		backBuffer->GetDesc(&mBackBufferDesc);

		if (FAILED(hr = mDirect3DDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView)))
		{
			ReleaseObject(backBuffer);
			throw GameException("IDXGIDevice::CreateRenderTargetView() failed.", hr);
		}

		ReleaseObject(backBuffer);

		if (mDepthStencilBufferEnabled)
		{
			D3D11_TEXTURE2D_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
			depthStencilDesc.Width = mScreenWidth;
			depthStencilDesc.Height = mScreenHeight;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

			if (mMultiSamplingEnabled)
			{
				depthStencilDesc.SampleDesc.Count = mMultiSamplingCount;
				depthStencilDesc.SampleDesc.Quality = mMultiSamplingQualityLevels - 1;
			}
			else
			{
				depthStencilDesc.SampleDesc.Count = 1;
				depthStencilDesc.SampleDesc.Quality = 0;
			}

			if (FAILED(hr = mDirect3DDevice->CreateTexture2D(&depthStencilDesc, nullptr, &mDepthStencilBuffer)))
			{
				throw GameException("IDXGIDevice::CreateTexture2D() failed.", hr);
			}

			if (FAILED(hr = mDirect3DDevice->CreateDepthStencilView(mDepthStencilBuffer, nullptr, &mDepthStencilView)))
			{
				throw GameException("IDXGIDevice::CreateDepthStencilView() failed.", hr);
			}
		}

		mViewport.TopLeftX = 0.0f;
		mViewport.TopLeftY = 0.0f;
		mViewport.Width = static_cast<float>(mScreenWidth);
		mViewport.Height = static_cast<float>(mScreenHeight);
		mViewport.MinDepth = 0.0f;
		mViewport.MaxDepth = 1.0f;

		// Set render targets and viewport through render target stack	
		Begin();
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

	LRESULT CALLBACK Game::WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		// Sort through the messages and decide what needs to be done for each message.
		switch (message)
		{
			// This message is read when the window is closed
			case WM_DESTROY:
			{
				// Send message to close the application. WM_QUIT or 0.
				PostQuitMessage(WM_QUIT);
				return 0;
			}
			break;
		}

		// Handle any messages that the switch case didn't handle
		return DefWindowProc(windowHandle, message, wParam, lParam);
	}

	//const vector<GameComponent*>& Game::Components() const
	//{
	//	// TODO: insert return statement here
	//}

	//const ServiceContainer& Game::Services() const
	//{
	//	// TODO: insert return statement here
	//}

}