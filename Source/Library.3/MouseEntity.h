#pragma once
#include "GameEntity.h"

#include <DirectXTK/Mouse.h>

namespace Library_3
{
	enum class MouseButtons
	{
		Left = 0,
		Right,
		Middle,
		X1,
		X2
	};

	enum class MouseModes
	{
		Absolute = 0,
		Relative
	};

	class MouseEntity final : public Library_3::GameEntity
	{
	public:
		explicit MouseEntity(Game& game, MouseModes mode = MouseModes::Relative);
		~MouseEntity() = default;

		MouseEntity(const MouseEntity&) = delete;
		MouseEntity(MouseEntity&&) = delete;

		MouseEntity& operator=(const MouseEntity&) = delete;
		MouseEntity& operator=(MouseEntity&&) = delete;
	
		virtual void Initialize() override;
		virtual void Update(/*const GameTime& gameTime*/) override;		

		int X() const;
		int Y() const;
		int Wheel() const;

		bool IsButtonUp(MouseButtons button) const;
		bool IsButtonDown(MouseButtons button) const;
		bool WasButtonUp(MouseButtons button) const;
		bool WasButtonDown(MouseButtons button) const;
		bool WasButtonPressedThisFrame(MouseButtons button) const;
		bool WasButtonReleasedThisFrame(MouseButtons button) const;
		bool IsButtonHeldDown(MouseButtons button) const;

		MouseModes GetMode() const;
		void SetMode(MouseModes mode);

	private:
		bool GetButtonState(const DirectX::Mouse::State& state, MouseButtons button) const;

		static std::unique_ptr<DirectX::Mouse> sMouse;

		DirectX::Mouse::State mCurrentState;
		DirectX::Mouse::State mLastState;
	};
}