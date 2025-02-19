#ifndef GAME_H
#define GAME_H

namespace Tmpl8 {
	
	class Game : public TheApp
	{
	public:
		Game();  // Constructor
		~Game(); // Destructor

		void Init();
		void Update(float deltaTime);
		void Tick(float deltaTime);
		void MouseMove(int x, int y);
		void MouseDown(int button);
		void MouseUp(int button);

	private:
		void InitializeTanks();
		void InitializeMap();
		void InitializeCollisions();
		void UpdateTanks(float deltaTime);
		void HandleSelectionBox();
		void MoveSelectedTanksToTarget();
		void DrawAllTanks();
		void UpdateAllTanks(float deltaTime);

		std::vector<Tank*> tank;
		std::vector<AiTank*> aitank;
		Map* mapTiles;
		Collision* col;
		BulletCollision* bulletCol;
		Surface* screen;  // Assuming a Screen class for drawing operations

		float deltaTime;
		float frame_timer;
		bool mouseDown;
		bool tanksAwaitingTarget;
		int mouseX, mouseY;
		int clickMouseX, clickMouseY;
		Vector2 dragStart, dragEnd;
	
	private:
		int mouseX, mouseY;
	};
}

#endif // GAME_H
