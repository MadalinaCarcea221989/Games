#include "precomp.h"
#include "Tank.h"
#include "Vector2.h"
#include "Phaser.h"
#include "Spriter.h"
#include "AiTank.h"
#include "BulletCollision.h"
#include <vector>

Tank::Tank(int team, float x, float y, float speed, int direction, int verticalAngle, int coolTime, int ammo, float health, float targetX, float targetY) : bulletCol(nullptr)
{
    this->x = x;
    this->y = y;
    this->nx = x;
    this->ny = y;
    this->speed = speed;
    this->direction = direction;

    this->verticalAngle = verticalAngle;
    this->coolTime = coolTime;// *2;
    this->ammo = ammo;
    this->health = health;

    this->targetPositionX = targetX;
    this->targetPositionY = targetY;

    tankBaseSprite = new Sprite(new Surface("assets/ctankbase1.tga"), 16);
    tankShadowSprite = new Sprite(new Surface("assets/ctankshadow.tga"), 16);
    tankGunSprite = new Sprite(new Surface("assets/ctankgun.tga"), 16);
    phaserSprite = new Sprite(new Surface("assets/phaser.tga"), 16);

}

void Tank::SetOpposingTanks(std::vector<AiTank*> opposingTanks, BulletCollision* bulletCol)
{
    opposingTeamTanks = opposingTanks;
    this->bulletCol = bulletCol;
}

void Tank::TimeRemaining(float deltaTime)
{
    elapsedTime += deltaTime;
}

void Tank::Draw(Surface* screen)
{
    static int frame = 0;
    if (health <= 0)
    {
        tankShadowSprite->SetFrame(direction);
        tankShadowSprite->Draw(screen, (int)x, (int)y);
    }
    else
    {
        tankBaseSprite->SetFlags(team * Spriter::FLARE);
        tankGunSprite->SetFlags(team * Spriter::FLARE);
        phaserSprite->SetFlags(team * Spriter::FLARE);

        tankBaseSprite->SetFrame(direction);
        tankBaseSprite->Draw(screen, (int)x, (int)y);

        tankGunSprite->SetFrame(direction);
        tankGunSprite->Draw(screen, (int)x, (int)y);

        // phaserSprite->SetFrame(direction);
        //phaserSprite->Draw(screen, (int)(x + tankWidth / 2), (int)y);

    }

    for (int i = 0; i < phasers.size(); i++)
    {
        phasers[i]->Draw(screen);
    }
}

void Tank::FindTarget()
{
    AiTank* closestTank = nullptr;
    float closestDistance = 100000.0f;

    for (AiTank* tank : opposingTeamTanks)
    {
        if (tank->health < 0)
            continue;
        // Calculate the distance between the AI tank and the current tank
        float distance = sqrtf(powf(tank->GetX() - x, 2) + powf(tank->GetY() - y, 2));

        // Update the closest tank if the current tank is closer and not the current target
        if (distance < closestDistance)
        {
            closestTank = tank;
            closestDistance = distance;
        }
    }
    // Set the target tank to the closest tank found
    target = closestTank;
}

void Tank::Move()
{
    // Calculate the direction vector from the tank's current position to the target position
    float dirX = targetPositionX - x;
    float dirY = targetPositionY - y;

    // Calculate the magnitude of the direction vector
    float magnitude = sqrt(dirX * dirX + dirY * dirY);

    // Normalize the direction vector
    if (magnitude > 0)
    {
        dirX /= magnitude;
        dirY /= magnitude;
    }
    speed = 0.2f;
    // Calculate the new position based on the current position, direction, and speed
    float newX = x + movementDirection.x * speed;
    float newY = y + movementDirection.y * speed;

    // Check if the new position is within the bounds of the map
    if (newX >= 0 && newX < SCRWIDTH - tankWidth && newY >= 0 && newY < SCRHEIGHT - tankHeight)
    {
        // Update the tank's position
        x = newX;
        y = newY;
    }

    if (abs(x - targetPositionX) < 5 || abs(y - targetPositionY) < 5)
    {
        movementDirection = float2(0);
    }
}

void Tank::SetTargetPosition(float targetX, float targetY)
{
    this->targetPositionX = targetX;
    this->targetPositionY = targetY;

    movementDirection = float2(targetPositionX, targetPositionY) - float2(x, y);
    movementDirection = normalize(movementDirection);
}

bool Tank::IsPointInside(float pointX, float pointY) const
{
    // Calculate the tank's bounding box coordinates
    float left = x;
    float right = x + tankWidth;
    float top = y;
    float bottom = y + tankHeight;

    // Check if the point is inside the bounding box
    if (pointX >= left && pointX <= right && pointY >= top && pointY <= bottom)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tmpl8::Tank::IsTargetInRange(AiTank* target)
{

    float distanceToTarget = sqrtf(powf(target->GetX() - x, 2) + powf(target->GetY() - y, 2));

    if (distanceToTarget < range) {
        // If the target is close, stop and shoot
        //Stop();
        //elapsedTime += 1;
        //if (elapsedTime >= coolTime) {
          //  Shoot();
           // elapsedTime = 0;
            //std::cout << "the aitank has shooted\n";
        //}
        return true; // Indicate that the target is in range
    }
    return false; // Indicate that the target is not in range

}

void Tank::TurnLeft()
{
    if (--direction < 0) direction = 15;
}

void Tank::TurnRight()
{
    if (++direction >= 15) direction = 0;
}

void Tank::Accelerate()
{
    if (health > 0.0f) {
        speed += 0.5f;
        if (speed > maxSpeed) {
            speed = maxSpeed;
        }
    }
    else {
        speed = 0.0f;
    }
}

void Tank::Decelerate()
{
    if (health > 0.0f) {
        speed -= 0.5f;
        if (speed < -maxSpeed) {
            speed = -maxSpeed;
        }
    }
    else {
        speed = 0.0f;
    }
}

void Tank::Stop()
{
    speed = 0.0f;
}

void Tank::Premove()
{
    float angle = ((2 * PI) / 16) * direction;
    nx = x + (sinf(angle) * speed);
    ny = y + (-cosf(angle) * speed);
    if (nx > SCRWIDTH - tankWidth)
        nx = SCRWIDTH - tankWidth;
    if (nx < 0)
        nx = 0;
    if (ny > SCRHEIGHT - tankHeight)
        ny = SCRHEIGHT - tankHeight;
    if (ny < 0)
        ny = 0;
}

void Tank::Shoot()
{
    if ((ammo > 0) && (health > 0.0f) && (elapsedTime >= coolTime) && target && target->health > 0.0f) {
        --ammo;
        elapsedTime = 0;

        Phaser* p = new Phaser(x, y, float2(target->x, target->y), 4.5f, direction, ((!team) ? 180 : 90), team, 101);
        phasers.push_back(p);
    }
}

void Tank::Update(AiTank* target, float deltaTime)
{
    bulletCol->CheckPhasersCollisionPlayer(phasers);

    for (int i = 0; i < phasers.size(); i++)
    {
        phasers[i]->Update(deltaTime);
    }

    if (rotationSpeed != 0 && health > 0.0f)
    {
        direction = (direction + rotationSpeed + 16) % 16;
        rotationSpeed = 0; // Reset rotation speed to stop rotation
    }

    if (!target || !IsTargetInRange(target) || target->health < 0.f)
    {
        FindTarget();
    }
    float distanceToTarget = 1000.f;
    // Calculate the angle to the target tank
    if (target)
    {
        float angleToTarget = atan2f(target->GetY() - y, target->GetX() - x);

        // Convert the angle to degrees
        int degreesToTarget = static_cast<int>(angleToTarget * 180.0f / PI);

        // Check if tank has reached the target position
        distanceToTarget = sqrt(pow(targetPositionX - x, 2) + pow(targetPositionY - y, 2));
    }
    if (distanceToTarget > 100.0f)
    {
        // Move towards the target position
        Premove();
        Move();
    }
    else
    {
        // Tank has reached the target, stop movement

        // Check if there are any enemy AI tanks in range
        if (target && target->health > 0 && IsTargetInRange(target))
        {
            Stop();
            Shoot();
        }
    }
    // Update the elapsed time
    elapsedTime += deltaTime;
}
int Tank::numberOfTanks = 6;