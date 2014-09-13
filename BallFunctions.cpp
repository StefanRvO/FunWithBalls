#include "BallFunctions.h"

void IdFix(std::vector<Ball> &Balls) //Sort the Id's and reassign them to start at 0 and increment 1 per ball
{
    for(int i=0;i<Balls.size(); i++) Balls[i].setId(i);
    return;

}

void SpawnBall(std::vector<Ball> &Balls)
{   int count=0;
    for (int i=0;i<1;i++) 
    {
        count++;
        float radius=(rand()%10000/1000.+3.)/1.;
        float placementx=rand()%SIZEX/zoomScale+xOffSet;
        float placementy=rand()%SIZEY/zoomScale+yOffSet;
        Ball tmpball(placementx,placementy,radius);
        bool overlap=false;
        for(int j=0;j<Balls.size();j++) 
        {
            if (sqrt((tmpball.placement.x-Balls[j].placement.x)*(tmpball.placement.x-Balls[j].placement.x)+(tmpball.placement.y-Balls[j].placement.y)*(tmpball.placement.y-Balls[j].placement.y))<=(tmpball.radius+Balls[j].radius)) 
            {
                overlap=true;
                if (count>1000*1) {overlap=false; tmpball.placement.x+=SIZEX;}
                break;
            }
        }
        if (overlap) { i--; continue;}
        tmpball.setId(Balls[Balls.size()-1].getId()+1);
        tmpball.setSpeed(1);
        Balls.push_back(tmpball);
    }
}

void SpawnBall(std::vector<Ball> &Balls,float x,float y,float radius,float dirx,float diry)
{ 
    for (int i=0;i<1;i++) 
    {
        float placementx=x;
        float placementy=y;
        Ball tmpball(placementx,placementy,radius);
        tmpball.setId(MaxId(Balls)+1);
        tmpball.setDirection(dirx,diry);
        Balls.push_back(tmpball);
    }
}
int MaxId(std::vector<Ball> &Balls) 
{
    int max=0;
    for (auto &CurBall : Balls) 
        {
            if (CurBall.getId()>max) max=CurBall.getId();
        }
    return max;
}
int MaxId(std::vector<Ball*> &Balls) 
{
    int max=0;
    for (auto &CurBall : Balls) 
        {
            if (CurBall->getId()>max) max=CurBall->getId();
        }
    return max;
}
vektor BallGetCenterOfMass(std::vector<Ball> &Balls) 
    {
    float totalmass=0;
    vektor CoM={0,0};
    for(auto &CurBall :Balls) 
    {
        totalmass+=CurBall.radius*CurBall.radius;
        CoM.x+=CurBall.placement.x*CurBall.radius*CurBall.radius;
        CoM.y+=CurBall.placement.y*CurBall.radius*CurBall.radius;
    }
    CoM.x/=totalmass;
    CoM.y/=totalmass;
    return CoM;
}

