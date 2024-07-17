#pragma once

namespace Tmpl8 {

	class Collision : public Game
	{

	public:

		Collision();
		void Collides(std::vector<Tank*> tabTanksP, std::vector<AiTank*> tabTankAi, int numTanks);

		void TeamPlayerCollision(std::vector<Tank*> tabTanksP, int numTeamTanks);

		int numAiTanks = 6;
		int numTeamTanks = 6;
		int numTanks = 12;
		float x=0;
		float y=0;
	};

}