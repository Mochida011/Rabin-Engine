#include <pch.h>
#include "L_AlgorithmPosition.h"
#include "Agent/BehaviorAgent.h"
//#include "Agent/CameraAgent.h"
//bool initialize = false;
void L_AlgorithmPosition::on_enter()
{

/*        targetGrid.col = 0;
        targetGrid.row = 4;  */  
        //Position = terrain->get_world_position(targetGrid);
        //agent->set_position(Position);
       
    agent->set_movement_speed(22);

    BehaviorNode::on_leaf_enter();
    


    
}



void L_AlgorithmPosition::on_update(float dt)
{


    //agent->set_movement_speed(12);
    
    // grab the current mouse pos
    const auto& mousePos = InputHandler::get_mouse_position();
    
    //std::cout << Position.x <<","<< Position.y <<"side"<<side<< std::endl;
    agent->get_blackboard().set_value("targetPos", targetGrid);
    auto pos = terrain->get_world_position(targetGrid);
    agent->get_blackboard().set_value("posPos", pos);
    const auto result = agent->move_toward_point(Position, dt);
    if (result) {

        switch (side) {
        case 0://left
            if (count == 8) {
                targetGrid.col = 0; targetGrid.row = 5 * count - 10;
            }
            else {
                targetGrid.col = 0; targetGrid.row = 5 * count - 2;
            }

            break;
        case 1://top
            if (count == 8) {
                targetGrid.row = 31; targetGrid.col = 5 * count - 13;
            }
            else {
                targetGrid.row = 31; targetGrid.col = 5 * count - 2;
            }

            break;
        case 2://right
            if (count == 8) {
                targetGrid.col = 28; targetGrid.row = 5 * count - 10;
            }
            else {
                targetGrid.col = 28; targetGrid.row = 5 * count - 2;
            }

            break;
        case 3:
            //bottom
            if (count == 8) {
                targetGrid.row = 0; targetGrid.col = 5 * count - 13;
            }
            else {
                targetGrid.row = 0; targetGrid.col = 5 * count - 2;
            }

            break;
        default:
            side = 0;
            break;

        }/*std::cout << targetGrid.col << " " << targetGrid.row << std::endl;*/

    
    }



    if (count < 8) {
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
