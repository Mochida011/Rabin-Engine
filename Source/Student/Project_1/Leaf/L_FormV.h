#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_FormV : public BaseNode<L_FormV>
{
protected:
    virtual void on_enter();
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    Vec3 Position, Position2;
};