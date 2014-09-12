#include<cstdlib>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include<iostream>
#include "Ball.h"
#include "globals.h"
#include "BallFunctions.h"

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
    if (BoxBounce)
    {
        if (placement.x+radius>SIZEX/zoomScale+xOffSet and direction.x>0)  direction.x=-direction.x;
        if (placement.x-radius<+xOffSet and direction.x<0) direction.x=-direction.x;
        if (placement.y+radius>SIZEY/zoomScale+yOffSet and direction.y>0)  direction.y=-direction.y;
        if (placement.y-radius<+yOffSet and direction.y<0) direction.y=-direction.y;
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
    if (direction.x==NAN or direction.x==-NAN) direction.x=0;
    if (direction.y==NAN or direction.y==-NAN) direction.y=0;
    if (placement.x==NAN or placement.x==-NAN) placement.x=0;
    if (placement.y==NAN or placement.y==-NAN) placement.y=0;
    placement.x+=direction.x;
    placement.y+=direction.y;
}
void Ball::Draw()
{
    al_draw_filled_circle(placement.x*zoomScale-xOffSet*zoomScale,placement.y*zoomScale-yOffSet*zoomScale,radius*zoomScale,al_map_rgb(color[0],color[1],color[2]));

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
                collision.x=(placement.x*radius+CurBall.placement.x*CurBall.radius)/(CurBall.radius+radius);
                collision.y=(placement.y*radius+CurBall.placement.y*CurBall.radius)/(CurBall.radius+radius);
                int newcolor[3];
                newcolor[0]=color[0]*radius+CurBall.radius*color[0]/(radius+CurBall.radius);
                newcolor[1]=color[1]*radius+CurBall.radius*color[1]/(radius+CurBall.radius);
                newcolor[2]=color[2]*radius+CurBall.radius*color[2]/(radius+CurBall.radius);
                float newradius=sqrt(radius*radius+CurBall.radius*CurBall.radius);

                //Make New Ball
                direction.x=(direction.x*radius+CurBall.direction.x*CurBall.radius)/(radius+CurBall.radius);
                direction.y=(direction.y*radius+CurBall.direction.y*CurBall.radius)/(radius+CurBall.radius);
                radius=newradius;
                *color=*newcolor;
                placement=collision;
                //std::cout << abs(&Balls[0]-&CurBall) << std::endl;
                Balls.erase(Balls.begin()+abs(&Balls[0]-&CurBall));
                setId(MaxId(Balls)+1);

            }
        }
    }
}


int Ball::getId() {
    return id;
}

void Ball::CalcAttractions(std::vector<Ball> &Balls) {
    for(auto &CurBall : Balls) {
        if (CurBall.getId()==id) continue;
        float distance=sqrt((placement.x-CurBall.placement.x)*(placement.x-CurBall.placement.x)+(placement.y-CurBall.placement.y)*(placement.y-CurBall.placement.y));
        float AttractionForce=GRAVITY*(CurBall.radius*CurBall.radius)*radius*radius/(pow(distance,1.1));
        vektor AtractVek;
        AtractVek.x=CurBall.placement.x-placement.x;
        AtractVek.y=CurBall.placement.y-placement.y;
        AtractVek=unitvektor(AtractVek);
        vektor ForceVek;
        ForceVek.x=AtractVek.x*AttractionForce;
        ForceVek.y=AtractVek.y*AttractionForce;
        direction.x+=ForceVek.x/(radius*radius);
        direction.y+=ForceVek.y/(radius*radius);



    }


}
void Ball::CalculateSingleAttraction(vektor Atrpos,double atrmass)
{
    float distance=sqrt((placement.x-Atrpos.x)*(placement.x-Atrpos.x)+(placement.y-Atrpos.y)*(placement.y-Atrpos.y));
    float AttractionForce;
    if (atrmass>0) AttractionForce=1*(atrmass*atrmass)*radius*radius/(pow(distance,1.1));
    else AttractionForce=-1*(atrmass*atrmass)*radius*radius/(pow(distance,1.1));
    if (abs(AttractionForce)>1000) 
    {
        if (AttractionForce>0) AttractionForce=1000;
        else AttractionForce=-1000;
    }
    vektor AtractVek;
    AtractVek.x=Atrpos.x-placement.x;
    AtractVek.y=Atrpos.y-placement.y;
    AtractVek=unitvektor(AtractVek);
    vektor ForceVek;
    ForceVek.x=AtractVek.x*AttractionForce;
    ForceVek.y=AtractVek.y*AttractionForce;
    direction.x+=ForceVek.x/(radius*radius);
    direction.y+=ForceVek.y/(radius*radius);

}
void Ball::DoDecay() {
    radius=pow(pow(radius,4)*1./Bdecay,1./4);
}
bool Ball::DoCheckUnspawn()
{
    if (radius<decaylimit) return false;
    return true;
}



