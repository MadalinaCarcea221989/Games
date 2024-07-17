#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Tank.h"
#include "BoundingBox.h"
#include "Collision.h"
#include <vector>
#include "Vector2.h"

class InputHandler {
public:
    static void MouseMove(int x, int y, int& mouseX, int& mouseY, bool mouseDown, Vector2& dragEnd);
    static void MouseDown(int button, int mouseX, int mouseY, bool& mouseDown, bool& tanksAwaitingTarget, Vector2& dragStart, std::vector<Tank*>& tank, Collision* col);
    static void MouseUp(int button, int mouseX, int mouseY, bool& mouseDown, bool& tanksAwaitingTarget, Vector2& dragEnd, std::vector<Tank*>& tank, int clickMouseX, int clickMouseY, Collision* col, Surface* screen);
};

#endif // INPUTHANDLER_H
