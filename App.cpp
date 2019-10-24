#include <iostream>
#include "App.h"

//Amount of Pipes
int App::amount = 2;

//Rate at whihc the pipes move
float App::rate = 0.0005;

//
float App::speed = 0.00000001;

//Spacing for the pipes
float App::tube_gap = 2.0;

#if defined WIN32
const char* App::pipeFile1 = "pipe1.png";
const char* App::pipeFile2 = "pipe2.png";
const char* App::background = "back.png";
const char* App::miguel = "../images/Miguel.png";
const char* App::daniel = "../images/Daniel.png";
const char* App::dongli = "../images/DongLi.png";
const char* App::angelo = "../images/Angelo.png";
const char* App::bird1 = "../images/MLGflappyb.png";
const char* App::bird2 = "../images/flappybirdOG.png";

#elif defined __APPLE__
const char* App::pipeFile1 = "pipe1.png";
const char* App::pipeFile2 = "pipe2.png";
const char* App::background = "back.png";
const char* App::miguel = "images/Miguel.png";
const char* App::daniel = "images/Daniel.png";
const char* App::dongli = "images/DongLi.png";
const char* App::angelo = "images/Angelo.png";
const char* App::bird1 = "images/MLGflappyb.png";
const char* App::bird2 = "images/flappybirdOG.png";

#else
const char* App::pipeFile1 = "pipe1.png";
const char* App::pipeFile2 = "pipe2.png";
const char* App::background = "back.png";
const char* App::miguel = "../images/Miguel.png";
const char* App::daniel = "../images/Daniel.png";
const char* App::dongli = "../images/DongLi.png";
const char* App::angelo = "../images/Angelo.png";
const char* App::bird1 = "../images/MLGflappyb.png";
const char* App::bird2 = "../images/flappybirdOG.png";
#endif

App::App(int argc, char** argv): GlutApp(argc, argv){
    gameStarted = false;
    gameEnded = true;
    CSEVersion = false;
    menu.push_back(new Labels(-0.4, 0.5, 0.8, 0.2, 0.5, 1.0, 0.5, "Choose Your Mode"));
    menu.push_back(new Labels(-0.4, 0.2, 0.8, 0.2, 1.0, 1.0, 1.0, "Default"));
    menu.push_back(new Labels(-0.4, -0.1, 0.8, 0.2, 0.5, 0.5, 1.0, "CSE Version"));
    score = 0;
    title = NULL;
    scoreBoard = NULL;
    explosion = NULL;
    back = new TexRect(background, -1.0, 1.0, 2.0, 2.0);

    
}

void App::draw() {
    
    back->draw(-0.1);

    if(gameStarted == false && gameEnded ) {
        if(title != NULL) title->draw(0.0);
        for (int i = 0; i < menu.size(); i++) {
            menu[i]->draw(0.0);
        }
        
        for (int i = 0; i < characterMenu.size(); i++) {
            characterMenu[i]->draw(0.0);
        }
    }
    
    if(gameStarted) {
        
        //
        if(!gameEnded) game->move();
        
        
        game->drawPipes();
        // Draw the pipes
        // Draw the Background
        if(scoreBoard != NULL) {
            scoreBoard->setString("Score: " + std::to_string(score));
            scoreBoard->draw(0.2);
        }
        if(!gameEnded) bird->draw();

    }
    
    for(int i = 0 ; i < endmenu.size() ; i++) {
        endmenu[i]->draw(0.2);
    }
    
    if(explosion != NULL) explosion->draw(0.2);
    redraw();
}

void App::createCharacterMenu() {
    for (int i = 0; i < menu.size(); i++) {
        delete menu[i];
    }
    menu.clear();
    
    if(CSEVersion == false ){
        title = new Labels(-0.8, 0.5, 1.6, 0.2, 1.0, 1.0, 1.0, "Choose Your Character!");
        characterMenu.push_back(new TexRect(bird1, -0.8, 0, 0.4,0.4));
        characterMenu.push_back(new TexRect(bird2, -0.3, 0, 0.4,0.4));
    }
    else {
        title = new Labels(-0.8, 0.5, 1.6, 0.2, 1.0, 1.0, 1.0, "Choose Your Professor!");
        characterMenu.push_back(new TexRect(miguel, -0.9, 0, 0.3,0.3));
        characterMenu.push_back(new TexRect(daniel, -0.5, 0, 0.5,0.5));
        characterMenu.push_back(new TexRect(dongli, 0.0, 0, 0.4,0.4));
        characterMenu.push_back(new TexRect(angelo, 0.5, 0, 0.4,0.4));
    }
    
}

void App::StartGame(const char* character) {
    for (int i = 0; i < characterMenu.size(); i++) {
        delete characterMenu[i];
    }
    characterMenu.clear();
    
    delete title;
    bird = new Bird(character);
    game = new Environment(amount, pipeFile2, pipeFile1, tube_gap, rate, speed);
    scoreBoard = new Labels(-0.7, 0.98, 0.4, 0.1, 1.0, 0.5, 0.5, "Score: 0");
    gameEnded = false;

}

void App::keyDown(unsigned char key, float x, float y){
    
    if (key == 27){
        exit(0);
    }
    if(gameStarted){
        if (key == ' '){
            bird->Jump();
           // redraw();
        }
    }
}
        

void App::idle()
{
    if(gameStarted && !gameEnded) {
        bird->move();
        
        std::pair<float, float> topLeft;
        std::pair<float, float> topRight;
        std::pair<float, float> botRight;
        std::pair<float, float> botLeft;
        
        std::tie(topLeft, topRight, botLeft, botRight) = bird->vertices();
        
        if(botLeft.second > 1.0 || botLeft.second < -1.0) {
            explosion = new AnimatedRect("nuclearExplosion.png", 5, 5, 50, topLeft.first - 0.1, topLeft.second + 0.27, 0.5, 0.5);
            endGame();
        }
        
        
        if(checkCollisions() == true) {
            explosion = new AnimatedRect("nuclearExplosion.png", 5, 5, 50, topLeft.first - 0.1, topLeft.second  + 0.27, 0.5, 0.5);
            endGame();
        }

        for (int i = 0; i < game->bottomPipes.size(); i++) {
            if(bird->getX() >= game->bottomPipes[i]->getCenterX() && !game->bottomPipes[i]->isPassed()) {
                addScore();
                game->bottomPipes[i]->setPassed(true);
            }
        }
    }

}


bool App::checkCollisions() {
    std::pair<float, float> topLeft;
    std::pair<float, float> topRight;
    std::pair<float, float> botRight;
    std::pair<float, float> botLeft;
    for (int i = 0; i < game->bottomPipes.size(); i++) {
        
        std::tie(topLeft, topRight, botLeft, botRight) = bird->vertices();
        //std::cout << topLeft.second << std::endl;
        // Bottom Pipes
        if(game->bottomPipes[i]->contains(topLeft.first, topLeft.second)) {
            std::cout << "Test 1" << std::endl;
            return true;
        }
        if(game->bottomPipes[i]->contains(topRight.first, topRight.second)) {
            std::cout << "Test 2" << std::endl;
            return true;
        }
        if(game->bottomPipes[i]->contains(botRight.first, botRight.second)) {
            std::cout << "Test 3" << std::endl;
            return true;
        }
        if(game->bottomPipes[i]->contains(botLeft.first, botLeft.second)) {
            std::cout << "Test 4" << std::endl;
            return true;
        }
    }
    
    for (int i = 0; i < game->topPipes.size(); i++) {
        std::tie(topLeft, topRight, botLeft, botRight) = bird->vertices();
        // Top Pipes
        if(game->topPipes[i]->contains(topLeft.first, topLeft.second)) {
            std::cout << "Test 5" << std::endl;
            return true;
        }
        if(game->topPipes[i]->contains(topRight.first, topRight.second)) {
            std::cout << "Test 6" << std::endl;
            return true;
        }
        if(game->topPipes[i]->contains(botRight.first, botRight.second)) {
            std::cout << "Test 7" << std::endl;
            return true;
        }
        if(game->topPipes[i]->contains(botLeft.first, botLeft.second)) {
            std::cout << "Test 8" << std::endl;
            return true;
        }
    }
    return false;
}

int App::getScore() const {
    return score;
}

void App::addScore() {
    score++;
}

void App::leftMouseDown(float x, float y) {
    
    if(gameStarted == false) {
        for (int i = 0; i < characterMenu.size(); i++) {
            if(characterMenu[i]->contains(x, y)) {
                gameStarted = true;
                StartGame(characterMenu[i]->getFile());
            }
        }
        
        if(!menu.empty()) {
            if(menu[1]->contains(x, y)) {
                std::cout << "Test 1" << std::endl;
                createCharacterMenu();
            }
            if(menu[2]->contains(x, y)) {
                std::cout << "Test 2" << std::endl;
                CSEVersion = true;
                createCharacterMenu();
            }
        }
    }
    else {
        for (int i = 0; i < game->bottomPipes.size(); i++) {
            if(game->bottomPipes[i]->contains(x, y)) {
                std::cout << "Test click" << std::endl;
            }
        }
    }
    
    if(gameEnded && endmenu.empty() == false) {
        if(endmenu[1]->contains(x, y)) {
            ResetGame();
        }
    }
    
    
}


void App::endGame() {
    gameEnded = true;
    std::cout << "Game Ended" << std::endl;
    explosion->playOnce();
    
    endmenu.push_back(new Labels(-0.4, 0.2, 0.8, 0.2, 1.0, 0.0, 0.0, "You Lost!"));
    endmenu.push_back(new Labels(-0.4, -0.1, 0.8, 0.2, 1.0, 1.0, 1.0, "Reset Game"));
}


void App::ResetGame() {
    
    for (int i = 0; i < endmenu.size(); i++) {
        delete endmenu[i];
    }
    endmenu.clear();
    
    gameStarted = false;
    gameEnded = true;
    CSEVersion = false;
    
    menu.push_back(new Labels(-0.4, 0.5, 0.8, 0.2, 0.5, 1.0, 0.5, "Choose Your Mode"));
    menu.push_back(new Labels(-0.4, 0.2, 0.8, 0.2, 1.0, 1.0, 1.0, "Default"));
    menu.push_back(new Labels(-0.4, -0.1, 0.8, 0.2, 0.5, 0.5, 1.0, "CSE Version"));
    
    score = 0;
    title = NULL;
    scoreBoard = NULL;
    explosion = NULL;
}

App::~App()
{
    if(gameStarted) {
        std::cout << "Exiting..." << std::endl;
        delete game;
    }
}
