#pragma once
#pragma once

#include "BehaviorNode.h"

class L_ColorHit : public BaseNode<L_ColorHit>
{
protected:
    virtual void on_enter()override;
    virtual void on_update(float dt)override;
private:
    Vec3 m_color;
    int check = 1;
};