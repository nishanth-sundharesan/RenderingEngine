#include "PchLibrary.h"
#include "DrawableGameEntity.h"

namespace Library
{
	DrawableGameEntity::DrawableGameEntity() :
		GameEntity(),
		mIsVisible(false)
	{
	}

	DrawableGameEntity::DrawableGameEntity(Game& game) :
		GameEntity(game),
		mIsVisible(true)
	{
	}

	bool DrawableGameEntity::IsVisible() const
	{
		return mIsVisible;
	}

	void DrawableGameEntity::SetVisible(bool visible)
	{
		mIsVisible = visible;
	}
}