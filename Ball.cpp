#include "Ball.h"

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
    ColChecked=false;
}
void Ball::Draw()
{
    al_draw_filled_circle(placement.x*zoomScale-xOffSet*zoomScale,placement.y*zoomScale-yOffSet*zoomScale,radius*zoomScale,al_map_rgb(color[0],color[1],color[2]));

}
bool Ball::HasCheckedCol() { return ColChecked;}
void Ball::setId(int identi)
{
    id=identi;
}
int Ball::CollisionDetect(Ball &Ball2)
{
    ColChecked=true;
    if (!(placement.x + radius + Ball2.radius >= Ball2.placement.x
    && placement.x <= Ball2.placement.x + radius + Ball2.radius
    && placement.y + radius + Ball2.radius >= Ball2.placement.y
    && placement.y <= Ball2.placement.y + radius + Ball2.radius)) return -1;
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
            return Ball2.getId();
        }
    }
    return -1;
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

                color[0]=(color[0]*radius*radius+CurBall.radius*CurBall.radius*CurBall.color[0])/(radius*radius+CurBall.radius*CurBall.radius)+.1;
                color[1]=(color[1]*radius*radius+CurBall.radius*CurBall.radius*CurBall.color[1])/(radius*radius+CurBall.radius*CurBall.radius)+.1;
                color[2]=(color[2]*radius*radius+CurBall.radius*CurBall.radius*CurBall.color[2])/(radius*radius+CurBall.radius*CurBall.radius)+.1;
                float newradius=sqrt(radius*radius+CurBall.radius*CurBall.radius);

                //Make New Ball
                direction.x=(direction.x*radius+CurBall.direction.x*CurBall.radius)/(radius+CurBall.radius);
                direction.y=(direction.y*radius+CurBall.direction.y*CurBall.radius)/(radius+CurBall.radius);
                radius=newradius;
                placement=collision;
                //std::cout << abs(&Balls[0]-&CurBall) << std::endl;
                Balls.erase(Balls.begin()+abs(&Balls[0]-&CurBall));
                setId(MaxId(Balls)+1);

            }
        }
    }
}


int Ball::getId() 
{
    return id;
}

void Ball::CalcAttractions(QuadTree &qTree) 
{
        std::vector<GravBody> Bodies;
        
        qTree.GetGravityBodies(Bodies,*this);
        //std::cout << Bodies.size() << std::endl;
        for (auto &body : Bodies) 
        {
            //std::cout << body.x << "  " << body.y << "  " <<body.radius << std::endl;
            float distance=sqrt((placement.x-body.x)*(placement.x-body.x)+(placement.y-body.y)*(placement.y-body.y));
            if (distance<0.0001) distance=0.0001;
            float AttractionForce=GRAVITY*(body.radius*body.radius)*radius*radius/(pow(distance,1.1));
            vektor AtractVek;
            AtractVek.x=body.x-placement.x;
            AtractVek.y=body.y-placement.y;
            AtractVek=unitvektor(AtractVek);
            vektor ForceVek;
            ForceVek.x=AtractVek.x*AttractionForce;
            ForceVek.y=AtractVek.y*AttractionForce;
            direction.x+=ForceVek.x/(radius*radius);
            direction.y+=ForceVek.y/(radius*radius);
        }

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

QuadTree::QuadTree(int pLevel, TreeRectangle pBounds)
{
    level=pLevel;
    bounds=pBounds;
    nodes.clear();
    nodes.reserve(4);
    objects.clear();
    objects.reserve(10);
}
QuadTree::~QuadTree()
{
}

void QuadTree::clear()
{
    objects.clear();
    for(auto &node : nodes)
    {
        node.clear();
    }
}
void QuadTree::split()
{
    float subWidth=bounds.width/2.;
    float subHeight=bounds.height/2.;
    TreeRectangle Rnode0={bounds.x+subWidth,bounds.y,subWidth,subHeight};
    TreeRectangle Rnode1={bounds.x,bounds.y,subWidth,subHeight};
    TreeRectangle Rnode2{bounds.x,bounds.y+subHeight,subWidth,subHeight};
    TreeRectangle Rnode3={bounds.x+subWidth,bounds.y+subHeight,subWidth,subHeight};
    QuadTree n0(level+1,Rnode0);
    QuadTree n1(level+1,Rnode1);
    QuadTree n2(level+1,Rnode2);
    QuadTree n3(level+1,Rnode3);
    nodes.push_back(n0);
    nodes.push_back(n1);
    nodes.push_back(n2);
    nodes.push_back(n3);
}
void QuadTree::SetBounds(TreeRectangle Rec)
{
    bounds=Rec;
}
int QuadTree::getIndex(Ball &ThisBall)
{
    int index=-1;
    float verticalMidpoint=bounds.x+bounds.width/2.;
    float horizontalMidpoint=bounds.y+bounds.height/2.;
    float ballx=ThisBall.placement.x-ThisBall.radius;
    float bally=ThisBall.placement.y-ThisBall.radius;
    bool topQuadrant=(bally<horizontalMidpoint && bally+ThisBall.radius*2 < horizontalMidpoint);
    bool bottomQuadrant = (bally > horizontalMidpoint);
    
    if(ballx < verticalMidpoint && ballx+ThisBall.radius*2 < verticalMidpoint)
    {
        if (topQuadrant)
        {
            index=1;
        }
        else if(bottomQuadrant)
        {
            index=2;
        }  
    }
    else if (ballx>verticalMidpoint)
    {
        if (topQuadrant)
        {
            index=0;
        }
        else if(bottomQuadrant)
        {
            index=3;
        }  
    }
    return index;
}
void QuadTree::insert(Ball ThisBall)
{
    if (nodes.size())
    {
        int index=getIndex(ThisBall);
        if (index!=-1)
        {
            nodes[index].insert(ThisBall);
            return;
        } 
    }
    objects.push_back(ThisBall);
    
    if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
    {
        if (!(nodes.size()))  split();
        for (int i=0;i<objects.size();)
        {
            int index=getIndex(objects[i]);
            if(index!=-1)
            {
                nodes[index].insert(objects[i]);
                objects.erase(objects.begin()+i);
            }
            else i++;      
        }
    }
}
void QuadTree::retrieve(std::vector<Ball> &returnBalls,Ball &ThisBall)
{
    int index=getIndex(ThisBall);
    if(index != -1 and nodes.size()) 
    {
        nodes[index].retrieve(returnBalls,ThisBall);
        return;
    }
    for (int i=0;i<objects.size();i++) returnBalls.push_back(objects[i]);
    for(int i=0;i<nodes.size();i++) nodes[i].retrieve(returnBalls,ThisBall);
    return;
         
}
void QuadTree::Draw()
{
    
    for(int i=0;i<nodes.size() ;i++) nodes[i].Draw();
    al_draw_rectangle(bounds.x*zoomScale-xOffSet*zoomScale,bounds.y*zoomScale-yOffSet*zoomScale,(bounds.x+bounds.width)*zoomScale-xOffSet*zoomScale,(bounds.y+bounds.height)*zoomScale-yOffSet*zoomScale,al_map_rgb(255,0,255),(5-level/2.));
    al_draw_filled_circle(getCenterOfMass().x*zoomScale-xOffSet*zoomScale,getCenterOfMass().y*zoomScale-yOffSet*zoomScale,(3-level/2.),al_map_rgb(255,0,255));
    //std::cout << objects.size() << "\n";


}
vektor QuadTree::getCenterOfMass()
{
    if (CenterOfMass.y==-999999999)
    {   if (getGravityRadius())
        {
            vektor CoM={0,0};
            if(nodes.size())
            {
                for(auto &node : nodes)  CoM.x+=node.getCenterOfMass().x*node.getGravityRadius()*node.getGravityRadius();
                for(auto &node : nodes)  CoM.y+=node.getCenterOfMass().y*node.getGravityRadius()*node.getGravityRadius();
            }
            CoM.x+=BallGetCenterOfMass(objects).x*GetTotalRadius(objects)*GetTotalRadius(objects);
            CoM.y+=BallGetCenterOfMass(objects).y*GetTotalRadius(objects)*GetTotalRadius(objects);
            //std::cout << "jj" << GetTotalRadius(objects) << std::endl;
            //std::cout << "jjs" << objects.size() << std::endl;
            CenterOfMass.x=CoM.x/(getGravityRadius()*getGravityRadius());
            CenterOfMass.y=CoM.y/(getGravityRadius()*getGravityRadius());
        }
        
    }
    return CenterOfMass;    
}
float QuadTree::getGravityRadius()
{
    if (gravityRadius==-1)
    {
        float totalmass=0;
        if(nodes.size())
        {
            for(auto &node :nodes) totalmass+=node.getGravityRadius()*node.getGravityRadius();
        }
       for (auto &object:objects) totalmass+=object.radius*object.radius;
       gravityRadius=sqrt(totalmass);
       
    }
    return gravityRadius;
}
void  QuadTree::GetGravityBodies(std::vector<GravBody> &rBodies, Ball &ThisBall)
{
    if (nodes.size())
    {
        int index=getIndex(ThisBall);
        for (int i=0;i<nodes.size();i++)
        {
            if (i!=index)
            {
                float distancex=abs(nodes[i].getCenterOfMass().x-ThisBall.placement.x);
                float distancey=abs(nodes[i].getCenterOfMass().y-ThisBall.placement.y);
                if (sqrt(distancex*distancex+distancey*distancey)<nodes[i].getGravityRadius())
                {
                    nodes[i].GetGravityBodies(rBodies,ThisBall);
                }
                else
                {
                    GravBody tmpbody={getCenterOfMass().x,getCenterOfMass().y,getGravityRadius()};
                    rBodies.push_back(tmpbody);
                }   
            }
            else nodes[i].GetGravityBodies(rBodies,ThisBall);
        }
    }
    for (auto &object :objects)
    {
        GravBody tmpbody={object.placement.x,object.placement.y,object.radius};
        
    }
}
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
        tmpball.setId(MaxId(Balls)+1);
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

vektor BallGetCenterOfMass(std::vector<Ball> &Balls) 
{
    using namespace std;
    float totalmass=0;
    vektor CoM={0,0};
    if (Balls.size())
    {
        for(auto &CurBall :Balls) 
        {
            totalmass+=CurBall.radius*CurBall.radius;
            CoM.x+=CurBall.placement.x*CurBall.radius*CurBall.radius;
            CoM.y+=CurBall.placement.y*CurBall.radius*CurBall.radius;
        }
        CoM.x/=totalmass;
        CoM.y/=totalmass;
    }
    return CoM;
}
float GetTotalRadius(std::vector<Ball> &Balls) 
{
    float totalmass=0;
    for(auto &ThisBall: Balls) totalmass+=ThisBall.radius*ThisBall.radius;
    return sqrt(totalmass);
}



