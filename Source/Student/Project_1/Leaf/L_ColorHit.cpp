#include <pch.h>
#include "L_ColorHit.h"
#include "L_AgentW.h"
#include "../Agent/BehaviorAgent.h"

void L_ColorHit::on_enter()
{
 
    BehaviorNode::on_leaf_enter();

    //display_leaf_text();
}
void L_ColorHit::on_update(float dt) {
    Vec3 color = Vec3(((float)((rand() % 360)) / (float)100), ((float)((rand() % 360)) / (float)100), ((float)((rand() % 360)) / (float)100));

    for (auto a : agents->get_all_agents_by_type("Ring")) {
        a->set_color(color);

    }

    on_success();
    std::cout << "done" << std::endl;
    display_leaf_text();

}