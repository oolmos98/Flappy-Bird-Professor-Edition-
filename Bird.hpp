//
//  Bird.hpp
//  glutapp
//
//  Created by Jefferson Santiago on 12/4/18.
//  Copyright © 2018 Angelo Kyrilov. All rights reserved.
//

#ifndef Bird_hpp
#define Bird_hpp

#include <iostream>
#include "TexRect.h"
#include <vector>
#include "Physics.hpp"
#include <tuple>
#include <utility>


class Bird : public Physics {
    
    TexRect* bird;
    float lift = 0.0005;
    
public:
    Bird(const char* texture);
    ~Bird();
    
    void move();
    void Jump();
    void draw();
    float getX() const;
    float getY() const;
    std::tuple<std::pair<float, float>, std::pair<float, float>, std::pair<float, float> , std::pair<float, float>> vertices();
    virtual void Fall();
};

#endif /* Bird_hpp */
