#include "precomp.h"
#include "AiTank.h"
#include "Tank.h"
#include "Vector2.h"
#include "Spriter.h"
#include "BulletCollision.h"
#include "Phaser.h"

using namespace Tmpl8;

AiTank::AiTank(int team, float x, float y, float speed, int rightFrame, int verticalAngle, int coolTime, int ammo, float health)
{
    this->x = x;
    this->y = y;
    this->nx = x;
    this->ny = y;
    this->speed = speed;
    this->rightFrame = rightFrame;
    this->verticalAngle = verticalAngle;
    this->coolTime = coolTime;// *2;
    this->ammo = ammo;
    this->health = health;
    this->bulletCol = bulletCol;

    aiTankBaseSprite = new Sprite(new Surface("assets/caitankbase.tga"), 16);
    aiTankShadowSprite = new Sprite(new Surface("assets/ctankshadow.tga"), 16);
    aiTankGunSprite = new Sprite(new Surface("assets/ctankgun.tga"), 16);
    phaserSprite = new Sprite(new Surface("assets/phaser.tga"), 16);
}

void AiTank::SetOpposingTanks(std::vector<Tank*> opposingTanks, BulletCollision* bulletCol)
{
    opposingTeamTanks = opposingTanks;
    this->bulletCol = bulletCol;
}

void AiTank::FindTarget(Tank* currentTarget)
{
    Tank* closestTank = nullptr;
    float closestDistance = 100000.0f;

    for (Tank* tank : opposingTeamTanks)
    {
        // Calculate the distance between the AI tank and the current tank
        float distance = sqrtf(powf(tank->GetX() - x, 2) + powf(tank->GetY() - y, 2));

        // Update the closest tank if the current tank is closer and not the current target
        if (distance < closestDistance)// && tank != currentTarget)
        {
            closestTank = tank;
            closestDistance = distance;
        }
    }
    // Set the target tank to the closest tank found
    target = closestTank;
}

bool AiTank::IsTargetInRange(Tank* target)
{
    if (!target)
        return false;

   /* if (target)
        std::cout << "\nNULLPTR\n";*/

    float distanceToTarget = sqrtf(powf(target->GetX() - x, 2) + powf(target->GetY() - y, 2));

    if (distanceToTarget < range) {
        // If the target is close, stop and shoot
        //Stop();
        //elapsedTime += 1;
        //if (elapsedTime >= coolTime) {
        //    Shoot();
        //    elapsedTime = 0;
        //    //std::cout << "the aitank has shooted\n";
        //}
        return true; // Indicate that the target is in range
    }
    return false; // Indicate that the target is not in range
}

void AiTank::Draw(Surface* screen)
{

    static int frame = 0;
    if (health <= 0)
    {
        aiTankShadowSprite->SetFrame(rightFrame);
        aiTankShadowSprite->Draw(screen, (int)x, (int)y);
    }
    else
    {

        while (rightFrame < 0)
            rightFrame += 16;

        aiTankBaseSprite->SetFlags(team * Spriter::FLARE);
        aiTankGunSprite->SetFlags(team * Spriter::FLARE);
        phaserSprite->SetFlags(team * Spriter::FLARE);

        aiTankBaseSprite->SetFrame(rightFrame);
        aiTankBaseSprite->Draw(screen, (int)x, (int)y);

        aiTankGunSprite->SetFrame(rightFrame);
        aiTankGunSprite->Draw(screen, (int)x, (int)y);

    }

    for (int i = 0; i < phasers.size(); i++)
    {
        phasers[i]->Draw(screen);
    }
}

void AiTank::Move()
{
    if (health > 0.0f)
    {
        x = nx;
        y = ny;
    }
}

void AiTank::TurnLeft()
{
    if (--rightFrame < 0) rightFrame = 15;
}

void AiTank::TurnRight()
{
    if (++rightFrame >= 15) rightFrame = 0;
}

void AiTank::Accelerate()
{
    speed += 0.1f;
    if (speed > maxSpeed) {
        speed = maxSpeed;
    }
}

void AiTank::Decelerate()
{
    speed -= 0.1f;
    if (speed < -maxSpeed) {
        speed = -maxSpeed;
    }
}

void AiTank::Stop()
{
    speed = 0.0f;
}

void AiTank::Premove()
{
    float angle = ((2 * PI) / 16) * rightFrame;
    nx = x + (sinf(angle) * speed);
    ny = y + (-cosf(angle) * speed);
    if (nx > SCRWIDTH - aiTankWidth)
        nx = SCRWIDTH - aiTankWidth;
    if (nx < 0)
        nx = 0;
    if (ny > SCRHEIGHT - aiTankHeight)
        ny = SCRHEIGHT - aiTankHeight;
    if (ny < 0)
        ny = 0;
}

void AiTank::Shoot()
{
    std::cout << elapsedTime << " " << coolTime << "\n";
    if ((ammo > 0) && (health > 0.0f) && (elapsedTime >= coolTime) && target->health >= 0.f && target)
    {
        --ammo;
        elapsedTime = 0;

        // Calculate the starting position of the phaser based on the tank's position and direction
        float phaserX = x + cosf(rightFrame) * aiTankWidth / 2;
        float phaserY = y + sinf(rightFrame) * aiTankWidth / 2;
        float phaserDirection = rightFrame;

        Phaser* newBullet = new Phaser(phaserX, phaserY, float2(target->x, target->y));
        phasers.push_back(newBullet);


    }
}


void AiTank::Think(float deltaTime) {

    bulletCol->CheckPhasersCollisionEnemy(phasers);
    if (health <= 0)
        return;

    float angleToTarget = 0;

    if (target)
        angleToTarget = atan2f(target->GetY() - y, target->GetX() - x);
    // Convert the angle to degrees
    int degreesToTarget = static_cast<int>(angleToTarget * 180.0f / PI);

    elapsedTime += deltaTime;


    for (int i = 0; i < phasers.size(); i++)
    {
        phasers[i]->Update(deltaTime);
    }

    if (!target || !IsTargetInRange(target) || target->health < 0.f)
    {
        FindTarget(target);
    }

    float targetX = x;
    float targetY = y;

    if (target)
    {
        targetX = target->GetX();
        targetY = target->GetY();
    }

    float2 directionVector(targetX - x, targetY - y);
    directionVector = normalize(directionVector);
    direction = atan2f(directionVector.y, directionVector.x);
    rightFrame = static_cast<int>((angleToTarget * 180.0f / PI) / 16.0f);

    // Calculate the angle difference between the AI tank's direction and the target angle
    int angleDifference = degreesToTarget - rightFrame;
    if (angleDifference < -180) {
        angleDifference += 360;
    }
    else if (angleDifference > 180) {
        angleDifference -= 360;
    }


    if (IsTargetInRange(target))
    {
        Stop();
        Shoot();
        bulletCol->CheckPhasersCollisionEnemy(phasers);
        return;
    }
    //IsTargetInRange(target);

    // Adjust the strategy based on the angle difference
    if (angleDifference > 10) {
        // If the angle difference is significant, turn right
        TurnRight();
    }
    else if (angleDifference < -10) {
        // If the angle difference is significant, turn left
        TurnLeft();
    }
    else {
        // If the angle difference is small, move towards the target
        Accelerate();
    }
    Premove();
    Move();
    Shoot();
    bulletCol->CheckPhasersCollisionEnemy(phasers);



}

void AiTank::UpdateBullets(float deltaTime)
{
    for (Phaser* phaser : phasers)
    {
        // Update the position of the bullet based on its direction and speed
        float bulletX = phaser->GetX();
        float bulletY = phaser->GetY();
        float bulletSpeed = phaser->GetSpeed();
        float bulletDirection = phaser->GetDirection();

        bulletX += cosf(bulletDirection) * bulletSpeed * deltaTime;
        bulletY += sinf(bulletDirection) * bulletSpeed * deltaTime;

        // Set the updated position back to the bullet object
        phaser->SetX(bulletX);
        phaser->SetY(bulletY);
    }
}

int AiTank::numberOfAiTanks = 6;
