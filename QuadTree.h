#pragma once
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "Ball.h"
#include "globals.h"
#include "BallFunctions.h"
typedef struct {

    float x;
    float y;
    float width;
    float height;
} TreeRectangle;

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
};
