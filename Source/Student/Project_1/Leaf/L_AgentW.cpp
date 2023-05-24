#include <pch.h>
#include "L_AgentW.h"
#include "Agent/BehaviorAgent.h"
//#include "Agent/CameraAgent.h"
extern bool stop;

void L_AgentW::on_enter()
{

    BehaviorNode::on_leaf_enter();

    stop = true;


}

void L_AgentW::on_update(float dt)
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
    agentPos->set_scaling(2);
    Position = terrain->get_world_position(grid);
    // we want to know where on the ground the mouse was clicked
    const auto& plane = terrain->get_terrain_plane();

    // find out where on the plane the click happened
    const auto worldPos = renderer->screen_to_world(mousePos.x, mousePos.y, plane);
    //const auto pos = renderer->screen_to_world((int)Position.x, (int)Position.y, plane);
    //const auto result = agent->move_toward_point(Position, dt);
    //agent->set_position(pospos);
    const float fixedDt = dt;
    Vec3 white(200.f, 200.f, 200.f);
    for (auto a : agents->get_all_agents_by_type("D")) {

        BehaviorAgent* temp = (BehaviorAgent*)a;
        temp->set_color(white);
    }

    for (int i = 0; i < agents->get_all_agents_by_type("DC").size(); i++) {
        BehaviorAgent* temp = (BehaviorAgent*)agents->get_all_agents_by_type("DC")[i];
        temp->set_color(white);
    }

    for (auto a : agents->get_all_agents_by_type("D2")) {

        BehaviorAgent* temp = (BehaviorAgent*)a;
        temp->set_color(white);

    }

    for (int i = 0; i < agents->get_all_agents_by_type("DC2").size(); i++) {

        BehaviorAgent* temp = (BehaviorAgent*)agents->get_all_agents_by_type("DC2")[i];
        temp->get_blackboard().set_value("color",0);
        temp->set_color(white);

    }

    for (int i = 0; i < agents->get_all_agents_by_type("V").size(); i++) {

        BehaviorAgent* temp = (BehaviorAgent*)agents->get_all_agents_by_type("V")[i];
        
        temp->set_color(white);

    }

    //agent->get_id();
    //const auto pos2 = renderer->screen_to_world(40, 50,plane);

    on_success();


    display_leaf_text();
}
