#include "Ball.h"
#include<stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include<iostream>
#include "globals.h"

Ball::Ball(float x,float y) {
    placement.x=x;
    placement.y=y;
    direction.x=(rand()%20000)/10000.-1;
    direction.y=(rand()%20000)/10000.-1;
    direction=unitvektor(direction);
    for(int i=0;i<3;i++) color[i]=rand()%256;
    radius=5;

}
Ball::Ball(float x,float y,float radi) {
    placement.x=x;
    placement.y=y;
    direction.x=(rand()%20000)/10000.-1;
    direction.y=(rand()%20000)/10000.-1;
    direction=unitvektor(direction);
    for(int i=0;i<3;i++) color[i]=rand()%256;
    radius=radi;

}
Ball::Ball(float x,float y,int r,int g,int b) {
    placement.x=x;
    placement.y=y;
    direction.x=(rand()%20000)/10000.-1;
    direction.y=(rand()%20000)/10000.-1;
    direction=unitvektor(direction);
    color[0]=r; color[1]=g; color[2]=b;
    radius=5;
}
Ball::Ball(float x,float y,int r,int g,int b,float radi) {
    placement.x=x;
    placement.y=y;
    direction.x=(rand()%20000)/10000.-1;
    direction.y=(rand()%20000)/10000.-1;
    direction=unitvektor(direction);
    color[0]=r; color[1]=g; color[2]=b;
    radius=radi;
}

Ball::~Ball() {
}
vektor Ball::unitvektor(vektor v) {
    vektor v2;
    v2.x=v.x/sqrt(v.x*v.x+v.y*v.y);
    v2.y=v.y/sqrt(v.x*v.x+v.y*v.y);
    return v2;
}
void Ball::setSpeed(double speed) {
    direction=unitvektor(direction);
    direction.x*=speed;
    direction.y*=speed;
}

float Ball::getSpeed() {
    return direction.x/unitvektor(direction).x;
}

void Ball::setDirection(double x, double y)
{
    direction.x=x;
    direction.y=y;
}
void Ball::MakeStep()
{
    placement.x+=direction.x;
    placement.y+=direction.y;
    if (BoxBounce)
    {
        if (placement.x+radius>SIZEX and direction.x>0)  direction.x=-direction.x;
        if (placement.x-radius<0 and direction.x<0) direction.x=-direction.x;
        if (placement.y+radius>SIZEY and direction.y>0)  direction.y=-direction.y;
        if (placement.y-radius<0 and direction.y<0) direction.y=-direction.y;
    }
    if (Eviscosity)
    {
        float visforce=viscosity*radius*sqrt(direction.x*direction.x+direction.y*direction.y)/50.;
        float visacc=visforce/(radius*radius);
        vektor forcedir;
        forcedir=unitvektor(direction);
        direction.x-=forcedir.x*visacc;
        direction.y-=forcedir.y*visacc;
    }
}
void Ball::Draw()
{
    al_draw_filled_circle(placement.x,placement.y,radius,al_map_rgb(color[0],color[1],color[2]));

}
void Ball::setId(int identi)
{
    id=identi;
}
void Ball::CollisionDetect(std::vector<Ball> &Balls )
{
    for(auto &CurBall : Balls) {
        if (CurBall.getId()==id) continue;
        //Test for proximity before real test
        if (!(placement.x + radius + CurBall.radius >= CurBall.placement.x
        && placement.x <= CurBall.placement.x + radius + CurBall.radius
        && placement.y + radius + CurBall.radius >= CurBall.placement.y
        && placement.y <= CurBall.placement.y + radius + CurBall.radius)) continue;

        //Real test
        if (sqrt((placement.x-CurBall.placement.x)*(placement.x-CurBall.placement.x)+(placement.y-CurBall.placement.y)*(placement.y-CurBall.placement.y))<=(radius+CurBall.radius)) {
            //std::cout << "collision" << std::endl;

            if (!CollisionMerge)
            {
                //Calculate new directions
                float x=(direction.x*(radius-CurBall.radius)+(2*CurBall.radius*CurBall.direction.x))/(radius+CurBall.radius);
                float y=(direction.y*(radius-CurBall.radius)+(2*CurBall.radius*CurBall.direction.y))/(radius+CurBall.radius);
                float x2=(CurBall.direction.x*(CurBall.radius-radius)+(2*radius*direction.x))/(radius+CurBall.radius);
                float y2=(CurBall.direction.y*(CurBall.radius-radius)+(2*radius*direction.y))/(radius+CurBall.radius);
                CurBall.setDirection(x2,y2);
                setDirection(x,y);
                CurBall.MakeStep();
                MakeStep();
            }
            else
            {
                //Calculate collision point
                vektor collision;
                collision.x=(placement.x*CurBall.radius*CurBall.radius+CurBall.placement.x*radius*radius)/(CurBall.radius*CurBall.radius+radius*radius);
                collision.y=(placement.y*CurBall.radius*CurBall.radius+CurBall.placement.y*radius*radius)/(CurBall.radius*CurBall.radius+radius*radius);
                int newcolor[3];
                newcolor[0]=color[0]*radius+CurBall.radius*color[0]/(radius+CurBall.radius);
                newcolor[1]=color[1]*radius+CurBall.radius*color[1]/(radius+CurBall.radius);
                newcolor[2]=color[2]*radius+CurBall.radius*color[2]/(radius+CurBall.radius);
                float newradius=sqrt(radius*radius+CurBall.radius*CurBall.radius);

                //Make New Ball
                direction.x=(direction.x*radius+CurBall.direction.x*CurBall.radius)/(radius+CurBall.radius);
                direction.y=(direction.y*radius+CurBall.direction.y*CurBall.radius)/(radius+CurBall.radius);
                setId(Balls[Balls.size()-1].getId()+1);
                radius=newradius;
                *color=*newcolor;
                placement=collision;
                //std::cout << abs(&Balls[0]-&CurBall) << std::endl;
                Balls.erase(Balls.begin()+abs(&Balls[0]-&CurBall));

            }
        }
    }
}


int Ball::getId() {
    return id;
}

void Ball::CalcAttraction(std::vector<Ball> &Balls) {
    for(auto &CurBall : Balls) {
        if (CurBall.getId()==id) continue;
        float distance=sqrt((placement.x-CurBall.placement.x)*(placement.x-CurBall.placement.x)+(placement.y-CurBall.placement.y)*(placement.y-CurBall.placement.y));
        float AttractionForce=GRAVITY*(CurBall.radius*CurBall.radius)*radius*radius/distance;
        vektor AtractVek;
        AtractVek.x=CurBall.placement.x-placement.x;
        AtractVek.y=CurBall.placement.y-placement.y;
        AtractVek=unitvektor(AtractVek);
        vektor ForceVek;
        ForceVek.x=AtractVek.x*AttractionForce;
        ForceVek.y=AtractVek.y*AttractionForce;
        direction.x+=ForceVek.x/radius;
        direction.y+=ForceVek.y/radius;



    }


}
void Ball::DoDecay() {
    radius=pow(pow(radius,4)*1./Bdecay,1./4);
}
bool Ball::DoCheckUnspawn()
{
    if (radius<decaylimit) return false;
    return true;
}



