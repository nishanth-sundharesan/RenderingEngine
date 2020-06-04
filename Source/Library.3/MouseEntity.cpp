#include "PchLibrary.h"
#include "MouseEntity.h"

#include "Game.h"

// Info: https://github.com/Microsoft/DirectXTK/wiki/Mouse

using namespace DirectX;

namespace Library_3	
{
	std::unique_ptr<Mouse> MouseEntity::sMouse(new DirectX::Mouse);

	MouseEntity::MouseEntity(Game& game, MouseModes mode):
		GameEntity(game)
	{
		sMouse->SetWindow(game.GetWindowHandle());
		SetMode(mode);
	}

	void MouseEntity::Initialize()
	{
		mCurrentState = sMouse->GetState();
		mLastState = mCurrentState;
	}

	void MouseEntity::Update(/*const GameTime& gameTime*/)
	{
		mLastState = mCurrentState;
		mCurrentState = sMouse->GetState();
	}

	int MouseEntity::X() const
	{
		return mCurrentState.x;
	}

	int MouseEntity::Y() const
	{
		return mCurrentState.y;
	}

	int MouseEntity::Wheel() const
	{
		return mCurrentState.scrollWheelValue;
	}

	bool MouseEntity::IsButtonUp(MouseButtons button) const
	{
		return GetButtonState(mCurrentState, button) == false;
	}

	bool MouseEntity::IsButtonDown(MouseButtons button) const
	{
		return GetButtonState(mCurrentState, button);
	}

	bool MouseEntity::WasButtonUp(MouseButtons button) const
	{
		return GetButtonState(mLastState, button) == false;
	}

	bool MouseEntity::WasButtonDown(MouseButtons button) const
	{
		return GetButtonState(mLastState, button);
	}

	bool MouseEntity::WasButtonPressedThisFrame(MouseButtons button) const
	{
		return (IsButtonDown(button) && WasButtonUp(button));
	}

	bool MouseEntity::WasButtonReleasedThisFrame(MouseButtons button) const
	{
		return (IsButtonUp(button) && WasButtonDown(button));
	}

	bool MouseEntity::IsButtonHeldDown(MouseButtons button) const
	{
		return (IsButtonDown(button) && WasButtonDown(button));
	}

	MouseModes MouseEntity::GetMode() const
	{
		return static_cast<MouseModes>(mCurrentState.positionMode);
	}

	void MouseEntity::SetMode(MouseModes mode)
	{
		sMouse->SetMode(static_cast<Mouse::Mode>(mode));
	}

	bool MouseEntity::GetButtonState(const Mouse::State& state, MouseButtons button) const
	{
		switch (button)
		{
		case Library_3::MouseButtons::Left:
			return state.leftButton;

		case Library_3::MouseButtons::Right:
			return state.rightButton;

		case Library_3::MouseButtons::Middle:
			return state.middleButton;

		case Library_3::MouseButtons::X1:
			return state.xButton1;

		case Library_3::MouseButtons::X2:
			return state.xButton2;

		default:
			throw GameException("Invalid Mouse Button");
		}
	}
}
