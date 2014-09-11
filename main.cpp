#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "Ball.h"
#include <math.h>
#include "globals.h"

void DrawSettings();
void HandleEvent(ALLEGRO_EVENT &ev);
int main(int argc, char **argv){



    //Setup (init) start
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    al_init_font_addon();
    al_init_ttf_addon();
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


    //Main loop
    while(true) {
        while (!al_is_event_queue_empty(event_queue)) {
            al_get_next_event(event_queue,&ev);
            HandleEvent(ev);
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        if (Egravity) {
        for(int i=0;i<Balls.size();i++) Balls[i].CalcAttraction(Balls);
        }
        for(int i=0;i<5;i++) {
            for(int i=0;i<Balls.size();i++) Balls[i].MakeStep();
            if (Collision) for(int i=0;i<Balls.size();i++) Balls[i].CollisionDetect(Balls);
        }

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
    //Make font
    ALLEGRO_FONT *font =al_load_ttf_font("FreeSans.ttf",SIZEX/100,0);
    //Draw settings box
    al_draw_line(SIZEX*0.2,0,SIZEX*0.2,SIZEY*0.2,al_map_rgb(0,0,255),2);
    al_draw_line(SIZEX*0.2,SIZEY*0.2,0,SIZEY*0.2,al_map_rgb(0,0,255),2);
    al_draw_text(font, al_map_rgb(0,0,255), 0, 0,ALLEGRO_ALIGN_LEFT, "Settings");
    //Gravity
    al_draw_line(SIZEX*0.2,SIZEY*0.03,0,SIZEY*0.03,al_map_rgb(0,0,255),2);
    if (Egravity) al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.035,ALLEGRO_ALIGN_LEFT, "Gravity: %.3f",GRAVITY);
    else al_draw_textf(font, al_map_rgb(50,50,50), 0, SIZEY*0.035,ALLEGRO_ALIGN_LEFT, "Gravity: %.3f",GRAVITY);
    al_draw_line(SIZEX*0.19,SIZEY*0.048,SIZEX*0.07,SIZEY*0.048,al_map_rgb(0,0,255),2);
    float GravityContX=(GRAVITY+0.5)/1.*0.12+0.07; //Incomplete/correct
    al_draw_filled_circle(SIZEX*GravityContX,SIZEY*0.048,SIZEX*0.005,al_map_rgb(0,0,255));
    //BoxBounce
    al_draw_line(SIZEX*0.2,SIZEY*0.065,0,SIZEY*0.065,al_map_rgb(0,0,255),2);
    al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.07,ALLEGRO_ALIGN_LEFT, "Bounce on Edges: ");
    if (BoxBounce) al_draw_filled_rectangle(SIZEX*0.09,SIZEY*0.075,SIZEX*0.10,SIZEY*0.09,al_map_rgb(0,0,255));
    else al_draw_rectangle(SIZEX*0.09,SIZEY*0.075,SIZEX*0.10,SIZEY*0.09,al_map_rgb(0,0,255),1);

    //Collision
    al_draw_line(SIZEX*0.2,SIZEY*0.1,0,SIZEY*0.1,al_map_rgb(0,0,255),2);
    al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.105,ALLEGRO_ALIGN_LEFT, "Collision: ");
    if (Collision) al_draw_filled_rectangle(SIZEX*0.05,SIZEY*0.11,SIZEX*0.06,SIZEY*0.125,al_map_rgb(0,0,255));
    else al_draw_rectangle(SIZEX*0.05,SIZEY*0.11,SIZEX*0.06,SIZEY*0.125,al_map_rgb(0,0,255),1);


    al_destroy_font(font);

}


void HandleEvent(ALLEGRO_EVENT &event) {

    if (event.type==ALLEGRO_EVENT_DISPLAY_CLOSE) std::exit(0);
    if (event.type==ALLEGRO_EVENT_KEY_DOWN) { //Keyboard event
        if (event.keyboard.keycode==ALLEGRO_KEY_S) ShowSettings=!ShowSettings;

    }
    if (event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) { //Mouse Event
            if (ShowSettings) {
        if (event.mouse.x>SIZEX*0.09  and event.mouse.x<SIZEX*0.10 and event.mouse.y>SIZEY*0.075 and event.mouse.y<SIZEY*0.09) BoxBounce=!BoxBounce;
        else if (event.mouse.x>SIZEX*0.05  and event.mouse.x<SIZEX*0.06 and event.mouse.y>SIZEY*0.11 and event.mouse.y<SIZEY*0.125) Collision=!Collision;
        else if (event.mouse.x>SIZEX*0.0  and event.mouse.x<SIZEX*0.07 and event.mouse.y>SIZEY*0.04 and event.mouse.y<SIZEY*0.06) Egravity=!Egravity;
        else if (event.mouse.x>SIZEX*0.07  and event.mouse.x<SIZEX*0.2 and event.mouse.y>SIZEY*0.04 and event.mouse.y<SIZEY*0.06) {
                Egravity=true;
                 float relx= (float)event.mouse.x/SIZEX;
                relx-=0.07;
                relx*=1;
                relx/=0.12;
                relx-=0.5;
                GRAVITY=relx;
        }


            }
    }


    }

