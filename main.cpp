#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "Ball.h"
#include <math.h>
#include "defines.h"

void DrawSettings();

int main(int argc, char **argv){



    //Setup (init) start
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    if(!al_init() or !al_init_primitives_addon() or !al_install_mouse())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

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
    srand(time(NULL));
    //Setup (init) end

    //Create the Balls
    std::vector<Ball> Balls;
    for (int i=0;i<100;i++) {
        float radius=(rand()%10000/1000.+3.)/1.;
        float placementx=rand()%SIZEX;
        float placementy=rand()%SIZEY;
        Ball tmpball(placementx,placementy,radius);
        bool overlap=false;
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
    std::cout << Balls.size() << std::endl;
    for(int i=0;i<Balls.size();i++) Balls[i].setSpeed((rand()%1000/1000.)*1);
    ALLEGRO_EVENT ev;

    //Balls created

    bool ShowSettings=true;

    //Main loop
    while(true) {
        while (!al_is_event_queue_empty(event_queue)) {
            al_get_next_event(event_queue,&ev);
            if (ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE) return 0;
        }
        al_clear_to_color(al_map_rgb(0,0,0));

        for(int i=0;i<Balls.size();i++) Balls[i].CalcAttraction(Balls);
        for(int i=0;i<5;i++) {
        for(int i=0;i<Balls.size();i++) Balls[i].MakeStep();
        for(int i=0;i<Balls.size();i++) Balls[i].CollisionDetect(Balls); }
        for(int i=0;i<Balls.size();i++) Balls[i].Draw();

        if(ShowSettings) {
            DrawSettings();



        }

        al_flip_display();
    }
    al_destroy_display(display);

    return 0;
}

void DrawSettings() {

    //Draw settings box
    //al_draw_line(SIZEX*0.2,0,SIZEX*0.2,SIZEY*0.2,al_map_rgb(0,0,255),2);




}
