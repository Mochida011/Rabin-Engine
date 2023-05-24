#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_Ring: public BaseNode<L_Ring>
{
protected:
    virtual void on_enter();
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    float radx = 6.f; float rady = 2.5f;
    Vec3 Position, Position2;
};