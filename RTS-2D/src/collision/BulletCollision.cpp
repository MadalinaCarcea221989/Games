#include "precomp.h"
#include "BulletCollision.h"
#include "Tank.h"
#include "AiTank.h"
#include "Phaser.h"
#include "Vector2.h"

using namespace Tmpl8;

BulletCollision::BulletCollision(std::vector<Tank*> tabTanksP, std::vector<AiTank*> tabTanksAi, int numTanks)
{
    this->tabTanksP = tabTanksP;
    this->tabTanksAi = tabTanksAi;
}

void BulletCollision::CheckPhasersCollisionEnemy(std::vector<Phaser*> tabPhasers)
{
    for (int t = 0; t < tabTanksP.size(); ++t)
    {
        for (int p = 0; p < tabPhasers.size(); ++p)
        {
            if ((tabPhasers[p]->team != tabTanksP[t]->team) && // Different teams
                (tabTanksP[t]->health > 0.0f) &&               // Tank still alive
                (tabPhasers[p]->timeToLive > 0))               // Phaser didn't already hit another tank from the opposite team
            {
                Vector2 diff(tabTanksP[t]->nx - tabPhasers[p]->nx, tabTanksP[t]->ny - tabPhasers[p]->ny);
                float dist = diff.length();
                if (dist < (tankWidth + tankHeight) / 2.0f)
                {
                    tabPhasers[p]->timeToLive = 0;
                    tabTanksP[t]->health = tabTanksP[t]->health - tabPhasers[p]->killPower;
                }
            }
            else if (tabTanksP[t]->health <= 0.0f){}
        }
    }
}

void BulletCollision::CheckPhasersCollisionPlayer(std::vector<Phaser*> tabPhasers)
{
    for (t = 0; t < tabTanksAi.size(); ++t)
    {
        for (p = 0; p < tabPhasers.size(); ++p)
        {
            if ((tabPhasers[p]->team != tabTanksAi[t]->team) && //different teams
                (tabTanksAi[t]->health > 0.0f) &&                 //tank still alive
                (tabPhasers[p]->timeToLive > 0)                        //phaser didn't already hit another tank from opposite team
                )
            {
                Vector2 diff(tabTanksAi[t]->nx - tabPhasers[p]->nx, tabTanksAi[t]->ny - tabPhasers[p]->ny);
                float dist = diff.length();
                if ((dist < (tankWidth + tankHeight) / 2.0f))
                {
                    tabPhasers[p]->timeToLive = 0;
                    tabTanksAi[t]->health = tabTanksAi[t]->health - tabPhasers[p]->killPower;
                }
            }
            else if (tabTanksAi[t]->health <= 0.0f) {}
        }
    }
}

//bool BulletCollision::CheckPixelPerfectCollision(Tank* tank, Phaser* phaser)
//{
//    // Get pixel data from the sprites
//    const std::vector<uint32_t>& tankPixels = tank->GetSprite()->GetPixelData();
//    const std::vector<uint32_t>& phaserPixels = phaser->GetSprite()->GetPixelData();
//
//    // Determine the overlapping area
//    int xStart = std::max(tank->GetX(), phaser->GetX());
//    int yStart = std::max(tank->GetY(), phaser->GetY());
//    int xEnd = std::min(tank->GetX() + tank->GetWidth(), phaser->GetX() + phaser->GetWidth());
//    int yEnd = std::min(tank->GetY() + tank->GetHeight(), phaser->GetY() + phaser->GetHeight());
//
//    // Check every pixel in the overlapping area for a collision
//    for (int y = yStart; y < yEnd; ++y)
//    {
//        for (int x = xStart; x < xEnd; ++x)
//        {
//            // Check if pixels at (x, y) in both sprites are not transparent
//            if (tankPixels[y * tank->GetWidth() + x] != 0 && phaserPixels[y * phaser->GetWidth() + x] != 0)
//            {
//                return true; // Collision detected
//            }
//        }
//    }
//
//    return false; // No collision
//}