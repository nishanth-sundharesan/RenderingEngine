#include "Pch.h"
#include <fstream>

// Enable memory leak detection.
// More information is here: https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// global declarations
IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
ID3D11Device *dev;                     // the pointer to our Direct3D device interface
ID3D11RenderTargetView *renderTargetView;    // the pointer to the currently bound render target
ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context

ID3D11InputLayout *inputLayout;           // the pointer to the input layout
ID3D11VertexShader *vertexShader;         // the pointer to the vertex shader
ID3D11PixelShader *pixelShader;           // the pointer to the pixel shader
ID3D11Buffer *vertexBuffer;               // the pointer to the vertex buffer

// a struct to define a single vertex
struct VertexPositionColor
{ 
	XMFLOAT3 Position;
	XMFLOAT4 Color;

	VertexPositionColor() { }

	VertexPositionColor(const XMFLOAT3& position, const XMFLOAT4& color)
		: Position(position), Color(color) { }
};

// function prototypes
void InitD3D(HWND hWnd);    // sets up and initializes Direct3D
void RenderFrame(void);     // renders a single frame
void CleanD3D(void);        // closes Direct3D and releases memory

void InitGraphics(void);    // creates the shape to render
void InitPipeline(void);    // loads and prepares the shaders

void LoadBinaryFile(const std::string& filename, std::vector<char>& data);

// define the screen resolution
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600


XMVECTORF32 BackgroundColor = { 0.392f, 0.584f, 0.929f, 1.0f };

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Entry point for the Windows program.
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	UNREFERENCED_PARAMETER(previousInstance);
	UNREFERENCED_PARAMETER(commandLine);

	// Enable memory leak detection.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//// the handle for the window, filled by a function
	//HWND hWnd;
	//// this struct holds information for the window class
	//WNDCLASSEX wc;

	//// clear out the window class for use
	//ZeroMemory(&wc, sizeof(WNDCLASSEX));

	//// fill in the struct with the needed information
	//wc.cbSize = sizeof(WNDCLASSEX);
	//wc.style = CS_HREDRAW | CS_VREDRAW;
	//wc.lpfnWndProc = WindowProc;
	//wc.hInstance = instance;
	//wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	////wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	//wc.lpszClassName = L"WindowClass1";

	//// register the window class
	//RegisterClassEx(&wc);

	//// calculate the size of the client area
	//RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};    // set the size, but not the position
	//AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

	//// create the window and use the result as the handle
	//hWnd = CreateWindowEx(NULL,
	//					  L"WindowClass1",    // name of the window class
	//					  L"Game",   // title of the window
	//					  WS_OVERLAPPEDWINDOW,    // window style
	//					  300,    // x-position of the window
	//					  300,    // y-position of the window
	//					  wr.right - wr.left,    // width of the window
	//					  wr.bottom - wr.top,    // height of the window
	//					  NULL,    // we have no parent window, NULL
	//					  NULL,    // we aren't using menus, NULL
	//					  instance,    // application handle
	//					  NULL);    // used with multiple windows, NULL

	//// display the window on the screen
	//ShowWindow(hWnd, showCommand);

	// set up and initialize Direct3D
	InitD3D(hWnd);

	// enter the main loop:

	//// this struct holds Windows event messages
	//MSG message;
	//ZeroMemory(&message, sizeof(message));

	//// Enter the infinite message loop
	//while (TRUE)
	//{
	//	// Check to see if any messages are waiting in the queue
	//	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	//	{
	//		// translate keystroke messages into the right format
	//		TranslateMessage(&message);

	//		// send the message to the WindowProc function
	//		DispatchMessage(&message);

	//		// check to see if it's time to quit
	//		if (msg.message == WM_QUIT)
	//			break;
	//	}
	//	RenderFrame();
	//}

	// clean up DirectX and COM
	CleanD3D();

	// return this part of the WM_QUIT message to Windows
	return static_cast<int>(msg.wParam);
}

//// this is the main message handler for the program
//LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	// sort through and find what code to run for the message given
//	switch (message)
//	{
//		// this message is read when the window is closed
//		case WM_DESTROY:
//		{
//			// close the application entirely
//			PostQuitMessage(WM_QUIT);
//			return 0;
//		} break;
//	}
//
//	// Handle any messages the switch statement didn't
//	return DefWindowProc (hWnd, message, wParam, lParam);
//}

// this function initializes and prepares Direct3D for use
void InitD3D(HWND hWnd)
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferDesc.Width = SCREEN_WIDTH;                    // set the back buffer width
	scd.BufferDesc.Height = SCREEN_HEIGHT;                  // set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = hWnd;                                // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

	// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
								  D3D_DRIVER_TYPE_HARDWARE,
								  NULL,
								  NULL,
								  NULL,
								  NULL,
								  D3D11_SDK_VERSION,
								  &scd,
								  &swapchain,
								  &dev,
								  NULL,
								  &devcon);

	// get the address of the back buffer from swapchain.
	ID3D11Texture2D *backBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &backBuffer);

	// use the back buffer address to create the render target
	dev->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();

	// bind the render target
	devcon->OMSetRenderTargets(1, &renderTargetView, NULL);


	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;

	devcon->RSSetViewports(1, &viewport);

	InitPipeline();
	InitGraphics();
}

// this is the function used to render a single frame
void RenderFrame(void)
{
	// clear the back buffer to a deep blue
	devcon->ClearRenderTargetView(renderTargetView, reinterpret_cast<const float*>(&BackgroundColor));

	// do 3D rendering on the back buffer here
	// Bind the verter buffer array to input assembly.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// select which primtive type we are using
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw the vertex buffer to the back buffer
	devcon->Draw(3, 0);

	// switch the back buffer and the front buffer
	swapchain->Present(0, 0);
}

// this is the function that creates the shape to render
void InitGraphics()
{
	// create a triangle using the VERTEX struct
	VertexPositionColor vertices[] =
	{
		VertexPositionColor(XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)),
		VertexPositionColor(XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)),
		VertexPositionColor(XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f))
	};


	// create the vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	bd.ByteWidth = sizeof(VertexPositionColor) * 3;             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	dev->CreateBuffer(&bd, NULL, &vertexBuffer);       // create the buffer


	// copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
	memcpy(ms.pData, vertices, sizeof(vertices));                 // copy the data
	devcon->Unmap(vertexBuffer, NULL);                                      // unmap the buffer
}

// this function loads and prepares the shaders
void InitPipeline()
{
	// load and compile the two shaders	

	std::vector<char> compiledVertexShader;		
	LoadBinaryFile("Shaders\\VertexShader.cso", compiledVertexShader);

	// encapsulate both shaders into shader objects
	dev->CreateVertexShader(&compiledVertexShader[0], compiledVertexShader.size(), nullptr, &vertexShader);


	std::vector<char> compiledPixelShader;
	LoadBinaryFile("Shaders\\PixelShader.cso", compiledPixelShader);

	// encapsulate both shaders into shader objects
	dev->CreatePixelShader(&compiledPixelShader[0], compiledPixelShader.size(), nullptr, &pixelShader);	

	// set the shader objects
	devcon->VSSetShader(vertexShader, 0, 0);
	devcon->PSSetShader(pixelShader, 0, 0);

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	dev->CreateInputLayout(ied, ARRAYSIZE(ied), &compiledVertexShader[0], compiledVertexShader.size(), &inputLayout);
	devcon->IASetInputLayout(inputLayout);
}

// this is the function that cleans up Direct3D and COM
void CleanD3D()
{
	swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

	// close and release all existing COM objects
	inputLayout->Release();
	vertexShader->Release();
	pixelShader->Release();
	vertexBuffer->Release();

	swapchain->Release();
	renderTargetView->Release();
	dev->Release();
	devcon->Release();
}

void LoadBinaryFile(const std::string& filename, std::vector<char>& data)
{
	std::ifstream file(filename.c_str(), std::ios::binary);
	if (file.bad())
	{
		throw std::exception("Could not open file.");
	}

	file.seekg(0, std::ios::end);
	UINT size = (UINT) file.tellg();

	if (size > 0)
	{
		data.resize(size);
		file.seekg(0, std::ios::beg);
		file.read(&data.front(), size);
	}

	file.close();
}