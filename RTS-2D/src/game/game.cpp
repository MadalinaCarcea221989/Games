#include "../templ/precomp.h"
#include "../player/Tank.h"
#include "../ai/AiTank.h"
#include "../map/Map.h"
#include "../collision/Collision.h"
#include "../weapons/Phaser.h"
#include "../collision/BulletCollision.h"
#include "../utils/BoundingBox.h"
#include "../utils/InputHandler.h"
#include "../utils/TankManager.h"
#include <iostream>

float frame_timer = 0.0f;

void Game::Init()
{
    InitializeTanks();
    InitializeMap();
    InitializeCollisions();
}

void Game::Update(float deltaTime)
{
    UpdateTanks(deltaTime);
}

void Game::Tick(float deltaTime)
{
    deltaTime /= 1000.0f;
    frame_timer += deltaTime;

    screen->Plot(SCRWIDTH - 2, SCRHEIGHT - 2, 0xffffff);

    mapTiles->DrawTileMap(screen);

    HandleSelectionBox();

    col->Collides(tank, aitank, tank.size());

    Update(deltaTime);

    if (tanksAwaitingTarget)
    {
        MoveSelectedTanksToTarget();
    }

    DrawAllTanks();
    UpdateAllTanks(deltaTime);
}

void Game::MouseMove(int x, int y)
{
    InputHandler::MouseMove(x, y, mouseX, mouseY, mouseDown, dragEnd);
}

void Game::MouseDown(int button)
{
    InputHandler::MouseDown(button, mouseX, mouseY, mouseDown, tanksAwaitingTarget, dragStart, tank, col);
}

void Game::MouseUp(int button)
{
    InputHandler::MouseUp(button, mouseX, mouseY, mouseDown, tanksAwaitingTarget, dragEnd, tank, dragStart, col, screen);
;
}

void Game::InitializeTanks()
{
    for (int i = 0; i < 6; i++)
    {
        tank.push_back(new Tank(0, 100 + i * 2, 100 + i * 80, 5.f, 0, 0, 5, 100, 100.0f, mouseX, mouseY));
        aitank.push_back(new AiTank(1, 1028 + i / 10, 100 + i * 80, 0.2f, 0, 0, 5, 100, 100.f));
    }

    bulletCol = new BulletCollision(tank, aitank, tank.size());

    for (int i = 0; i < 6; i++)
    {
        tank[i]->SetOpposingTanks(aitank, bulletCol);
        aitank[i]->SetOpposingTanks(tank, bulletCol);
    }
}

void Game::InitializeMap()
{
    mapTiles = new Map();
}

void Game::InitializeCollisions()
{
    col = new Collision();
}

void Game::UpdateTanks(float deltaTime)
{
    for (Tank* currentTank : tank)
    {
        if (currentTank->IsSelected())
        {
            currentTank->Premove();
            currentTank->Move();

            screen->Line((int)currentTank->GetX(), (int)currentTank->GetY(), clickMouseX, clickMouseY, 0xFF00FF);

            if (currentTank->GetX() == mouseX && currentTank->GetY() == mouseY)
            {
                currentTank->SetSelected(false);
            }
        }
    }
}

void Game::HandleSelectionBox()
{
    BoundingBox selectionBox = CreateBoundingBox(dragStart.x, dragStart.y, dragEnd.x, dragEnd.y);

    if (mouseDown)
    {
        dragEnd.x = mouseX;
        dragEnd.y = mouseY;

        selectionBox = CreateBoundingBox(dragStart.x, dragStart.y, dragEnd.x, dragEnd.y);
        screen->Box((int)selectionBox.left, (int)selectionBox.top, (int)selectionBox.right, (int)selectionBox.bottom, 0xFFFFFF);

        for (Tank* currentTank : tank)
        {
            float tankX = currentTank->GetX();
            float tankY = currentTank->GetY();

            if (PointInsideBoundingBox(tankX, tankY, selectionBox))
            {
                currentTank->SetSelected(true);
                screen->Box((int)tankX, (int)tankY, (int)(tankX + 50), (int)(tankY + 50), 0xFF0000);
            }
            else
            {
                currentTank->SetSelected(false);
            }
        }
    }
}

void Game::MoveSelectedTanksToTarget()
{
    for (Tank* currentTank : tank)
    {
        if (currentTank->IsSelected())
        {
            currentTank->Move();
            screen->Line((int)currentTank->GetX(), (int)currentTank->GetY(), clickMouseX, clickMouseY, 0xFF0000);
            col->TeamPlayerCollision(tank, tank.size());
        }
    }
}

void Game::DrawAllTanks()
{
    for (int i = 0; i < tank.size(); i++)
    {
        tank[i]->Draw(screen);
        tank[i]->Premove();
        tank[i]->Accelerate();
        tank[i]->Decelerate();
        tank[i]->Update(aitank[i], deltaTime);
        tank[i]->Stop();

        aitank[i]->Think(deltaTime);
        aitank[i]->Draw(screen);
        aitank[i]->Move();
    }
}

void Game::UpdateAllTanks(float deltaTime)
{
    for (int i = 0; i < tank.size(); i++)
    {
        col->Collides(tank, aitank, tank.size());
        Update(deltaTime);
        tank[i]->Update(aitank[i], deltaTime);
    }
}
