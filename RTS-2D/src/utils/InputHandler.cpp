#include "precomp.h"
#include "InputHandler.h"

using namespace Tmpl8;

void InputHandler::MouseMove(int x, int y, int& mouseX, int& mouseY, bool mouseDown, Vector2& dragEnd)
{
    mouseX = x;
    mouseY = y;
    if (mouseDown)
    {
        dragEnd.x = x;
        dragEnd.y = y;
    }
}

void InputHandler::MouseDown(int button, int mouseX, int mouseY, bool& mouseDown, bool& tanksAwaitingTarget, Vector2& dragStart, std::vector<Tank*>& tank, Collision* col)
{
    if (button == 0) // Left mouse button
    {
        mouseDown = true;
        tanksAwaitingTarget = true;
        dragStart.x = mouseX;
        dragStart.y = mouseY;

        for (Tank* currentTank : tank)
        {
            currentTank->SetSelected(false);
            col->TeamPlayerCollision(tank, tank.size());
        }
    }
    else if (button == 1) // Right mouse button
    {
        col->TeamPlayerCollision(tank, tank.size());
    }
}

void InputHandler::MouseUp(int button, int mouseX, int mouseY, bool& mouseDown, bool& tanksAwaitingTarget, Vector2& dragEnd, std::vector<Tank*>& tank, Vector2& dragStart, Collision* col, Surface* screen)
{
    if (button == 0) // Left mouse button
    {
        mouseDown = false;
        tanksAwaitingTarget = false;

        dragEnd.x = mouseX;
        dragEnd.y = mouseY;

        BoundingBox selectionBox = CreateBoundingBox(dragStart.x, dragStart.y, dragEnd.x, dragEnd.y);

        for (Tank* currentTank : tank)
        {
            float tankX = currentTank->GetX();
            float tankY = currentTank->GetY();

            if (PointInsideBoundingBox(tankX, tankY, selectionBox))
            {
                // Tank is within the selection box, apply the box outline
                currentTank->SetSelected(true);
                screen->Box((int)tankX, (int)tankY, (int)(tankX + 50), (int)(tankY + 50), 0xFF0000);
            }
            else
            {
                // Tank is outside the selection box, remove the box outline
                currentTank->SetSelected(false);
            }
        }
    }
}
