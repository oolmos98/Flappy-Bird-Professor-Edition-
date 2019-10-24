//
//  Physics.cpp
//  glutapp
//
//  Created by Jefferson Santiago on 12/6/18.
//  Copyright © 2018 Angelo Kyrilov. All rights reserved.
//

#include "Physics.hpp"


const float Physics::gravity = -0.0000005;


float Physics::velocity_y(float v0, int time)
{
    return v0 + (gravity * time);
}

Physics::Physics()
{
    velYo = 0;
}
Physics::~Physics()
{
}

std::tuple<float> Physics::jump(float initVel, float y, int time)
{

    float posY = 0;

    velYo = initVel;

    posY = velocity_y(velYo, time);

    return std::make_tuple(posY);
}
