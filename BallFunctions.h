#include<vector>
#include<cstdlib>
#include "Ball.h"
#include"globals.h"
#include<cmath>
void SpawnBall(std::vector<Ball> &Balls);
int MaxId(std::vector<Ball> &Balls);
void SpawnBall(std::vector<Ball> &Balls,float x,float y,float radius,float dirx, float diry);
