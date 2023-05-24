#include <pch.h>
#include "L_CollisionWall.h"
#include "Agent/BehaviorAgent.h"
//#include "Agent/CameraAgent.h"



void L_CollisionWall::on_update(float dt)
{
    // grab the current mouse pos
    const auto& mousePos = InputHandler::get_mouse_position();
    GridPos grid;
    grid.col = 10;
    grid.row = 10;

    
    Position = terrain->get_world_position(grid);
    // we want to know where on the ground the mouse was clicked
    const auto& plane = terrain->get_terrain_plane();
    grid.col = 0; grid.row = 20;
    const auto& positionCornerBL = terrain->get_world_position(grid);
    grid.row = 0; 
    const auto& positionCornerTL = terrain->get_world_position(grid);

    grid.col = 20; grid.row = 20;
    const auto& positionCornerBR = terrain->get_world_position(grid);
    grid.row = 0;
    const auto& positionCornerTR = terrain->get_world_position(grid);
    
    if (AABB(agent->get_position(),positionCornerTL,positionCornerTR, positionCornerBR,positionCornerBL)) {
        on_success();
    }
    else {
        on_failure();
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
