#include <pch.h>
#include "D_Delay10.h"

D_Delay10::D_Delay10() : delay(10.0f)
{}

void D_Delay10::on_enter()
{
    /*delay = RNG::range(1.0f, 2.0f);*/

    BehaviorNode::on_enter();
}

void D_Delay10::on_update(float dt)
{
    delay -= dt;

    if (delay < 0.0f)
    {
        BehaviorNode* child = children.front();

        child->tick(dt);

        // assume same status as child
        set_status(child->get_status());
        set_result(child->get_result());
    }
}
