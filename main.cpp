#include <Pokitto.h>
#include <miloslav.h>
#include <Tilemap.hpp>
#include <SDFileSystem.h>
#include "Smile.h"
#include "Bar.h"
#include "Balloon.h"
#include "maps.h"


struct Boon{
    int x;
    int y;
    int color;
};

int main(){
    using Pokitto::Core;
    using Pokitto::Display;
    using Pokitto::Buttons;
    
    Core::begin();
    Display::loadRGBPalette(miloslav);


    int x=32, y=132, vy=-3, speed=3;
    int x2 = 64, y2 = 132, c2=0;
    int barX = 38, barY = 132;
    bool barMirror = false;
    
    int rowSize = 19;
    
    Boon rowA[rowSize];
    Boon rowB[rowSize];
    Boon rowC[rowSize];
    
    for(int i = 0; i < rowSize; ++i){
        Boon a;
        a.x = i*12;
        a.y = 16;
        a.color = 0;
        
        Boon b;
        b.x = i*12;
        b.y = 26;
        b.color = 16;
        
        Boon c;
        c.x = i*12;
        c.y = 36;
        c.color = 32;
        
        rowA[i] = a;
        rowB[i] = b;
        rowC[i] = c;
    }
    
    
    
    while( Core::isRunning() ){
        if( !Core::update() ) 
            continue;

        if(Buttons::leftBtn()) barX -= speed;
        else if(Buttons::rightBtn()) barX += speed;
        
        
        
        for(int i = 0; i < rowSize; ++i){
            rowA[i].x--;
            if(rowA[i].x < -8)rowA[i].x = Display::width;
            
            rowB[i].x++;
            if(rowB[i].x > Display::width )rowB[i].x = -8;
            
            rowC[i].x--;
            if(rowC[i].x < -8)rowC[i].x = Display::width;
            
            
            Display::drawSprite(rowA[i].x, rowA[i].y, Balloon, false, false, rowA[i].color);
            Display::drawSprite(rowB[i].x, rowB[i].y, Balloon, false, false, rowB[i].color);
            Display::drawSprite(rowC[i].x, rowC[i].y, Balloon, false, false, rowC[i].color);
        }
        
        
        if(y < 4) vy = 2;
        
        if(y >= barY-16) {
            if(x+8 > barX && x < barX + 26){
                barMirror = !barMirror;
                vy = -3;
            }
            if(y > barY){
                //newGame
            }
        }
        
        if(barMirror) x2 = barX + 24;
        else x2 = barX-6;
        
        y += vy;
        
        
        

        Display::drawSprite(x, y, Smile);
        Display::drawSprite(x2, y2, Smile);
        Display::drawSprite(barX, barY, Bar, false, barMirror);
        
    }
    
    return 0;
}
