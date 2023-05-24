#include <pch.h>
#include "L_PlaySound.h"

void L_PlaySound::on_enter()
{
	
	audioManager->SetVolume(0.2f);
	audioManager->PlaySoundEffect(L"Assets\\Audio\\boing.wav");

	BehaviorNode::on_leaf_enter();
	on_success();
}