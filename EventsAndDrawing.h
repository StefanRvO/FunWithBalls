#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include<iostream>
#include<vector>
#include <cstdlib>
#include "globals.h"
#include "Ball.h"
#include "BallFunctions.h"
#include "QuadTree.h"
#define SETTINGSSIZEX 0.2f
#define SETTINGSSIZEY 0.45f
void DrawSettings(ALLEGRO_FONT *font);
void HandleEvent(ALLEGRO_EVENT &ev,std::vector<Ball> &Balls);
void HandleNoEventMouse(std::vector<Ball> &Balls);
void VariousDraw(ALLEGRO_FONT *font,std::vector<Ball> &Balls,QuadTree &qtree);
