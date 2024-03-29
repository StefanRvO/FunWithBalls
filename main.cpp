#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "Ball.h"
#include "globals.h"
#include "EventsAndDrawing.h"

int main(int argc, char **argv){



    //Setup (init) start
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    if(!al_init() or !al_init_primitives_addon() or !al_install_mouse())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    al_install_keyboard();
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(SIZEX, SIZEY);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    event_queue = al_create_event_queue();
    if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      }
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_init_font_addon();
    al_init_ttf_addon();

    srand(time(NULL));
    //Setup (init) end
    
    //Create the Balls
    std::vector<Ball> Balls;
    for (int i=0;i<20;i++) {
        float radius=(rand()%10000/1000.+3.)/1.;
        float placementx=rand()%SIZEX;
        float placementy=rand()%SIZEY;
        Ball tmpball(placementx,placementy,radius);
        bool overlap=false;
        //The Balls spawned should not overlap other balls
        for(int j=0;j<Balls.size();j++) {
            if (sqrt((tmpball.placement.x-Balls[j].placement.x)*(tmpball.placement.x-Balls[j].placement.x)+(tmpball.placement.y-Balls[j].placement.y)*(tmpball.placement.y-Balls[j].placement.y))<=(tmpball.radius+Balls[j].radius)) {
                overlap=true;
                break;
            }
        }
        if (overlap) { i--; continue;}
        
        tmpball.setId(i);
        Balls.push_back(tmpball);
    }
    ALLEGRO_EVENT ev;

    //Balls created


    //Main loop
    TreeRectangle QTRect={0,0,0,0};
    QuadTree qTree(0,QTRect);
    float spawnprogress=0;
    while(true)
    {
        ALLEGRO_FONT *font =al_load_ttf_font("FreeSans.ttf",SIZEX/90,0);
        /*for(int i=0;i<Balls.size();i++) std::cout << Balls[i].placement.x << "\n";
        std::cout << "\n"; */
        //std::cout << Balls.size() << std::endl;
        if (Espawn)
        {
            spawnprogress+=spawnrate;
            while(spawnprogress>1)
            {
                spawnprogress-=1.;
                SpawnBall(Balls);
            }
        }
        while (!al_is_event_queue_empty(event_queue)) {
            al_get_next_event(event_queue,&ev);
            HandleEvent(ev,Balls,display);
        }
        HandleNoEventMouse(Balls);
        al_clear_to_color(al_map_rgb(0,0,0));

        for(int i=0;i<Balls.size();i++) Balls[i].MakeStep();
        float maxX=-99999999999999;
        float minX=999999999999999;
        float minY=999999999999999;
        float maxY=-99999999999999;
        for(int i=0;i<Balls.size();i++)
        {
            if (Balls[i].placement.x+Balls[i].radius>maxX) maxX=Balls[i].placement.x+Balls[i].radius;
            if (Balls[i].placement.x-Balls[i].radius<minX) minX=Balls[i].placement.x-Balls[i].radius;
            if (Balls[i].placement.y+Balls[i].radius>maxY) maxY=Balls[i].placement.y+Balls[i].radius;
            if (Balls[i].placement.y-Balls[i].radius<minY) minY=Balls[i].placement.y-Balls[i].radius;
        }
        IdFix(Balls);
        TreeRectangle QTRect={minX,minY,maxX-minX,maxY-minY};
        QuadTree qTree(0,QTRect);
        qTree.clear();
        for(auto ThisBall : Balls) qTree.insert(ThisBall);
        
        if (ShowQuadTree) qTree.Draw();
        if (Collision and !PresCol) {
            bool checkdone=false;
            while(!checkdone)
            {
                checkdone=true;
                IdFix(Balls);
                for(int i=0;i<Balls.size();i++)
                {
                    if (Balls[i].HasCheckedCol()) continue;
                    std::vector<Ball> rtBalls;
                    rtBalls.clear();
                    rtBalls.reserve(10);
                    qTree.retrieve(rtBalls,Balls[i]);
                    for(int k=0;k<rtBalls.size();k++)
                    {
                        if (Balls[i].getId()==rtBalls[k].getId()) continue;
                        int rtBall=Balls[i].CollisionDetect(Balls[rtBalls[k].getId()]);
                        if (rtBall!=-1) 
                        {
                            Balls.erase(Balls.begin()+rtBalls[k].getId());
                            checkdone=false;
                            break;
                        }
                    }
                    if (!checkdone) break;
                }
            }
        }
        else if (Collision and PresCol)
        {
            for(int i=0;i<Balls.size();i++) Balls[i].CollisionDetect(Balls);
        
        }
        if (Egravity and !PresGrav) {
            for(int i=0;i<Balls.size();i++) Balls[i].CalcAttractions(qTree);
        }
        else if (Egravity and PresGrav) {
            for(int i=0;i<Balls.size();i++) Balls[i].CalcAttractions(Balls);
        }
        if (Edecay) for(int i=0;i<Balls.size();i++) Balls[i].DoDecay();
        if (Edecaylimit and Balls.size()) for(int i=0;i<Balls.size();i++) if(!Balls[i].DoCheckUnspawn()) Balls.erase(Balls.begin()+i);
        for(int i=0;i<Balls.size();i++) if(Balls[i].radius*zoomScale>0.1) Balls[i].Draw();
        
        VariousDraw(font,Balls,qTree);
        if(ShowSettings) {
            DrawSettings(font);
        }
        al_flip_display();
        al_destroy_font(font);
    }
    al_destroy_display(display);

    return 0;
}


