#include<vector>
#include<cstdlib>
#include<algorithm>
#include "Ball.h"
#include"globals.h"
#include<cmath>
void SpawnBall(std::vector<Ball> &Balls);
int MaxId(std::vector<Ball> &Balls);
int MaxId(std::vector<Ball*> &Balls);
void SpawnBall(std::vector<Ball> &Balls,float x,float y,float radius,float dirx, float diry);
vektor BallGetCenterOfMass(std::vector<Ball> &Balls);
void IdFix(std::vector<Ball> &Balls);
bool IdCompare(Ball &Ball1,Ball &Ball2);
