#pragma once
namespace Tmpl8 {

	class BulletCollision
	{
	public:

		BulletCollision(std::vector<Tank*> tabTanksP, std::vector<AiTank*> tabTanksAi, int numTanks);

		void CheckPhasersCollisionEnemy(std::vector<Phaser*> phasers);
		void CheckPhasersCollisionPlayer(std::vector<Phaser*> phasers);

		//bool CheckPixelPerfectCollision(Tank* tank, Phaser* phaser);

		std::vector<Tank*> tabTanksP;
		std::vector<AiTank*> tabTanksAi;
		int t, p;
	};
}