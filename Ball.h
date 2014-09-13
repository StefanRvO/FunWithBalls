#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED
#include <allegro5/allegro.h>
#include <vector>
typedef struct
{
    double x;
    double y;
} vektor;


class Ball {


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
    void CollisionDetect(std::vector<Ball>&);
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


#endif // BALL_H_INCLUDED
