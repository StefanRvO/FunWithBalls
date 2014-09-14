#pragma once
#include <vector>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <iostream>
#include "globals.h"
typedef struct 
{

    double x;
    double y;
    double width;
    double height;
} TreeRectangle;
typedef struct 
{
    double x;
    double y;
    double radius;
    } GravBody;
typedef struct
{
    double x;
    double y;
} vektor;

class QuadTree;
class Ball;


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
        int CollisionDetect(Ball &Ball2);
        vektor placement;
        vektor direction;
        float radius;
        int color[3];
        void CalcAttractions(QuadTree &qTree);
        void CalculateSingleAttraction(vektor Atrpos,double atrmass);
        float getSpeed();
        void DoDecay();
        bool DoCheckUnspawn();
        void CollisionDetect(std::vector<Ball> &Balls );
        void CalcAttractions(std::vector<Ball> &Balls);
        bool HasCheckedCol();



    private:
        vektor unitvektor(vektor);
        int id;
        bool ColChecked=false;
};

class QuadTree
{
    private:
        int MAX_OBJECTS=5;
        int MAX_LEVELS=15;
        int level;
        std::vector<Ball> objects;
        std::vector<QuadTree> nodes;
        TreeRectangle bounds;
        vektor CenterOfMass={-99999999,-999999999};
        float gravityRadius=-1;
    
    public:
        QuadTree(int pLevel, TreeRectangle pBounds);
        void clear();
        void split();
        int getIndex(Ball &ThisBall);
        void insert(Ball ThisBall);
        void retrieve(std::vector<Ball> &returnBalls,Ball &ThisBall);
        ~QuadTree();
        void Draw();
        vektor getCenterOfMass();
        float getGravityRadius();
        void GetGravityBodies(std::vector<GravBody> &rBodies,Ball &ThisBall);
        void SetBounds(TreeRectangle);
        
};
void SpawnBall(std::vector<Ball> &Balls);
int MaxId(std::vector<Ball> &Balls);
int MaxId(std::vector<Ball*> &Balls);
void SpawnBall(std::vector<Ball> &Balls,float x,float y,float radius,float dirx, float diry);
vektor BallGetCenterOfMass(std::vector<Ball> &Balls);
void IdFix(std::vector<Ball> &Balls);
bool IdCompare(Ball &Ball1,Ball &Ball2);
float GetTotalRadius(std::vector<Ball> &Balls) ;
