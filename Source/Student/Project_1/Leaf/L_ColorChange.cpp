#include <pch.h>
#include "L_ColorChange.h"
#include "L_AgentW.h"
#include "../Agent/BehaviorAgent.h"
bool stop; 
void K_ColorChange::on_enter()
{

    const auto leftMouseState = InputHandler::get_current_state(MouseButtons::LEFT);

    if (leftMouseState == InputHandler::InputState::PRESSED)
    {
        
        //agents->set_color(Colors::SpringGreen);
        /*Color red =Color(255,255,255);*/
        
        // grab the current mouse pos
        //const auto& mousePos = InputHandler::get_mouse_position();

        // we want to know where on the ground the mouse was clicked
        //const auto& plane = terrain->get_terrain_plane();

        
        // find out where on the plane the click happened
        //const auto worldPos = renderer->screen_to_world(mousePos.x, mousePos.y, plane);

        // if the click point was actually on the plane

    }
    //std::cout << m_color.x << "," << m_color.y << "," << m_color.z << std::endl;
    m_color = Vec3(1.0, 0.04, 0.04);

    agent->set_color(m_color);
    check = 1;

    //on_success();
    BehaviorNode::on_leaf_enter();
    
    //display_leaf_text();
}
void K_ColorChange::on_update(float dt) {
   
    if (check == 1) {
        if (m_color.x >= 0.04f && m_color.z == 0.04f && m_color.y <=1.0f ) {

            m_color.x-=0.01f;
            m_color.y+=0.01f;
        }
        else {

             m_color.x = 0.04f; m_color.y = 1.0f; m_color.z = 0.04f;
            check = 2;
        }
    }
    else if (check == 2) {
        if (m_color.x == 0.04f && m_color.z <= 1.0f && m_color.y >= 0.04f) {
            m_color.y-=0.01f;
            m_color.z+=0.01f;
        }
        else {
            m_color.x = 0.04f; m_color.y = 0.04f; m_color.z = 1.0f;
            check = 3;
        }
    }
    else if (check == 3) {
        if (m_color.y == 0.04f && m_color.z >= 0.04f && m_color.x <= 1.f) {
            m_color.z-=0.01f;
            m_color.x+=0.01f;
        }
        else {
            m_color.z = 0.04f; m_color.x = 1.0f; m_color.y = 0.04f; check = 1;
        }
    }
    //std::cout << m_color.x<<"," << m_color.y << "," << m_color.z<<"update" << std::endl;

    //if (agent->get_blackboard().get_value<int>("color")==0) {
        
    //}
    //else {
    //    
    //}
    if (stop) {
        
    }
    else {
        agent->set_color(4*(m_color));
    }
   

    display_leaf_text();

}