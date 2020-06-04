#include "PchLibrary.h"
#include "KeyboardEntity.h"

// Info: https://github.com/microsoft/DirectXTK/wiki/Keyboard

namespace Library_3
{
	std::unique_ptr<DirectX::Keyboard> KeyboardEntity::sKeyboard(new DirectX::Keyboard);

	KeyboardEntity::KeyboardEntity(Game& game) :
		GameEntity(game)
	{
	}

	void KeyboardEntity::Initialize()
	{
		mCurrentState = sKeyboard->GetState();
		mLastState = mCurrentState;
	}

	void KeyboardEntity::Update()
	{
		mLastState = mCurrentState;
		mCurrentState = sKeyboard->GetState();
	}

	bool KeyboardEntity::IsKeyUp(Keys key) const
	{
		return mCurrentState.IsKeyUp(static_cast<DirectX::Keyboard::Keys>(key));
	}

	bool KeyboardEntity::IsKeyDown(Keys key) const
	{
		return mCurrentState.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(key));
	}

	bool KeyboardEntity::WasKeyUp(Keys key) const
	{
		return mLastState.IsKeyUp(static_cast<DirectX::Keyboard::Keys>(key));
	}

	bool KeyboardEntity::WasKeyDown(Keys key) const
	{
		return mLastState.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(key));
	}

	bool KeyboardEntity::WasKeyPressedThisFrame(Keys key) const
	{
		return (IsKeyDown(key) && WasKeyUp(key));
	}

	bool KeyboardEntity::WasKeyReleasedThisFrame(Keys key) const
	{
		return (IsKeyUp(key) && WasKeyDown(key));
	}

	bool KeyboardEntity::IsKeyHeldDown(Keys key) const
	{
		return (IsKeyDown(key) && WasKeyDown(key));
	}
}
