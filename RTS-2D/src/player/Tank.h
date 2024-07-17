#pragma once

namespace Tmpl8 {

	const int tankWidth = 50;
	const int tankHeight = 50;
	const float maxSpeed = 2.0f;

	class BulletCollision;
	class Phaser;
	class AiTank;

	class Tank
	{
	public:
		Tank(int team = 0, float x = 0.0f, float y = 0.0f, float speed = 0.2f, int direction = 0, int verticalAngle = 0, int coolTime = 30, int ammo = 100, float health = 100.0f, float targetX = 0.f, float targetY = 0.f);

		void SetOpposingTanks(std::vector<AiTank*> opposingTanks, BulletCollision* bulletCol);
		void TimeRemaining(float deltaTime);
		void Draw(Surface* screen);
		void Move();
		void TurnLeft();
		void TurnRight();
		void Update(AiTank* target, float deltaTime);
		void Accelerate();
		void Decelerate();
		void Stop();
		void Shoot();
		void Premove();
		void SetTargetPosition(float targetX, float targetY);
		bool IsPointInside(float pointX, float pointY) const;
		void FindTarget();
		bool IsTargetInRange(AiTank* target);

		float GetX() const { return x; }
		float GetY() const { return y; }

		float GetWidth() const { return tankWidth; }
		float GetHeight() const { return tankHeight; }

		int team = 0;
		float movementSpeed = 0;
		float targetX = 0;
		float targetY = 0;
		float x, y, nx, ny;

		float coolTime = 5.f;
		int ammo = 100;
		float range = 350.f;
		float health = 100.0f;
		int direction = 0;
		float speed = 0;
		int verticalAngle = 0;
		float elapsedTime = 0.f;
		int rotationSpeed = 0;
		float2 movementDirection = float2(0);
		AiTank* target;

		BulletCollision* bulletCol;

		static int numberOfTanks;

		

		bool isSelected = false;
		bool selected = false;
		bool showOutline = false;
		bool tanksAwaitingTarget = false;

		bool HasBoxOutline() const { return hasBoxOutline; }
		void SetBoxOutline(bool outline) { hasBoxOutline = outline; }

		bool hasBoxOutline = false;

		bool IsSelected() const { return isSelected; }
		void SetSelected(bool selected) { isSelected = selected; }

		int numberOfTheTank = ++numberOfTanks;
		std::vector<AiTank*> opposingTeamTanks;

	private:
		Sprite* tankBaseSprite;
		Sprite* tankShadowSprite;
		Sprite* tankGunSprite;
		Sprite* phaserSprite;

		std::vector<Phaser*> phasers;
		float targetPositionX = 0.f;
		float targetPositionY = 0.f;
	};

} // namespace Tmpl8
