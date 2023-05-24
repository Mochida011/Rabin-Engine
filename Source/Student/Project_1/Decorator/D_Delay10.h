#pragma once
#include "BehaviorNode.h"

class D_Delay10 : public BaseNode<D_Delay10>
{
public:
    D_Delay10();

protected:
    float delay;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};