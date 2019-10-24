//
//  Environment.hpp
//  glutapp
//
//  Created by Omar Olmos on 12/3/18.
//  Copyright © 2018 Angelo Kyrilov. All rights reserved.
//

#ifndef Environment_hpp
#define Environment_hpp

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include "TexRect.h"
#include <deque>
#include <random>
#include "Timer.h"
#include <thread>

class Environment {
    
public:
    std::deque<TexRect*> topPipes;
    std::deque<TexRect*> bottomPipes;
    
    float pipe_offset;
    const char* pipe_image1;
    const char* pipe_image2;
    int amount;
    float rate;
    float speed;
    
    Environment();
    Environment(int, const char*, const char*, float, float, float);
    
    void buildPipes();
    void addPipe();
    
    void resetPipes(TexRect* rect, float height);
    
    void move();
    void drawPipes();
    float generateHeight(float, float);
    
    ~Environment();
    
};
#endif /* Environment_hpp */
