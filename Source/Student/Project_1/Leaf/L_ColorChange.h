#pragma once

#include "BehaviorNode.h"

class K_ColorChange : public BaseNode<K_ColorChange>
{
protected:
    virtual void on_enter()override;
    virtual void on_update(float dt)override;
private:
    Vec3 m_color;
    int check = 1;
};