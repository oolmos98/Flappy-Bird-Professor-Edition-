//
//  Labels.hpp
//  glutapp
//
//  Created by Jefferson Santiago on 12/13/18.
//  Copyright © 2018 Angelo Kyrilov. All rights reserved.
//

#ifndef Labels_hpp
#define Labels_hpp

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <string>
#include "Rect.h"

class Labels : public Rect {
    
    std::string title;

public:
    Labels(float x, float y, float w, float h, float r, float g, float b, std::string);
    ~Labels();
    
    void setString(std::string);
    
    void draw(float);
    
};

#endif /* Labels_hpp */
