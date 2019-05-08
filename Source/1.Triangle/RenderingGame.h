#pragma once

#include "Game.h"

namespace Rendering
{
	class ColoredTriangle;

	class RenderingGame : public Library::Game
	{
	public:
		RenderingGame(HINSTANCE instance, const std::wstring& windowClassName, const std::wstring& windowTitle, int showCommand);

		virtual void Initialize() override;
		//virtual void Update(const GameTime& gameTime) override;
		virtual void Draw() override;

	protected:
		virtual void Shutdown() override;

	private:
		static const XMVECTORF32 BackgroundColor;

		//LPDIRECTINPUT8 mDirectInput;
		/*std::unique_ptr<Keyboard> mKeyboard;
		std::unique_ptr<Mouse> mMouse;
		std::unique_ptr<FpsComponent> mFpsComponent;
		std::unique_ptr<FirstPersonCamera> mCamera;*/

		std::unique_ptr<ColoredTriangle> mColoredTriangle;
	};
}