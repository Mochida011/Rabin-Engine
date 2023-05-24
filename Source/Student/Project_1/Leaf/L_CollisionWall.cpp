#include <pch.h>
#include "L_CollisionWall.h"
#include "Agent/BehaviorAgent.h"
//#include "Agent/CameraAgent.h"



void L_CollisionWall::on_update(float dt)
{
    // grab the current mouse pos
    BehaviorAgent* temp = (BehaviorAgent*)agents->get_all_agents_by_type("DVDAgent")[0];
    if (temp->get_blackboard().get_value<Vec3>("posPos") != Position) {
        
        std::cout << Position.x << std::endl;
        //std::cout << "heh" << std::endl;
        Position = temp->get_blackboard().get_value<Vec3>("posPos");
       on_failure();
    }
    else {
        on_success();

        //std::cout << "heh2" << std::endl;
    }

    //// find out where on the plane the click happened
    //const auto worldPos = renderer->screen_to_world(mousePos.x, mousePos.y, plane);
    //const auto pos = renderer->screen_to_world((int)Position.x, (int)Position.y, plane);
    //const auto result = agent->move_toward_point(Position, dt);

    //std::cout << "d" << std::endl;

    //if (result == true)
    //{
    //    on_success();
    //}

    display_leaf_text();
}
