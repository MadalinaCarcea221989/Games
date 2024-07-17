#pragma once

namespace Tmpl8 {

	const int aiTankWidth = 50;
	const int aiTankHeight = 50;

	class BulletCollision;
	class Phaser;
	class AiTank
	{
	public:
		AiTank(int team = 1, float x = 0.0f, float y = 0.0f, float speed = 1.0f, int rightFrame = 0, int verticalAngle = 0, int coolTime = 30, int ammo = 100, float health = 100.0f);

		void SetOpposingTanks(std::vector<Tank*> opposingTanks, BulletCollision* bulletCol);
		void FindTarget(Tank* currentTarget);
		bool IsTargetInRange(Tank* target);
		void Think(float deltaTime);
		void UpdateBullets(float deltaTime);

		void Draw(Surface* screen);
		void Move();
		void TurnLeft();
		void TurnRight();
		void Accelerate();
		void Decelerate();
		void Stop();
		void Premove();
		void Shoot();

		int team = 1;

		float x, y, nx, ny;
		float health = 100;
		int rightFrame;
		float2 position = 0;
		float speed;
		float range = 350.f;
		int verticalAngle = 0;

		float coolTime = 5.f;
		float elapsedTime = 0;
		int ammo = 100;


		int numberOfTheAiTank = numberOfAiTanks;

		BulletCollision* bulletCol;
		Tank* target = nullptr;

		float2 direction = 0;
		float GetX() const { return x; }
		float GetY() const { return y; }

		std::vector<Tank*> opposingTeamTanks;
		std::vector<Phaser*> phasers;
		const float maxSpeed = 0.3f;

	private:
		Sprite* aiTankBaseSprite;
		Sprite* aiTankShadowSprite;
		Sprite* aiTankGunSprite;
		Sprite* phaserSprite;

		static int numberOfAiTanks;
		const float minSpeed = 0.1f;
	};
}