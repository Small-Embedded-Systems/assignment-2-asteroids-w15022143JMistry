/* Jaimine Mistry W15022143	*/

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <display.h>
#include <mbed.h>
#include <physics.h>
#include <controls.h>

/** Joystick inputs **/
enum position { JLEFT,JDOWN,JRIGHT,JUP,JCENTRE};
DigitalIn buttons[] = {P5_0, P5_1, P5_4, P5_2, P5_3};

/** Joystick controls **/

void controls(void){
  if(ispressed(JLEFT)){
    headingAngle=headingAngle+9;
  } else if(ispressed(JRIGHT)){
    headingAngle=headingAngle-9;
  } else if(ispressed(JUP)){
		if(accel<2){
			accel=accel+0.2;
		}
  }
	if(ispressed(JCENTRE)){
		missile_system();
  }
}

bool startagain(void){
	if(lives==0 && ispressed(JCENTRE)){
		lives=3;
		return true;
			}
	return false;
}
bool ispressed(enum position p){
    return !buttons[p];
}
