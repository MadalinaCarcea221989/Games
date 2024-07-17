#pragma once

namespace Tmpl8
{
	class Map;
	class Tank;
	class AiTank;
	class Collision;
	class Phaser;
	class BulletCollision;
	class Game : public TheApp
	{
	public:
		// game flow methods
		void Init();
		void Update(float deltaTime);
		void Tick(float deltaTime);
		void Shutdown() { /* implement if you want to do something on exit */ }
		// input handling
		void MouseUp(int button);

		void MouseDown(int button);
		void MouseMove(int x, int y);
		void MouseWheel(float y) {};
		void ClickMouse(int x, int y) { clickMouseX = x; clickMouseY = y; }
		void KeyUp(int key) { /* implement if you want to handle keys */ }
		void KeyDown(int key) { /* implement if you want to handle keys */ }
		// data members
		int2 mousePos, focusStart;
		bool mouseDown = false;
		bool tanksAwaitingTarget = false;
		float zoom = 100;
		int clickMouseX, clickMouseY;
		std::vector<Tank*> tank;
		std::vector<AiTank*> aitank;
		Map* mapTiles;

		Collision* col;
		BulletCollision* bulletCol;

		int2 dragStart;
		int2 dragEnd;


	private:
		int mouseX, mouseY;
	};
} // namespace Tmpl8