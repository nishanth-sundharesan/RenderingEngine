#pragma once

#include "Game.h"

namespace Rendering
{
	class ColoredCubeCube;

	class RenderingGame : public Library::Game
	{
	public:
		RenderingGame(HINSTANCE instance, const std::wstring& windowClassName, const std::wstring& windowTitle, std::int32_t showCommand);

		virtual ~RenderingGame() = default;

		RenderingGame(const RenderingGame& rhs) = delete;
		RenderingGame& operator=(const Game& rhs) = delete;

		RenderingGame(const RenderingGame&& rhs) = delete;
		RenderingGame& operator=(const RenderingGame&& rhs) = delete;

		virtual void Initialize() override;
		virtual void Draw() override;

	protected:
		virtual void Shutdown() override;

	private:
		std::unique_ptr<ColoredCubeCube> mColoredCube;
	};
}