#include <pch.h>
#include "L_Downsize.h"

void L_Downsize::on_enter()
{

	
	if (agent->get_scaling().x>1) {
		float scale = agent->get_scaling().x;
		scale -= 1.f;
		agent->set_scaling(scale);
		std::cout << "shrink" << std::endl;
	}
	BehaviorNode::on_leaf_enter();
	on_success();
}