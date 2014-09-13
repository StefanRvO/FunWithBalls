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
    if (isnan(direction.x)) direction.x=0;
    if (isnan(direction.y)) direction.y=0;
    if (isnan(placement.x)) placement.x=0;
    if (isnan(placement.y)) placement.y=0;
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
void Ball::CollisionDetect(Ball &Ball2,std::vector<Ball> &Balls)
{
    if (!(placement.x + radius + Ball2.radius >= Ball2.placement.x
    && placement.x <= Ball2.placement.x + radius + Ball2.radius
    && placement.y + radius + Ball2.radius >= Ball2.placement.y
    && placement.y <= Ball2.placement.y + radius + Ball2.radius)) return;
    //Real test
    if (sqrt((placement.x-Ball2.placement.x)*(placement.x-Ball2.placement.x)+(placement.y-Ball2.placement.y)*(placement.y-Ball2.placement.y))<=(radius+Ball2.radius)) {
        //std::cout << "collision" << std::endl;
        if (!CollisionMerge)
        {
            //Calculate new directions
            float x=(direction.x*(radius-Ball2.radius)+(2*Ball2.radius*Ball2.direction.x))/(radius+Ball2.radius);
            float y=(direction.y*(radius-Ball2.radius)+(2*Ball2.radius*Ball2.direction.y))/(radius+Ball2.radius);
            float x2=(Ball2.direction.x*(Ball2.radius-radius)+(2*radius*direction.x))/(radius+Ball2.radius);
            float y2=(Ball2.direction.y*(Ball2.radius-radius)+(2*radius*direction.y))/(radius+Ball2.radius);
            Ball2.setDirection(x2,y2);
            setDirection(x,y);
            Ball2.MakeStep();
            MakeStep();
        }
        else
        {
            //Calculate collision point
            vektor collision;
            collision.x=(placement.x*radius+Ball2.placement.x*Ball2.radius)/(Ball2.radius+radius);
            collision.y=(placement.y*radius+Ball2.placement.y*Ball2.radius)/(Ball2.radius+radius);
            color[0]=(color[0]*radius*radius+Ball2.radius*Ball2.radius*Ball2.color[0])/(radius*radius+Ball2.radius*Ball2.radius)+.1;
            color[1]=(color[1]*radius*radius+Ball2.radius*Ball2.radius*Ball2.color[1])/(radius*radius+Ball2.radius*Ball2.radius)+.1;
            color[2]=(color[2]*radius*radius+Ball2.radius*Ball2.radius*Ball2.color[2])/(radius*radius+Ball2.radius*Ball2.radius)+.1;
            float newradius=sqrt(radius*radius+Ball2.radius*Ball2.radius);
            //Make New Ball
            direction.x=(direction.x*radius+Ball2.direction.x*Ball2.radius)/(radius+Ball2.radius);
            direction.y=(direction.y*radius+Ball2.direction.y*Ball2.radius)/(radius+Ball2.radius);
            radius=newradius;
            placement=collision;
            //std::cout << abs(&Balls[0]-&Ball2) << std::endl;
            Balls.erase(Balls.begin()+abs(&Balls[0]-&Ball2));
            setId(MaxId(Balls)+1);
            IdFix(Balls);
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
        if (distance<0.0001) distance=0.0001;
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
    if (distance<0.0001) distance=0.0001;
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



