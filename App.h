#ifndef App_h
#define App_h

#include "GlutApp.h"
#include <vector>
#include "AnimatedRect.h"
#include "Environment.hpp"
#include "Bird.hpp"
#include "Labels.hpp"
#include <tuple>
#include <utility>


class App: public GlutApp {
    static int amount;
    static float rate;
    static float tube_gap;
    static float speed;
    
    static const char* pipeFile1;
    static const char* pipeFile2;
    static const char* background;
    static const char* miguel;
    static const char* daniel;
    static const char* angelo;
    static const char* dongli;
    
    static const char* bird1;
    static const char* bird2;
    
    AnimatedRect* explosion;
    AnimatedRect* fastExplosion;
    Environment* game;
    TexRect* back;
    Bird* bird;
    
    std::vector<Labels*> menu;
    std::vector<Labels*> endmenu;
    Labels* title;
    Labels* scoreBoard;
    
    std::vector<TexRect*> characterMenu;
    
    bool gameStarted;
    bool CSEVersion;
    bool gameEnded;
    
    int score;

public:
    
    App(int argc, char** argv);
    
    void createCharacterMenu();
    void StartGame(const char*);
    
    void draw();
    
    void idle();
    
    int getScore() const;
    void addScore();
    
    bool checkCollisions();
    
    void endGame();
    
    void ResetGame();
    
    void keyDown(unsigned char key, float x, float y);
    
    void leftMouseDown(float, float);
    ~App();
    
};
#endif
