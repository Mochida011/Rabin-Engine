#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

void ProjectOne::setup()
{
    // Create your inital agents
    //agents->create_behavior_agent("ExampleAgenteg1", BehaviorTreeTypes::Example);
    agents->create_behavior_agent("DVDAgent", BehaviorTreeTypes::BouncingLogo);
    
    for (int i = 0; i < 3; i++) {
        agents->create_behavior_agent("Giants", BehaviorTreeTypes::Giants);
    }
    for (int i = 0; i < 5; i ++) {
        agents->create_behavior_agent("D", BehaviorTreeTypes::DpositionTree);
    }
    
    for (int i = 0; i < 7; i++) {
        agents->create_behavior_agent("DC", BehaviorTreeTypes::DpositionTree);
    }

    for (int i = 0; i < 5; i++) {
        agents->create_behavior_agent("D2", BehaviorTreeTypes::DpositionTree);
    }

    for (int i = 0; i < 7; i++) {
        agents->create_behavior_agent("DC2", BehaviorTreeTypes::DpositionTree);
    }

    for (int i = 0; i < 7; i++) {
        agents->create_behavior_agent("V", BehaviorTreeTypes::FormV);
    }
    for (int i = 0; i < 50; i++) {
        agents->create_behavior_agent("Ring", BehaviorTreeTypes::Ring);
    }
    // you can technically load any map you want, even create your own map file,
    // but behavior agents won't actually avoid walls or anything special, unless you code that yourself
    // that's the realm of project 2 though
    terrain->goto_map(0);

    // you can also enable the pathing layer and set grid square colors as you see fit
    // works best with map 0, the completely blank map
    terrain->pathLayer.set_enabled(true);
    terrain->pathLayer.set_value(0, 0, Colors::Red);
    

    // camera position can be modified from this default as well
    auto camera = agents->get_camera_agent();
    camera->set_position(Vec3(-62.0f, 70.0f, terrain->mapSizeInWorld * 0.5f));
    camera->set_pitch(0.610865); // 35 degrees

    audioManager->SetVolume(0.5f);
    //audioManager->PlaySoundEffect(L"Assets\\Audio\\thump.wav");
    audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
    // uncomment for example on playing music in the engine (must be .wav)
    audioManager->PlayMusic(L"Assets\\Audio\\motivate.wav");
    // audioManager->PauseMusic(...);
    // audioManager->ResumeMusic(...);
    // audioManager->StopMusic(...);
}