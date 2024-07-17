#include "precomp.h"
#include "Phaser.h"
#include "Tank.h"
#include "AiTank.h"
#include "Spriter.h"


using namespace Tmpl8;

Phaser::Phaser(float x, float y, float2 target, float speed, int rightFrame, int timeToLive, int team, int killPower)
{
    this->x = x;
    this->y = y;
    this->nx = x;
    this->ny = y;
    this->rightFrame = rightFrame;
    this->speed = speed;
    this->timeToLive = timeToLive;
    this->team = team;
    this->killPower = killPower;

    movementDirection = target - float2(x, y);
    movementDirection = normalize(movementDirection);

    phaserSprite = new Sprite(new Surface("assets/phaser.tga"), 16);
}

void Phaser::Stop()
{
    speed = 0.0f;
}

void Phaser::Premove()
{
    float angle = ((2 * PI) / 16) * rightFrame;
    nx = x + movementDirection.x * speed;//(sinf(angle) * speed);
    ny = y + movementDirection.y * speed;//(cosf(angle) * speed);

    if (nx > SCRWIDTH - tankWidth)
        nx = SCRWIDTH - tankWidth;
    if (nx < 0)
        nx = 0;
    if (ny > SCRHEIGHT - tankHeight)
        ny = SCRHEIGHT - tankHeight;
    if (ny < 0)
        ny = 0;

}
void Phaser::Move()
{
    if (timeToLive > 0)
    {
        x = nx;
        y = ny;
    }
}

void Phaser::Draw(Surface* screen)
{
    static int frame = 0;
    if (timeToLive <= 0)
    {
        //don't draw anything!
    }
    else
    {
        phaserSprite->SetFlags(Spriter::FLARE);
        while (rightFrame < 0)
            rightFrame += 16;
        rightFrame = rightFrame % 16;
        phaserSprite->SetFrame(rightFrame);
        phaserSprite->Draw(screen, (int)(x + tankWidth / 2), (int)y);

    }

}

bool Phaser::IsDead() const
{
    if (timeToLive < 0)
        return true;
    return false;
}

void Phaser::Update(float deltaTime)
{
    //timeToLive -= deltaTime;
    if (timeToLive > 0)
    {
        Premove();
        Move();
        timeToLive -= deltaTime;
        x = nx;
        y = ny;

    }
}
