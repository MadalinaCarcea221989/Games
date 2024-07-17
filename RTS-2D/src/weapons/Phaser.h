#pragma once

namespace Tmpl8
{
	class Phaser
	{
	public:

		Phaser(float x, float y, float2 targetPosition, float speed = 4.5f, int rightFrame = 0, int timeToLive = 180, int team = 0, int killPower = 101);

		void Stop();
		void Move();
		void Premove();
		void Draw(Surface* screen);
		bool IsDead() const;
		void Update(float deltaTime);

		float x, y, nx, ny;
		int rightFrame;
		int killPower = 101;
		float speed = 2.5f;
		//int direction;
		int timeToLive = 80;
		float2 movementDirection = float2(0);

		int team; //0:allied, 1: enemy

		float GetX() const { return x; }
		float GetY() const { return y; }
		float GetSpeed() const { return speed; }
		float GetDirection() const { return rightFrame; }

		//float GetWidth() const { return phaserWidth; }
		//float GetHeight() const { return phaserHeight; }

		float SetX(float newX) { return newX; }
		float SetY(float newY) { return newY; }

	private:
		Sprite* phaserSprite;
		

	};
}