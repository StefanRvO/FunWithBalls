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
#include "BallFunctions.h"
#include "QuadTree.h"


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
    ALLEGRO_FONT *font =al_load_ttf_font("FreeSans.ttf",SIZEX/90,0);
    float spawnprogress=0;
    while(true)
    {
        //Balls.reserve(Balls.size()+10);
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
            HandleEvent(ev,Balls);
        }
        HandleNoEventMouse(Balls);
        al_clear_to_color(al_map_rgb(0,0,0));
        if (Egravity) {
            for(int i=0;i<Balls.size();i++) Balls[i].CalcAttractions(Balls);
        }
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
        TreeRectangle QTRect={minX,minY,maxX-minX,maxY-minY};
        QuadTree qTree(0,QTRect);
        for(auto ThisBall : Balls) qTree.insert(ThisBall);
        qTree.Draw();
        if (Collision) {
            for(int i=0;i<Balls.size();i++)
            {
                std::vector<Ball> rtBalls;
                qTree.retrieve(rtBalls,Balls[i]);
                Balls[i].CollisionDetect(rtBalls);
            }
        }
        if (Edecay) for(int i=0;i<Balls.size();i++) Balls[i].DoDecay();
        if (Edecaylimit and Balls.size()) for(int i=0;i<Balls.size();i++) if(!Balls[i].DoCheckUnspawn()) Balls.erase(Balls.begin()+i);
        for(int i=0;i<Balls.size();i++) if(Balls[i].radius*zoomScale>0.1) Balls[i].Draw();
        al_draw_textf(font, al_map_rgb(0,0,255), SIZEX*0.91, 0,ALLEGRO_ALIGN_LEFT, "Balls: %d",Balls.size());
        al_draw_textf(font, al_map_rgb(0,0,255), SIZEX*0.91, SIZEY*0.03,ALLEGRO_ALIGN_LEFT, "zoomScale: %.4f",zoomScale);
        al_draw_textf(font, al_map_rgb(0,0,255), SIZEX*0.91, SIZEY*0.06,ALLEGRO_ALIGN_LEFT, "xOffSet %.1f",xOffSet);
        al_draw_textf(font, al_map_rgb(0,0,255), SIZEX*0.91, SIZEY*0.09,ALLEGRO_ALIGN_LEFT, "yOffSet %.1f",yOffSet);

        if(ShowSettings) {
            DrawSettings(font);
        }
        al_flip_display();
    }
    al_destroy_display(display);

    return 0;
}


