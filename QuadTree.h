#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "Ball.h"
#include "globals.h"
typedef struct {

    float x;
    float y;
    float width;
    float height;
} TreeRectangle;

class QuadTree
{
    private:
        int MAX_OBJECTS=20;
        int MAX_LEVELS=15;
        int level;
        std::vector<Ball> objects;
        std::vector<QuadTree> nodes;
        TreeRectangle bounds;
    
    public:
        QuadTree(int pLevel, TreeRectangle pBounds);
        void clear();
        void split();
        int getIndex(Ball &ThisBall);
        void insert(Ball ThisBall);
        void retrieve(std::vector<Ball> &returnBalls,Ball &ThisBall);
        ~QuadTree();
        void Draw();
        
};
