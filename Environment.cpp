//
//  Environment.cpp
//  glutapp
//
//  Created by Omar Olmos on 12/3/18.
//  Copyright © 2018 Angelo Kyrilov. All rights reserved.
//

#include "Environment.hpp"

//Constructors for the environment
Environment::Environment() : amount(0),pipe_offset(0.4), pipe_image1(" "), pipe_image2(" "){
    buildPipes();
    drawPipes();
}

Environment::Environment(int amount, const char* file, const char*  file2, float pipe_offset, float rate, float speed): amount(amount),  pipe_offset(pipe_offset), pipe_image1(file), pipe_image2(file2), rate(rate), speed(speed){
    buildPipes();
    drawPipes();
    
}

//Function to create pipes
void Environment::buildPipes(){
    
   // std::cout << "Building " << amount << " Top Pipes" << std::endl;
    float randomHeight = 0;
    for(int i = 0; i < amount; i++){
        //Building top pipes
        // Generate random Height for each pipes
        randomHeight = generateHeight(-0.5, 0.5);
        topPipes.push_back(new TexRect(pipe_image1, (3.0 + ((float)i*pipe_offset)), 2.0 - 0.5, 0.5, 1.6));
        bottomPipes.push_back(new TexRect(pipe_image2, (3.0 + ((float)i*pipe_offset)), -0.8, 0.5, 1.6) );
    }
}

void Environment::resetPipes(TexRect* rect, float height) {
    rect->setX(2.5);
    rect->setY(height);
    rect->setX(2.5);
    rect->setY(height);
    rect->setPassed(false);
}

void Environment::addPipe(){
    
}
//Randomize the height of the pipes
float Environment::generateHeight(float low, float high) {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(low, high);
    
    return dis(gen);
}

//Move the pipes at a set rate
void Environment::move(){
    
    //std::cout << "Moving Pipes " << std::endl;
    
    rate += speed;
    
    for(int i = 0; i < amount; i++){
        
        float x = topPipes[i]->getX();
        
        topPipes[i]->setX(x - rate);
        x = bottomPipes[i]->getX();
        
        //std::cout << bottomPipes[i]->getY() << std::endl;
        //std::cout << x << std::endl;
        
        bottomPipes[i]->setX(x - rate);
        
        //If pipe reaches end, move to end.
        if(topPipes[i]->getX() + topPipes[i]->getW() <= -1.0){
            float randomHeight = 0;
            randomHeight = generateHeight(-0.5, 0.5);
            resetPipes(topPipes[i], 2.0 - randomHeight);
            resetPipes(bottomPipes[i], (topPipes[i]->getY() - topPipes[i]->getH()) - 0.8);
        }
    }
}

//Draw pipes
void Environment::drawPipes(){
    //std::cout << "Drawing Pipes " << std::endl;
    
    for(int i = 0; i < amount; i++){
        topPipes[i]->draw(0.1);
        bottomPipes[i]->draw(0.1);
    }
}

//Destructor
Environment::~Environment(){
    std::cout << "Deleting " << amount << " Pipes" << std::endl;
    for(int i = 0; i < amount; i++){
        delete topPipes[i];
        delete bottomPipes[i];
    }
}
