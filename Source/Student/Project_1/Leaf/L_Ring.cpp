#include <pch.h>
#include "L_Ring.h"
#include "Agent/BehaviorAgent.h"
//#include "Agent/CameraAgent.h"


void L_Ring::on_enter()
{

    BehaviorNode::on_leaf_enter();

}

void L_Ring::on_update(float dt)
{
    const float fixedDt = dt;
    // grab the current mouse pos
    auto ogpos = agent->get_position();
    //std::cout << agent->get_position().x<<" "<<agent->get_position().z << std::endl;
    const auto& plane = terrain->get_terrain_plane();
    float angle = 360.f / (float)agents->get_all_agents_by_type("Ring").size();
    BehaviorAgent* D = (BehaviorAgent*)agents->get_all_agents_by_type("V")[2];
    
    GridPos gPos,gPos2; gPos.col = 8; gPos.row = 5; gPos2.col = 0; gPos2.row = 0;
    auto TempPos = terrain->get_world_position(gPos)- terrain->get_world_position(gPos2);
    //std::cout << TempPos.x<<" "<<TempPos.z<<std::endl;
    for (int i = 0; i < agents->get_all_agents_by_type("Ring").size();i++) {
        BehaviorAgent* temp = (BehaviorAgent*)agents->get_all_agents_by_type("Ring")[i];
        auto postomove=TempPos;
        postomove.x = TempPos.x * cosf(angle*i);
        postomove.z = TempPos.z * sinf(angle*i);
        postomove += D->get_position();
        temp->set_scaling(1);
        temp->move_toward_point(postomove,fixedDt);
    }

    //agent->get_id();
    //const auto pos2 = renderer->screen_to_world(40, 50,plane);
    Vec3 positionh=TempPos;
    positionh.y = 0; 
    
    bool result = agent->move_toward_point(positionh, fixedDt);

    if (result == true)
    {
        //on_success();
    }

    display_leaf_text();
}
