#include "EventsAndDrawing.h"


void DrawSettings(ALLEGRO_FONT *font) { //Yeah it looks like shit.. Blame Allegro
    //Draw settings box
    al_draw_line(SIZEX*SETTINGSSIZEX,0,SIZEX*SETTINGSSIZEX,SIZEY*SETTINGSSIZEY,al_map_rgb(0,0,255),2);
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*SETTINGSSIZEY,0,SIZEY*SETTINGSSIZEY,al_map_rgb(0,0,255),2);
    al_draw_text(font, al_map_rgb(0,0,255), 0, 0,ALLEGRO_ALIGN_LEFT, "Settings");
    //Gravity
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*0.03,0,SIZEY*0.03,al_map_rgb(0,0,255),2);
    if (Egravity) al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.035,ALLEGRO_ALIGN_LEFT, "Gravity: %.3f",GRAVITY);
    else al_draw_textf(font, al_map_rgb(50,50,50), 0, SIZEY*0.035,ALLEGRO_ALIGN_LEFT, "Gravity: %.3f",GRAVITY);
    al_draw_line(SIZEX*0.19,SIZEY*0.048,SIZEX*0.07,SIZEY*0.048,al_map_rgb(0,0,255),2);
    float GravityContX=(GRAVITY+0.25)/.5*0.12+0.07; //Incomplete/correct
    al_draw_filled_circle(SIZEX*GravityContX,SIZEY*0.048,SIZEX*0.005,al_map_rgb(0,0,255));
    //BoxBounce
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*0.065,0,SIZEY*0.065,al_map_rgb(0,0,255),2);
    al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.07,ALLEGRO_ALIGN_LEFT, "Bounce on Edges: ");
    if (BoxBounce) al_draw_filled_rectangle(SIZEX*0.09,SIZEY*0.075,SIZEX*0.10,SIZEY*0.09,al_map_rgb(0,0,255));
    else al_draw_rectangle(SIZEX*0.09,SIZEY*0.075,SIZEX*0.10,SIZEY*0.09,al_map_rgb(0,0,255),1);

    //Collision
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*0.1,0,SIZEY*0.1,al_map_rgb(0,0,255),2);
    al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.105,ALLEGRO_ALIGN_LEFT, "Collision: ");
    if (Collision) al_draw_filled_rectangle(SIZEX*0.05,SIZEY*0.11,SIZEX*0.06,SIZEY*0.125,al_map_rgb(0,0,255));
    else al_draw_rectangle(SIZEX*0.05,SIZEY*0.11,SIZEX*0.06,SIZEY*0.125,al_map_rgb(0,0,255),1);
    //Viscosity
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*0.135,0,SIZEY*0.135,al_map_rgb(0,0,255),2);
    if (Eviscosity) al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.135,ALLEGRO_ALIGN_LEFT, "Viscosity: %.3f",viscosity);
    else al_draw_textf(font, al_map_rgb(50,50,50), 0, SIZEY*0.135,ALLEGRO_ALIGN_LEFT, "Viscosity: %.3f",viscosity);
    al_draw_line(SIZEX*0.19,SIZEY*0.15,SIZEX*0.08,SIZEY*0.15,al_map_rgb(0,0,255),2);
    float ViscContX=(viscosity+25)/50.*0.11+0.08; //Incomplete/correct
    al_draw_filled_circle(SIZEX*ViscContX,SIZEY*0.15,SIZEX*0.005,al_map_rgb(0,0,255));
    //Spawning
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*0.165,0,SIZEY*0.165,al_map_rgb(0,0,255),2);
    if (Espawn) al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.165,ALLEGRO_ALIGN_LEFT, "Spawnrate: %.3f",spawnrate*2);
    else al_draw_textf(font, al_map_rgb(50,50,50), 0, SIZEY*0.165,ALLEGRO_ALIGN_LEFT, "Spawnrate: %.3f",spawnrate*2);
    al_draw_line(SIZEX*0.19,SIZEY*0.18,SIZEX*0.09,SIZEY*0.18,al_map_rgb(0,0,255),2);
    float spawnContX=(spawnrate)/2.5*0.09+0.09; //Incomplete/correct
    al_draw_filled_circle(SIZEX*spawnContX,SIZEY*0.18,SIZEX*0.005,al_map_rgb(0,0,255));
    //Decay
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*0.195,0,SIZEY*0.195,al_map_rgb(0,0,255),2);
    if (Edecay) al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.195,ALLEGRO_ALIGN_LEFT, "Decay: %.3f",Bdecay);
    else al_draw_textf(font, al_map_rgb(50,50,50), 0, SIZEY*0.195,ALLEGRO_ALIGN_LEFT, "Decay: %.3f",Bdecay);
    al_draw_line(SIZEX*0.19,SIZEY*0.21,SIZEX*0.07,SIZEY*0.21,al_map_rgb(0,0,255),2);
    float DecayContX=(Bdecay-0.9)/0.2*0.12+0.07; //Incomplete/correct
    al_draw_filled_circle(SIZEX*DecayContX,SIZEY*0.21,SIZEX*0.005,al_map_rgb(0,0,255));
    //decaylimit
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*0.225,0,SIZEY*0.225,al_map_rgb(0,0,255),2);
    if (Edecaylimit) al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.225,ALLEGRO_ALIGN_LEFT, "Unspawnsize: %.3f",decaylimit);
    else al_draw_textf(font, al_map_rgb(50,50,50), 0, SIZEY*0.225,ALLEGRO_ALIGN_LEFT, "UnSpawnsize: %.3f",decaylimit);
    al_draw_line(SIZEX*0.19,SIZEY*0.24,SIZEX*0.11,SIZEY*0.24,al_map_rgb(0,0,255),2);
    float decaysContX=(decaylimit-0.01)/4.99*0.08+0.11; //Incomplete/correct
    al_draw_filled_circle(SIZEX*decaysContX,SIZEY*0.24,SIZEX*0.005,al_map_rgb(0,0,255));
    //CollisionMerge
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*0.255,0,SIZEY*0.255,al_map_rgb(0,0,255),2);
    al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.255,ALLEGRO_ALIGN_LEFT, "CollisionMerge: ");
    if (CollisionMerge) al_draw_filled_rectangle(SIZEX*0.08,SIZEY*0.262,SIZEX*0.09,SIZEY*0.275,al_map_rgb(0,0,255));
    else al_draw_rectangle(SIZEX*0.08,SIZEY*0.262,SIZEX*0.09,SIZEY*0.275,al_map_rgb(0,0,255),1);
    //MouseSpawn
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*0.285,0,SIZEY*0.285,al_map_rgb(0,0,255),2);
    if (MouseSpawn)
    {
        al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.285,ALLEGRO_ALIGN_LEFT, "MouseSpawn: ");
        al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.31,ALLEGRO_ALIGN_LEFT, "Size: %.1f",MouseSpawnSize);
        if (MouseSpawnCont) al_draw_filled_rectangle(SIZEX*0.08,SIZEY*0.292,SIZEX*0.09,SIZEY*0.305,al_map_rgb(0,0,255));
        else al_draw_rectangle(SIZEX*0.08,SIZEY*0.292,SIZEX*0.09,SIZEY*0.305,al_map_rgb(0,0,255),1);
    }
    else
        {
        al_draw_textf(font, al_map_rgb(50,50,50), 0, SIZEY*0.285,ALLEGRO_ALIGN_LEFT, "MouseSpawn: ");
        al_draw_textf(font, al_map_rgb(50,50,50), 0, SIZEY*0.31,ALLEGRO_ALIGN_LEFT, "Size: %.1f",MouseSpawnSize);
        if (MouseSpawnCont) al_draw_filled_rectangle(SIZEX*0.08,SIZEY*0.292,SIZEX*0.09,SIZEY*0.305,al_map_rgb(50,50,50));
        else al_draw_rectangle(SIZEX*0.08,SIZEY*0.292,SIZEX*0.09,SIZEY*0.305,al_map_rgb(50,50,50),1);
    }
    al_draw_line(SIZEX*0.19,SIZEY*0.32,SIZEX*0.06,SIZEY*0.32,al_map_rgb(0,0,255),2);
    float MouseSpawnSizeContX=(MouseSpawnSize-0.1)/39.9*0.13+0.06; //Incomplete/correct
    al_draw_filled_circle(SIZEX*MouseSpawnSizeContX,SIZEY*0.32,SIZEX*0.005,al_map_rgb(0,0,255));
    
    //MouseAttraction
    al_draw_line(SIZEX*SETTINGSSIZEX,SIZEY*0.345,0,SIZEY*0.345,al_map_rgb(0,0,255),2);
    if (EMouseattraction) al_draw_textf(font, al_map_rgb(0,0,255), 0, SIZEY*0.345,ALLEGRO_ALIGN_LEFT, "MouseGrav: %.0f",Mouseattraction);
    else al_draw_textf(font, al_map_rgb(50,50,50), 0, SIZEY*0.345,ALLEGRO_ALIGN_LEFT, "MouseGrav: %.0f",Mouseattraction);
    al_draw_line(SIZEX*0.19,SIZEY*0.36,SIZEX*0.09,SIZEY*0.36,al_map_rgb(0,0,255),2);
    float MouseattractionContX=(Mouseattraction+50)/100.*0.10+0.09; //Incomplete/correct
    al_draw_filled_circle(SIZEX*MouseattractionContX,SIZEY*0.36,SIZEX*0.005,al_map_rgb(0,0,255));

}


void HandleEvent(ALLEGRO_EVENT &event, std::vector<Ball> &Balls) {

    if (event.type==ALLEGRO_EVENT_DISPLAY_CLOSE) std::exit(0);
    else if (event.type==ALLEGRO_EVENT_KEY_DOWN) { //Keyboard event
        if (event.keyboard.keycode==ALLEGRO_KEY_S) ShowSettings=!ShowSettings;
        return;

    }
    else if (event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) //Mouse Event
    {
        if (ShowSettings)
        {
            if (event.mouse.x>SIZEX*0.09  and event.mouse.x<SIZEX*0.10 and event.mouse.y>SIZEY*0.075 and event.mouse.y<SIZEY*0.09) BoxBounce=!BoxBounce;
            else if (event.mouse.x>SIZEX*0.05  and event.mouse.x<SIZEX*0.06 and event.mouse.y>SIZEY*0.11 and event.mouse.y<SIZEY*0.125) Collision=!Collision;
            else if (event.mouse.x>SIZEX*0.0  and event.mouse.x<SIZEX*0.07 and event.mouse.y>SIZEY*0.04 and event.mouse.y<SIZEY*0.06) Egravity=!Egravity;
            else if (event.mouse.x>SIZEX*0.0  and event.mouse.x<SIZEX*0.08 and event.mouse.y>SIZEY*0.14 and event.mouse.y<SIZEY*0.16) Eviscosity=!Eviscosity;
            else if (event.mouse.x>SIZEX*0.0  and event.mouse.x<SIZEX*0.09 and event.mouse.y>SIZEY*0.17 and event.mouse.y<SIZEY*0.19) Espawn=!Espawn;
            else if (event.mouse.x>SIZEX*0.0  and event.mouse.x<SIZEX*0.07 and event.mouse.y>SIZEY*0.20 and event.mouse.y<SIZEY*0.22) Edecay=!Edecay;
            else if (event.mouse.x>SIZEX*0.0  and event.mouse.x<SIZEX*0.11 and event.mouse.y>SIZEY*0.23 and event.mouse.y<SIZEY*0.25) Edecaylimit=!Edecaylimit;
            else if (event.mouse.x>SIZEX*0.08  and event.mouse.x<SIZEX*0.09 and event.mouse.y>SIZEY*0.262 and event.mouse.y<SIZEY*0.275) CollisionMerge=!CollisionMerge;
            else if (event.mouse.x>SIZEX*0.08  and event.mouse.x<SIZEX*0.09 and event.mouse.y>SIZEY*0.292 and event.mouse.y<SIZEY*0.305) {MouseSpawnCont=!MouseSpawnCont; if (MouseSpawnCont) MouseSpawn=true;}
            else if (event.mouse.x>SIZEX*0.0  and event.mouse.x<SIZEX*0.075 and event.mouse.y>SIZEY*0.292 and event.mouse.y<SIZEY*0.305) MouseSpawn=!MouseSpawn;
            else if (event.mouse.x>SIZEX*0.0  and event.mouse.x<SIZEX*0.09 and event.mouse.y>SIZEY*0.35 and event.mouse.y<SIZEY*0.37) EMouseattraction=!EMouseattraction;
        }
        
        if (MouseSpawn and !MouseSpawnCont and (!(event.mouse.x<SIZEX*SETTINGSSIZEX and event.mouse.y<SIZEY*SETTINGSSIZEY) or !ShowSettings)) 
        {
            SpawnBall(Balls,event.mouse.x/zoomScale+xOffSet,event.mouse.y/zoomScale+yOffSet,MouseSpawnSize,0,0);
        }    


        return;
    }
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    if(state.buttons & 1)
    {
        if (ShowSettings)
        {
            if (state.x>SIZEX*0.07  and state.x<SIZEX*0.19 and state.y>SIZEY*0.04 and state.y<SIZEY*0.06)
            {
                Egravity=true;
                float relx= (float)state.x/SIZEX;
                relx-=0.07;
                relx*=.5;
                relx/=0.12;
                relx-=0.25;
                GRAVITY=relx;
            }
            else if (state.x>SIZEX*0.08  and state.x<SIZEX*0.19 and state.y>SIZEY*0.14 and state.y<SIZEY*0.16)
            {
                Eviscosity=true;
                float relx= (float)state.x/SIZEX;
                relx-=0.08;
                relx*=50;
                relx/=0.11;
                relx-=25;
                viscosity=relx;
            }
            else if (state.x>SIZEX*0.09  and state.x<SIZEX*0.19 and state.y>SIZEY*0.17 and state.y<SIZEY*0.19)
            {
                Espawn=true;
                float relx= (float)state.x/SIZEX;
                relx-=0.09;
                relx*=2.5;
                relx/=0.09;
                spawnrate=relx;
            }
            else if (state.x>SIZEX*0.07  and state.x<SIZEX*0.19 and state.y>SIZEY*0.20 and state.y<SIZEY*0.22)
            {
                Edecay=true;
                float relx= (float)state.x/SIZEX;
                relx-=0.07;
                relx*=0.2;
                relx/=0.12;
                relx+=0.9;
                Bdecay=relx;
            }
            else if (state.x>SIZEX*0.11  and state.x<SIZEX*0.19 and state.y>SIZEY*0.23 and state.y<SIZEY*0.25)
            {

                Edecaylimit=true;
                float relx= (float)state.x/SIZEX;
                relx-=0.11;
                relx*=4.99;
                relx/=0.08;
                relx+=0.01;
                decaylimit=relx;
            }
            else if (state.x>SIZEX*0.06  and state.x<SIZEX*0.19 and state.y>SIZEY*0.31 and state.y<SIZEY*0.33)
            {

                MouseSpawn=true;
                float relx= (float)state.x/SIZEX;
                relx-=0.06;
                relx*=39.9;
                relx/=0.13;
                relx+=0.1;
                MouseSpawnSize=relx;
            }
            else if (state.x>SIZEX*0.09  and state.x<SIZEX*0.19 and state.y>SIZEY*0.35 and state.y<SIZEY*0.37)
            {

                EMouseattraction=true;
                float relx= (float)state.x/SIZEX;
                relx-=0.09;
                relx*=100.;
                relx/=0.10;
                relx-=50;
                Mouseattraction=relx;
            } 
        }
    }
}
void HandleNoEventMouse(std::vector<Ball> &Balls) {

    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    if(state.buttons & 1) 
    {
        if (MouseSpawnCont and MouseSpawn and (!(state.x<SIZEX*SETTINGSSIZEX and state.y<SIZEY*SETTINGSSIZEY) or !ShowSettings)) 
        {
            SpawnBall(Balls,state.x/zoomScale+xOffSet,state.y/zoomScale+yOffSet,MouseSpawnSize,0,0);
            return;
        }
        if (EMouseattraction and (!(state.x<SIZEX*SETTINGSSIZEX and state.y<SIZEY*SETTINGSSIZEY) or !ShowSettings)) 
        {
            vektor mousatr;
            mousatr.x=state.x/zoomScale+xOffSet;
            mousatr.y=state.y/zoomScale+yOffSet;
            for( auto &ThisBall : Balls) ThisBall.CalculateSingleAttraction(mousatr,Mouseattraction);
        }
    }
    ALLEGRO_KEYBOARD_STATE key_state;
    al_get_keyboard_state(&key_state);
    if(al_key_down(&key_state,ALLEGRO_KEY_PAD_MINUS)) 
    { 
        float newZoomScale=zoomScale-zoomScale*0.02;
        float zoom_ratio=(newZoomScale)/zoomScale;
        xOffSet-=(SIZEX/zoomScale)*(1-zoom_ratio)/2.;
        yOffSet-=(SIZEY/zoomScale)*(1-zoom_ratio)/2.;
        zoomScale=newZoomScale;
    
    }
    if(al_key_down(&key_state,ALLEGRO_KEY_PAD_PLUS)) 
    {
        float newZoomScale=zoomScale+zoomScale*0.02;
        float zoom_ratio=(newZoomScale)/zoomScale;
        xOffSet-=(SIZEX/zoomScale)*(1-zoom_ratio)/2.;
        yOffSet-=(SIZEY/zoomScale)*(1-zoom_ratio)/2.;
        zoomScale=newZoomScale; 
    }
    if(al_key_down(&key_state,ALLEGRO_KEY_DOWN)) yOffSet+=10/zoomScale;
    if(al_key_down(&key_state,ALLEGRO_KEY_UP)) yOffSet-=10/zoomScale;
    if(al_key_down(&key_state,ALLEGRO_KEY_LEFT)) xOffSet-=10/zoomScale;
    if(al_key_down(&key_state,ALLEGRO_KEY_RIGHT)) xOffSet+=10/zoomScale;

    if(al_key_down(&key_state,ALLEGRO_KEY_C))
    {
        auto CenterOfMass=GetCenterOfMass(Balls);
        xOffSet=CenterOfMass.x-(SIZEX/zoomScale)/2.;
        yOffSet=CenterOfMass.y-(SIZEY/zoomScale)/2.;
    }
}
