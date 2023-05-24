#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_CollisionWall: public BaseNode<L_CollisionWall>
{
public:

    
protected:


    virtual void on_update(float dt);

private:
    Vec3 targetPoint;
    Vec3 Position;

};