#include "QuadTree.h"

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
    al_draw_rectangle(bounds.x*zoomScale-xOffSet*zoomScale,bounds.y*zoomScale-yOffSet*zoomScale,(bounds.x+bounds.width)*zoomScale-xOffSet*zoomScale,(bounds.y+bounds.height)*zoomScale-yOffSet*zoomScale,al_map_rgb(0,0,255),(3l)*zoomScale);
    //std::cout << objects.size() << "\n";


}
