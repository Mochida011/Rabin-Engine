#include <pch.h>
#include "L_ColorBlack.h"
#include "Agent/BehaviorAgent.h"
//#include "Agent/CameraAgent.h"

void L_ColorBlack::on_enter()
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
    gridd.col = 50; gridd.row = 40;

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



void L_ColorBlack::on_update(float dt)
{
    // grab the current mouse pos
    const auto& mousePos = InputHandler::get_mouse_position();
    auto agentPos = (BehaviorAgent*)agents->get_all_agents_by_type("DVDAgent")[0];
    auto agentGrid = agentPos->get_blackboard().get_value<GridPos>("targetPos");
    //errain->get_grid_position(agents->get_all_agents_by_type("DVDAgent")[0]->get_position());
    
    GridPos grid;
    grid = terrain->get_grid_position(agentPos->get_position());
    grid.col = agentGrid.col;
    grid.row = agentGrid.row;
    agentPos->set_movement_speed(9);
    agentPos->set_scaling(2);
    Position = terrain->get_world_position(grid);

    //for (int i = 0; i < gridd.row; i ++) {
    //    for (int j = 0; j < gridd.col; j++) {
    
    if (gridx<40-ring) {
        terrain->set_color(gridendy, gridx, Colors::Black);
        gridx++;
    }
    else if(gridendy>0+ring){
        gridendy--;
        terrain->set_color(gridendy, gridendx, Colors::Black);
        
    }
    else if (gridendx>0+ring) {
        terrain->set_color(gridendy, gridendx, Colors::Black);
        gridendx--;
    }
    else if (gridy<39-ring) {
        terrain->set_color(gridy, gridendx, Colors::Black);
        gridy++;
    }
    else {
        //restart
        ring++;
        gridx = 0+ring; gridy = 0+ring; gridendx = 39-ring; gridendy = 39-ring;

        
        if (ring==20) {
            on_success();
        }
        else {
            on_failure();
        }


    }

    display_leaf_text();
}
