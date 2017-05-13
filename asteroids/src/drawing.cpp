/* Jaimine Mistry W15022143	*/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <display.h>
#include <mbed.h>
#include <utilities.h>
#include <controls.h>
#include <drawing.h>
#include <physics.h>

/** LCD **/
Display *lcd = Display::theDisplay();
typedef uint16_t colour_t;
#define rgb(r,g,b) ((uint16_t)(31 * r /255)<<11 | (uint16_t)(63 * g /255)<<5 | (uint16_t)(31 * b /255))
const colour_t background = rgb(0,51,102);

/** Inputted onto LCD **/
void draw(void){
        lcd->fillScreen(background);
        drawmissiles(active);
        drawasteroids(asteroidactive);
        lcd->drawRect(0, 0, 480, 15, WHITE);
        lcd->setCursor(2,5);
        lcd->printf("Asteroids");
        lcd->setCursor(100,5);
        lcd->printf("Lives Left: %i", lives);
        lcd->setCursor(210,5);
        lcd->printf("Current Life: %i", timealive);
				lcd->setCursor(340,5);
        lcd->printf("Total Score: %i", totaltimealive);
				if(shieldhealth==3){
					/** Healthy shield **/
					lcd->drawLine(originX+leftX,originY+leftY,originX+pointX,originY+pointY,GREEN);
					lcd->drawLine(originX+leftX,originY+leftY,originX+rightX,originY+rightY,GREEN);
					lcd->drawLine(originX+rightX,originY+rightY,originX+pointX,originY+pointY,GREEN);
				}
				if(shieldhealth==2){
					/** Half-health shield **/
					lcd->drawLine(originX+leftX,originY+leftY,originX+pointX,originY+pointY,ORANGE);
					lcd->drawLine(originX+leftX,originY+leftY,originX+rightX,originY+rightY,ORANGE);
					lcd->drawLine(originX+rightX,originY+rightY,originX+pointX,originY+pointY,ORANGE);
				}
				if(shieldhealth==1){
					/** Low shield **/
					lcd->drawLine(originX+leftX,originY+leftY,originX+pointX,originY+pointY,RED);
					lcd->drawLine(originX+leftX,originY+leftY,originX+rightX,originY+rightY,RED);
					lcd->drawLine(originX+rightX,originY+rightY,originX+pointX,originY+pointY,RED);
				}
				if(shieldhealth<1){
					/** No shield **/
					lcd->drawLine(originX+leftX,originY+leftY,originX+pointX,originY+pointY,WHITE);
					lcd->drawLine(originX+leftX,originY+leftY,originX+rightX,originY+rightY,WHITE);
					lcd->drawLine(originX+rightX,originY+rightY,originX+pointX,originY+pointY,WHITE);
				}
				shield();
        swap_double_buffers();
}

void gameovertext(void){
	lcd->fillScreen(background);
	lcd->setCursor(190,115);
	lcd->printf("GAME OVER");
	lcd->setCursor(190,125);
	lcd->printf("FINAL SCORE: %i", totaltimealive);
	swap_double_buffers();
}

void init_double_buffering(void){
    uint16_t *buffer = lcd->getFb();
    uint16_t *frame2 = buffer+(480*272);
    LPC_LCD->UPBASE = (uint32_t)frame2;
}

void drawmissiles(struct missile *lst){
    while(lst) {
        lcd->fillCircle(lst->x,lst->y, 1, WHITE);
        lst = lst->next;
    }
}

void drawasteroids(struct asteroid *lst){
    while(lst) {
        lcd->fillCircle(lst->asteroidX,lst->asteroidY, 10, WHITE);
        lst = lst->next;
    }
}

void shield(void){
	if(shieldhealth>0){
		lcd->setCursor(2,245);
		lcd->printf("Shield Health:");
	}
	if(shieldhealth==1){
		lcd->drawRect(2, 255, 25, 5, RED);
	} else if(shieldhealth==2){
		lcd->drawRect(2, 255, 25, 5, RED);
		lcd->drawRect(29, 255, 25, 5, YELLOW);
	} else if(shieldhealth==3){
		lcd->drawRect(2, 255, 25, 5, RED);
		lcd->drawRect(29, 255, 25, 5, YELLOW);
		lcd->drawRect(56, 255, 25, 5, GREEN);
	}
}

void swap_double_buffers(void){
    unsigned int b;
    b = LPC_LCD->UPBASE;
    LPC_LCD->UPBASE = (uint32_t)lcd->getFb();
    lcd->setFb((uint16_t *)b);
}
