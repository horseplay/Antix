#include "Game/Home.h"
#include "GUI/Color.h"
#include "Game/Robot.h"

void initGraphics(int argc, char **argv);
void idleFunc();
void timerFunc(int dummy);
void displayFunc();
void drawPucks();
void drawTeams();
void drawRobot(Game::Robot* robot, const GUI::Color* color);
void drawHome(Game::Home* home, const GUI::Color* color);
void mousFunc(int button, int state, int x, int y);
void idleFunc();
