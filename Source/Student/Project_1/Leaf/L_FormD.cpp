#include <pch.h>
#include "L_FormD.h"
#include "Agent/BehaviorAgent.h"
//#include "Agent/CameraAgent.h"
bool f = true;
void Line(Vec2 start, Vec2 End, int numberOFAgents) {
    //float l = length();

    Vec2 space = End - start;
    space /= (float)numberOFAgents;
    const auto& plane = terrain->get_terrain_plane();
    for (int i = 0; i <numberOFAgents; i++) {
        //std::string name = "d";
        
      
        //agents->create_behavior_agent("D", (BehaviorTreeTypes)1);
        Vec3 PosPos = ((float)start.x+space.x*i, (float)start.y+space.y*i,plane);
        const auto pos = renderer->screen_to_world((int)PosPos.x, (int)PosPos.y, plane);
        //agents->get_all_agents_by_type("D")[i]->set_position(pos.first);
        
    }
    


}
void L_FormD::on_enter()
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
    //if (f==true) {
    //    Line(Vec2(0,30), Vec2(0,1000), 10);
    //    f = false;
    //}
   

    BehaviorNode::on_leaf_enter();




}
//#define SDF_FONT_ARC(cx, cy, r, t0, t1) \
//  {                                                                       \
//    float s = sign(t1 - t0);                                              \
//    float l = r * 2.0 * M_PI * abs(t1 - t0);                              \
//    float ll = min(state - stroke, l);                                    \
//    float tt = ll / (r * 2.0 * M_PI);                                     \
//    if (tt > 0.0) {                                                       \
//      ud = min(ud, Sdf_arc((p - vec2(cx, cy)) / r, t0, t0 + s * tt) * r); \
//    }                                                                     \
//    stroke += l;                                                          \
//  }



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
    agentPos->set_movement_speed(10);
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
    for (auto a : agents->get_all_agents_by_type("D")) {

        a->set_scaling(2);
        a->set_movement_speed(1);
        BehaviorAgent* temp = (BehaviorAgent*)a;
        
        Position = terrain->get_world_position(grid);
        temp->move_toward_point(Position,fixedDt);
        //Position.z += 500;
        grid.row++;

    }
    grid.col =agentGrid.col+1;
    grid.row = agentGrid.row;



    for (int i = 0; i < agents->get_all_agents_by_type("DC").size(); i++) {
        agents->get_all_agents_by_type("DC")[i]->set_scaling(2);
        agents->get_all_agents_by_type("DC")[i]->set_movement_speed(1);
        BehaviorAgent* temp = (BehaviorAgent*)agents->get_all_agents_by_type("DC")[i];
        
        if (i<2) {
            Position2 = terrain->get_world_position(grid);
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
            temp->move_toward_point(Position2, fixedDt);
            grid.col++;
        }
        else if(i<4){
            grid.row++;
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
            Position2 = terrain->get_world_position(grid);
            temp->move_toward_point(Position2, fixedDt);
        }
        else if (i<6) {
            grid.col--;
            grid.row++;
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
            Position2 = terrain->get_world_position(grid);
            temp->move_toward_point(Position2, fixedDt);
        }
        else {
            grid.col--;
            //std::cout << "col" << grid.col << "row" << grid.row << std::endl;
            Position2 = terrain->get_world_position(grid);
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
