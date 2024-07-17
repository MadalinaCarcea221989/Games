#include "precomp.h"
#include "Collision.h"
#include "Tank.h"
#include "Vector2.h"
#include "AiTank.h"

using namespace Tmpl8;

Collision::Collision() {}
void Collision::Collides(std::vector<Tank*> tabTanksP, std::vector<AiTank*> tabTankAi, int numTanks)
{
    for (int i = 0; i < numTanks; i++)
    {
        float tankPLeft = tabTanksP[i]->x;
        float tankPTop = tabTanksP[i]->y;
        float tankPRight = tabTanksP[i]->x + tankWidth;
        float tankPBottom = tabTanksP[i]->y + tankHeight;

        for (int j = 0; j < numTanks; j++)
        {
            float tankAILeft = tabTankAi[j]->x;
            float tankAITop = tabTankAi[j]->y;
            float tankAIRight = tabTankAi[j]->x + aiTankWidth;
            float tankAIBottom = tabTankAi[j]->y + aiTankHeight;

            if (tankPRight >= tankAILeft && tankPLeft <= tankAIRight &&
                tankPBottom >= tankAITop && tankPTop <= tankAIBottom)
            {
                // AABB collision detected
                tabTanksP[i]->nx = tabTanksP[i]->x;
                tabTanksP[i]->ny = tabTanksP[i]->y;
                tabTankAi[j]->nx = tabTankAi[j]->x;
                tabTankAi[j]->ny = tabTankAi[j]->y;

                tabTanksP[i]->Stop();
                tabTankAi[j]->Stop();

                std::cout << "AFTER COL\n";
            }
        }
    }
}
void Collision::TeamPlayerCollision(std::vector<Tank*> tabTanksP, int numTeamTanks)
{
    for (int i = 0; i < numTeamTanks; i++)
    {
        float tankP1Left = tabTanksP[i]->x;
        float tankP1Top = tabTanksP[i]->y;
        float tankP1Right = tabTanksP[i]->x + tankWidth;
        float tankP1Bottom = tabTanksP[i]->y + tankHeight;

        for (int j = i + 1; j < numTeamTanks; j++)
        {
            float tankP2Left = tabTanksP[j]->x;
            float tankP2Top = tabTanksP[j]->y;
            float tankP2Right = tabTanksP[j]->x + tankWidth;
            float tankP2Bottom = tabTanksP[j]->y + tankHeight;

            if (tankP1Right >= tankP2Left && tankP1Left <= tankP2Right &&
                tankP1Bottom >= tankP2Top && tankP1Top <= tankP2Bottom)
            {
                // AABB collision detected
                float dx = tabTanksP[j]->x - tabTanksP[i]->x;
                float dy = tabTanksP[j]->y - tabTanksP[i]->y;

                // Calculate the distance between the tanks
                float distance = std::sqrt(dx * dx + dy * dy);

                // Calculate the amount to push each tank back
                float pushBackAmount = (tankWidth - distance) / 2.0f;

                // Calculate the push back vectors for each tank
                float pushBackX = (dx / distance) * pushBackAmount;
                float pushBackY = (dy / distance) * pushBackAmount;

                // Push the tanks back
                tabTanksP[i]->x -= pushBackX;
                tabTanksP[i]->y -= pushBackY;
                tabTanksP[j]->x += pushBackX;
                tabTanksP[j]->y += pushBackY;
            }
        }
    }
}