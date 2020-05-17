#pragma once

namespace Library_3
{
	class Game;
	//class GameTime;

	class GameEntity
	{

	public:
		GameEntity();
		GameEntity(Game& game);
		virtual ~GameEntity() = default;

		GameEntity(const GameEntity& rhs) = delete;
		GameEntity& operator=(const GameEntity& rhs) = delete;

		GameEntity(const GameEntity&& rhs) = delete;
		GameEntity& operator=(const GameEntity&& rhs) = delete;

		Game* GetGame();
		void SetGame(Game& game);
		bool Enabled() const;
		void SetEnabled(bool enabled);

		virtual void Initialize();
		virtual void Shutdown();
		//virtual void Update(const GameTime& gameTime);

	protected:
		Game* mGame;
		bool mIsEnabled;
	};
}
