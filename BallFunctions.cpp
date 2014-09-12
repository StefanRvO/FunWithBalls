#include "BallFunctions.h"
void SpawnBall(std::vector<Ball> &Balls)
{   int count=0;
    for (int i=0;i<1;i++) 
    {
        count++;
        float radius=(rand()%10000/1000.+3.)/1.;
        float placementx=rand()%SIZEX;
        float placementy=rand()%SIZEY;
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
    for (Ball &CurBall : Balls) 
        {
            if (CurBall.getId()>max) max=CurBall.getId();
        }
    return max;
}

