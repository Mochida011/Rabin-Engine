#include <pch.h>
#include "L_FlipCam.h"

void L_FlipCam::on_enter()
{
	auto camera = agents->get_camera_agent();
	camera->set_position(Vec3(40.0f, 130.0f, terrain->mapSizeInWorld * 0.6f));
	camera->set_pitch(1.56); // 35 degrees
	BehaviorNode::on_leaf_enter();
	on_success();
}