#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_AlgorithmPosition: public BaseNode<L_AlgorithmPosition>
{//reflect angle 
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    Vec3 Position;
    GridPos targetGrid;


    int count=1; 
    int side = 0; 
};