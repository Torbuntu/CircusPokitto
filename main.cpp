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
    bool pop;
};


bool collides(int x, int y, Boon &row){
    return (x < row.x + 8) && (x + 16 > row.x) && (y < row.y + 8) && (y + 16 > row.y);
}

int main(){
    using Pokitto::Core;
    using Pokitto::Display;
    using Pokitto::Buttons;
    
    Core::begin();
    Display::loadRGBPalette(miloslav);


    int x=32, y=132, vy=-3, vx = 0, speed=3;
    int x2 = 64, y2 = 132, c2=0;
    int barX = 38, barY = 132;
    bool barMirror = false;
    
    int rowSize = 19;
    
    int score = 0;
    
    Boon rowA[rowSize];
    Boon rowB[rowSize];
    Boon rowC[rowSize];
    
    for(int i = 0; i < rowSize; ++i){
        Boon a;
        a.x = i*12;
        a.y = 16;
        a.color = 0;
        a.pop = false;
        
        Boon b;
        b.x = i*12;
        b.y = 26;
        b.color = 16;
        b.pop = false;
        
        Boon c;
        c.x = i*12;
        c.y = 36;
        c.color = 32;
        c.pop = false;
        
        rowA[i] = a;
        rowB[i] = b;
        rowC[i] = c;
    }
    
    
    
    while( Core::isRunning() ){
        if( !Core::update() ) 
            continue;

        if(Buttons::leftBtn() && barX > 8) barX -= speed;
        else if(Buttons::rightBtn() && barX + 40 < Display::width) barX += speed;
        
        // Update balloon movement and player collision and draw
        for(int i = 0; i < rowSize; ++i){
            
            rowA[i].x--;
            if(rowA[i].x < -8)rowA[i].x = Display::width;
            
            rowB[i].x++;
            if(rowB[i].x > Display::width )rowB[i].x = -8;
            
            rowC[i].x--;
            if(rowC[i].x < -8)rowC[i].x = Display::width;
            
            if(y < 17 && !rowA[i].pop && collides(x, y, rowA[i])){
                if(x < rowA[i].x+4){
                    vx = -1;
                }else {
                    vx = 1;
                }
                rowA[i].pop = true;
                score += 5;
                vy = 2;
            }
            
            if(y < 27 && !rowB[i].pop && collides(x, y, rowB[i])){
                if(x < rowB[i].x+4){
                    vx = -1;
                }else {
                    vx = 1;
                }
                rowB[i].pop = true;
                score += 5;
                vy = 2;
            }
            
            if(y < 37 && !rowC[i].pop && collides(x, y, rowC[i])){
                if(x < rowC[i].x+4){
                    vx = -1;
                }else {
                    vx = 1;
                }
                rowC[i].pop = true;
                score += 5;
                vy = 2;
            }
            
            if(!rowA[i].pop) Display::drawSprite(rowA[i].x, rowA[i].y, Balloon, false, false, rowA[i].color);
            if(!rowB[i].pop) Display::drawSprite(rowB[i].x, rowB[i].y, Balloon, false, false, rowB[i].color);
            if(!rowC[i].pop) Display::drawSprite(rowC[i].x, rowC[i].y, Balloon, false, false, rowC[i].color);
        }
        
        
        // Balloon collision
        
        
        // Update player position
        if(y < 4) vy = 2;
        if(x < 1 ) {
            x = 0;
            vx = -vx;
        }
        if(x+17 > Display::width){
            x=Display::width;
            vx = -vx;
        }
        // Player is bellow bar height
        if(y >= barY-16) {
            // Player is within bar x
            if(x+8 > barX && x < barX + 26){
                barMirror = !barMirror;
                vy = -3;
                x = x2;
                
            
            }
            if(y > barY){
                //newGame
            }
        }
        
        if(barMirror) x2 = barX + 24;
        else x2 = barX-6;
        
        y += vy;
        x += vx;
        
        
        //Draw player and bar
        Display::drawSprite(x, y, Smile);
        Display::drawSprite(x2, y2, Smile);
        Display::drawSprite(barX, barY, Bar, false, barMirror);
        
    }
    
    return 0;
}
