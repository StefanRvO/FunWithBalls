#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED
#include <allegro5/allegro.h>
#include <vector>
typedef struct{
    float x;
    float y;
    } vektor;


class Ball {


public:
    Ball(float x,float y);
    Ball(float x,float y,float radi);
    Ball(float x,float y,int r,int g,int b);
    Ball(float x,float y,int r,int g,int b,float radi);
    ~Ball();
    void setSpeed(float speed);
    void setDirection(float x, float y);
    void Draw();
    void MakeStep();
    void setId(int);
    int getId();
    void CollisionDetect(std::vector<Ball>&);
    vektor placement;
    vektor direction;
    float radius;
    int color[3];
    void CalcAttraction(std::vector<Ball> &Balls);


private:
    vektor unitvektor(vektor);
    int id;
};


#endif // BALL_H_INCLUDED
