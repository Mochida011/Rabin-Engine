#include <pch.h>
#include "L_FormD.h"
#include "Agent/BehaviorAgent.h"
//#include "Agent/CameraAgent.h"


void L_FormD::on_enter()
{

    BehaviorNode::on_leaf_enter();




}

void L_FormD::on_update(float dt)
{
    // grab the current mouse pos
    const auto& mousePos = InputHandler::get_mouse_position();
    auto agentPos = (BehaviorAgent*)agents->get_all_agents_by_type("DVDAgent")[0];
    auto agentGrid = agentPos->get_blackboard().get_value<GridPos>("targetPos");
        //errain->get_grid_position(agents->get_all_agents_by_type("DVDAgent")[0]->get_position());
        
    GridPos grid;
    grid.col = agentGrid.col;
    grid.row = agentGrid.row;
    agentPos->set_movement_speed(13);
    agentPos->set_scaling(1.5);
    Position = terrain->get_world_position(grid);
    // we want to know where on the ground the mouse was clicked
    const auto& plane = terrain->get_terrain_plane();

    // find out where on the plane the click happened
    const auto worldPos = renderer->screen_to_world(mousePos.x, mousePos.y, plane);
    //const auto pos = renderer->screen_to_world((int)Position.x, (int)Position.y, plane);
    //const auto result = agent->move_toward_point(Position, dt);
    //agent->set_position(pospos);
    const float fixedDt = dt;
    for (auto a : agents->get_all_agents_by_type("D")) {

        a->set_scaling(1.5);
        a->set_movement_speed(1);
        BehaviorAgent* temp = (BehaviorAgent*)a;
        
        Position = terrain->get_world_position(grid);
        temp->move_toward_point(Position,fixedDt);
        //Position.z += 500;
        grid.row++;

    }
    grid.col =agentGrid.col+1;
    grid.row = agentGrid.row;


      Position2 = terrain->get_world_position(grid);
    for (int i = 0; i < agents->get_all_agents_by_type("DC").size(); i++) {
        agents->get_all_agents_by_type("DC")[i]->set_scaling(2);
        agents->get_all_agents_by_type("DC")[i]->set_movement_speed(1);
        BehaviorAgent* temp = (BehaviorAgent*)agents->get_all_agents_by_type("DC")[i];
        
        if (i<2) {
            
            
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
           
            temp->move_toward_point(Position2, fixedDt);
            //grid.col++;
             Position2.z += 2;
        }
        else if(i<4){
            //grid.row++;
            Position2.x += 2;
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
            //Position2 = terrain->get_world_position(grid);
            temp->move_toward_point(Position2, fixedDt);
        }
        else if (i<6) {
            //grid.col--;
            //grid.row++;
            Position2.z -= 2;
            Position2.x += 2;
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
            //Position2 = terrain->get_world_position(grid);
            temp->move_toward_point(Position2, fixedDt);
        }
        else {
            //grid.col--;
            //Position2.z -= 2;
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
            //Position2 = terrain->get_world_position(grid);
            temp->move_toward_point(Position2, fixedDt);
        }
    }
    grid.col = agentGrid.col+ 9;
    grid.row = agentGrid.row;
    for (auto a : agents->get_all_agents_by_type("D2")) {

        a->set_scaling(1.5);
        a->set_movement_speed(1);
        BehaviorAgent* temp = (BehaviorAgent*)a;

        Position = terrain->get_world_position(grid);
        temp->move_toward_point(Position, fixedDt);
        //Position.z += 500;
        grid.row++;

    }
    grid.col = agentGrid.col + 1+9;
    grid.row = agentGrid.row;


    Position2 = terrain->get_world_position(grid);
    for (int i = 0; i < agents->get_all_agents_by_type("DC2").size(); i++) {
        agents->get_all_agents_by_type("DC2")[i]->set_scaling(2);
        agents->get_all_agents_by_type("DC2")[i]->set_movement_speed(1);
        BehaviorAgent* temp = (BehaviorAgent*)agents->get_all_agents_by_type("DC2")[i];

        if (i < 2) {


            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;

            temp->move_toward_point(Position2, fixedDt);
            //grid.col++;
            Position2.z += 2;
        }
        else if (i < 4) {
            //grid.row++;
            Position2.x += 2;
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
            //Position2 = terrain->get_world_position(grid);
            temp->move_toward_point(Position2, fixedDt);
        }
        else if (i < 6) {
            //grid.col--;
            //grid.row++;
            Position2.z -= 2;
            Position2.x += 2;
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
            //Position2 = terrain->get_world_position(grid);
            temp->move_toward_point(Position2, fixedDt);
        }
        else {
            //grid.col--;
            Position2.z -= 2;
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
            //Position2 = terrain->get_world_position(grid);
            temp->move_toward_point(Position2, fixedDt);
        }
    }

   
    //agent->get_id();
    //const auto pos2 = renderer->screen_to_world(40, 50,plane);
    bool result = agent->move_toward_point(Position, fixedDt);
    
    

    //std::cout << "d" << std::endl;
    //std::cout << "Position"<<Position.x<<" "<<Position.y << std::endl;

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}
