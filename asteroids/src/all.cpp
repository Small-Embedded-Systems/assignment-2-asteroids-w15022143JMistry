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
#include <physics.h>
#include <drawing.h>

Ticker drawing;
Ticker model;
Ticker controller;
Ticker asteroids;
static const float Dt = 0.01;

/** Main Function including initialisation **/
int main(){
    initialise_heap();
    initialise_asteroidheap();
    init_double_buffering();
		initialvalues();
		lives=5;
		drawing.attach(draw, 0.025);
		model.attach(physics, Dt);
		controller.attach(controls, 0.1);
		asteroids.attach(asteroid_system, 0.1);
		while(1){
		if(lives==0){
			drawing.detach();
			model.detach();
			controller.detach();
			asteroids.detach();
			gameovertext();
			if(startagain()){
				totalscore=0;
				totaltimealive=0;
				initialvalues();
				lives=5;
				drawing.attach(draw, 0.025);
				model.attach(physics, Dt);
				controller.attach(controls, 0.1);
				asteroids.attach(asteroid_system, 0.1);
			}
		}
	}
}
