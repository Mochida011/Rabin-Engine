#include <pch.h>
#include "L_AlgorithmPosition.h"
#include "Agent/BehaviorAgent.h"
//#include "Agent/CameraAgent.h"
bool initialize = false;
void L_AlgorithmPosition::on_enter()
{
    // set animation, speed, etc

    // grab the target position from the blackboard
    //const auto& bb = agent->get_blackboard();
    //targetPoint = bb.get_value<Vec3>("Click Position");

    //const auto& plane = terrain->get_terrain_plane();
    //Vec2 center = Vec2 ( terrain->get_world_position / 2,(float)terrain->get_map_height()/ 2);
    //agent->set_color(Vec3(0,0,255));
    //const auto pos = renderer->screen_to_world(Position.x, Position.y, plane);
    //Position = pos.first;
    //agent->look_at_point(targetPoint);

    //Line(Vec2(0,10),Vec2(0,20),50);
    //if (initialize == false) {
        targetGrid.col = 0;
        targetGrid.row = 4;
        initialize = true;    
        Position = terrain->get_world_position(targetGrid);
        agent->set_position(Position);
       
    //}

    agent->set_movement_speed(6);

    BehaviorNode::on_leaf_enter();
    


    
}



void L_AlgorithmPosition::on_update(float dt)
{


    

    // grab the current mouse pos
    const auto& mousePos = InputHandler::get_mouse_position();
    
    //std::cout << Position.x <<","<< Position.y <<"side"<<side<< std::endl;
    agent->get_blackboard().set_value("targetPos", targetGrid);
    const auto result = agent->move_toward_point(Position, dt);
    if (result) {

        switch (side) {
        case 0://left
            if (count ==5) {
                targetGrid.col = 0; targetGrid.row = 4 * count - 6;
            }
            else {
                targetGrid.col = 0; targetGrid.row = 4 * count-2;
            }
            
            break;
        case 1://top
            if(count==5) {
                targetGrid.row = 14; targetGrid.col = 4 * count - 11;
            }
            else {
                targetGrid.row = 14; targetGrid.col = 4 * count-2;
            }
            
            break;
        case 2://right
            if (count==5) {
                targetGrid.col = 8; targetGrid.row = 4 * count - 11;
            }
            else {
                targetGrid.col = 8; targetGrid.row= 4 * count -2;
            }
            
            break;
        case 3:
            //bottom
            if (count==5) {
                targetGrid.row = 0; targetGrid.col = 4 * count -11;
            }
            else {
                targetGrid.row = 0; targetGrid.col = 4 * count -2;
            }
            
            break;
        default:
            side = 0;
            break;

        }

    
    }



    if (count < 5) {
        count++;

    }
    else {
        count = 1;
    }

    //0 = left
    //1 = top
    //2 = right
    //3 = bottom 
    side++;
    if (side > 3) {
        side = 0;
    }

    Position = terrain->get_world_position(targetGrid);
    // we want to know where on the ground the mouse was clicked
    const auto& plane = terrain->get_terrain_plane();
    
    // find out where on the plane the click happened
    
    
    //std::cout << "d" << std::endl;

    //if (result == true)
    //{
    //    on_success();
    //}

    display_leaf_text();
}
