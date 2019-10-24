#include "App.h"

int main(int argc, char** argv) {
    GlutApp* app = new App(argc, argv);
    //glutFullScreen();
    app->run();
}
