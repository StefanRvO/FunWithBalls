#ifndef DEFINES_H_BALLFUNCTIONS
#define DEFINES_H_BALLFUNCTIONS

#include<vector>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include "Ball.h"
#include"globals.h"
void SpawnBall(std::vector<Ball> &Balls);
int MaxId(std::vector<Ball> &Balls);
int MaxId(std::vector<Ball*> &Balls);
void SpawnBall(std::vector<Ball> &Balls,float x,float y,float radius,float dirx, float diry);
vektor BallGetCenterOfMass(std::vector<Ball> &Balls);
void IdFix(std::vector<Ball> &Balls);
bool IdCompare(Ball &Ball1,Ball &Ball2);
class Ball;
#endif
