#include <pch.h>
#include "L_Upsize.h"

void L_Upsize::on_enter()
{
	if (agent->get_scaling().x < 12) {
		float scale = agent->get_scaling().x;
		scale += 1.f;
		agent->set_scaling(scale);
		//std::cout << "shrink" << std::endl;
	}
	else {
		on_failure();
	}
	BehaviorNode::on_leaf_enter();
	on_success();
	display_leaf_text();
}