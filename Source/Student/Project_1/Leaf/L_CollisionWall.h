#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_CollisionWall: public BaseNode<L_CollisionWall>
{
public:
    bool AABB(Vec3 currPos, Vec3 TL, Vec3 TR, Vec3 BR, Vec3 BL) {

        if (currPos.x <= TL.x) {
            return true;
        }
        if (currPos.x >= TR.x) {
            return true;
        }
        if (currPos.y >= BL.y) {
            return true;
        }
        if (currPos.y <= TL.y) {
            return true;
        }
        return false;
    }
protected:


    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    Vec3 Position;
};