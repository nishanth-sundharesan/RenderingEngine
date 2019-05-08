#include "Pch.h"
#include "GameEntity.h"

namespace Library
{
	GameEntity::GameEntity() :
		mGame(nullptr),
		mIsEnabled(false)
	{
	}

	GameEntity::GameEntity(Game& game) :
		mGame(&game),
		mIsEnabled(true)
	{
	}

	Game* GameEntity::GetGame()
	{
		return mGame;
	}

	void GameEntity::SetGame(Game& game)
	{
		mGame = &game;
	}

	bool GameEntity::Enabled() const
	{
		return mIsEnabled;
	}

	void GameEntity::SetEnabled(bool enabled)
	{
		mIsEnabled = enabled;
	}

	void GameEntity::Initialize()
	{
	}

	void GameEntity::Shutdown()
	{
	}

	/*void GameEntity::Update(const GameTime & gameTime)
	{
	}*/
}

