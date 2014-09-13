#include <allegro5/allegro.h>
#include<cstdlib>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include<iostream>
#include <vector>
#include "QuadTree.h"
#include "globals.h"
#include "BallFunctions.h"
#ifndef vektorstruct
#define vektorstruct
typedef struct
{
    double x;
    double y;
} vektor;
#endif


class Ball 
{


public:
    Ball(float x,float y);
    Ball(float x,float y,float radi);
    Ball(float x,float y,int r,int g,int b);
    Ball(float x,float y,int r,int g,int b,float radi);
    ~Ball();
    void setSpeed(double speed);
    void setDirection(double x, double y);
    void Draw();
    void MakeStep();
    void setId(int);
    int getId();
    void CollisionDetect(Ball &Ball2,std::vector<Ball> &Balls);
    vektor placement;
    vektor direction;
    float radius;
    int color[3];
    void CalcAttractions(std::vector<Ball> &Balls);
    void CalculateSingleAttraction(vektor Atrpos,double atrmass);
    float getSpeed();
    void DoDecay();
    bool DoCheckUnspawn();



private:
    vektor unitvektor(vektor);
    int id;
};
