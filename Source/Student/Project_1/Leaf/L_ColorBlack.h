#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_ColorBlack : public BaseNode<L_ColorBlack>
{
protected:
    virtual void on_enter();
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    GridPos gridd;
    int gridx = 0; int gridy = 0; int gridendx = 39; int gridendy = 39;
    int ring = 0; 
    Vec3 Position, Position2;
};