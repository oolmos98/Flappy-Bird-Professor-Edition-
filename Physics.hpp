//
//  Physics.hpp
//  glutapp
//
//  Created by Jefferson Santiago on 12/6/18.
//  Copyright © 2018 Angelo Kyrilov. All rights reserved.
//

#ifndef Physics_hpp
#define Physics_hpp

#include <tuple>

class Physics {
protected:

    static const float gravity;
    float velYo; // Initial Y Velocity
    float velocity_y(float v0, int time);
    
  public:
    Physics();
    ~Physics();

    std::tuple<float> jump(float v0, float y, int time);
 
};
#endif /* Physics_hpp */

/*
 
 Add this to the idle func
 void App::idle() {
 int time = 0;
 for(int i = 0 ; i < myRectangles.size() ; i++) {
 if(myRectangles[i]->isSelected()) {
 float posY = myRectangles[i]->getY();
 float newPosY = 0;
 //
 //            while(time < 5) {
 //
 //                if((myRectangles[i]->getY() - myRectangles[i]->getHeight()) > -1.0 && (myRectangles[i]->getY()) < 1.0) {
 //                    std::cout << "Test 1" << std::endl;
 //                    std::tie(newPosY) = (myRectangles[i]->jump(-0.0005,posY, time));
 //                    newPosY += newPosY;
 //                    std::cout << newPosY << std::endl;
 //                    myRectangles[i]->setY(myRectangles[i]->getY() - newPosY);
 //                    time++;
 //                }
 //                else {
 //                    break;
 //                }
 //            }
 //
 time = 0;
 float vel = 0.5;
 newPosY = 0;
 
 while(time < 5) {
 
 if((myRectangles[i]->getY() - myRectangles[i]->getHeight()) > -1.0) {
 std::cout << "Test 1" << std::endl;
 std::tie(newPosY) = (myRectangles[i]->jump(vel,posY, time));
 vel -= newPosY;
 std::cout << newPosY << std::endl;
 myRectangles[i]->setY(myRectangles[i]->getY() - vel);
 time++;
 }
 else {
 break;
 }
 }
 
 }
 }
 redraw();
 }
 
 
 
 */
