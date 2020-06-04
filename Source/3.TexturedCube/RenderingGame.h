#pragma once

#include "Game.h"

namespace Library_3
{
	class KeyboardEntity;
	class MouseEntity;
}

namespace Rendering
{
	class TexturedCube;

	class RenderingGame : public Library_3::Game
	{
	public:
		RenderingGame(HINSTANCE instance, const std::wstring& windowClassName, const std::wstring& windowTitle, std::int32_t showCommand);

		virtual ~RenderingGame() = default;

		RenderingGame(const RenderingGame& rhs) = delete;
		RenderingGame& operator=(const Game& rhs) = delete;

		RenderingGame(const RenderingGame&& rhs) = delete;
		RenderingGame& operator=(const RenderingGame&& rhs) = delete;

		virtual void Initialize() override;
		virtual void Update(/*const GameTime& gameTime*/) override;
		virtual void Draw() override;

	protected:
		virtual void Shutdown() override;

	private:
		static const XMVECTORF32 BackgroundColor;		

		std::unique_ptr<TexturedCube> mTexturedCube;
		std::unique_ptr<Library_3::KeyboardEntity> mKeyboardEntity;
		std::unique_ptr<Library_3::MouseEntity> mMouseEntity;
	};
}