#pragma once
#include "GameEntity.h"

namespace Library_3
{
	class DrawableGameEntity : public GameEntity
	{
	public:
		DrawableGameEntity();
		DrawableGameEntity(Game& game);
		//DrawableGameEntity(Game& game, Camera& camera);
		virtual ~DrawableGameEntity() = default;

		DrawableGameEntity(const DrawableGameEntity& rhs) = delete;
		DrawableGameEntity& operator=(const DrawableGameEntity& rhs) = delete;

		DrawableGameEntity(const DrawableGameEntity&& rhs) = delete;
		DrawableGameEntity& operator=(const DrawableGameEntity&& rhs) = delete;

		bool IsVisible() const;
		void SetVisible(bool visible);

		//Camera* GetCamera();
		//void SetCamera(Camera* camera);

		virtual void Draw() = 0;

	protected:
		bool mIsVisible;
		//Camera* mCamera;
	};
}