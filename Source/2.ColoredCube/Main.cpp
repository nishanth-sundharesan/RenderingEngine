#include "Pch.h"

#include "RenderingGame.h"
#include "GameException.h"

using namespace Rendering;
using namespace Library;

// Enable memory leak detection.
// More information is here: https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// Entry point for the Windows program.
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	UNREFERENCED_PARAMETER(previousInstance);
	UNREFERENCED_PARAMETER(commandLine);

	// Enable memory leak detection.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	std::unique_ptr<RenderingGame> game = std::make_unique<RenderingGame>(instance, L"RenderingClass", L"ColoredCube", showCommand);

	try
	{
		game->Run();
	}
	catch (GameException ex)
	{
		MessageBox(game->GetWindowHandle(), ex.GetWhatWString().c_str(), game->WindowTitle().c_str(), MB_ABORTRETRYIGNORE);
	}

	return 0;
}