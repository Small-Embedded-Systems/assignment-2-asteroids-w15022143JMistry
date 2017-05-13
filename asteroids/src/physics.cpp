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

/** Variables **/

static const int heapsize = 5;
static const int asteroidHeapsize = 11;
static node_t heap[heapsize];
static asteroid_t asteroidheap[asteroidHeapsize];
static node_t *freenodes;
static asteroid_t *asteroidfreenodes;

float originX;
float originY;
int headingAngle;
float headingAngleRadians;
float pointX;
float pointY;
float leftX;
float leftY;
float rightX;
float rightY;
double score;
int lives;
double speed;
int shieldhealth;
int totalscore;
double accel;
int timealive;
int totaltimealive;
int invincibility;

static const float Dt = 0.01;
struct missile *active = NULL;
struct asteroid *asteroidactive = NULL;

void physics(void){
    checkshipasteroids(asteroidactive);
    checkmissilesasteroids(active, asteroidactive);
    update(active);
    asteroidupdate(asteroidactive);
    wraparound();
    headingAngleRadians=radians(headingAngle);
    pointX=10*(cos(headingAngleRadians));
  	pointY=10*(sin(headingAngleRadians));
  	leftX=(-5*(cos(headingAngleRadians)))-(5*(sin(headingAngleRadians)));
  	leftY=(-5*(sin(headingAngleRadians)))+(5*(cos(headingAngleRadians)));
  	rightX=(-5*(cos(headingAngleRadians)))-(-5*(sin(headingAngleRadians)));;
  	rightY=(-5*(sin(headingAngleRadians)))+(-5*(cos(headingAngleRadians)));;
  	originX=originX+speed*(cos(headingAngleRadians));
  	originY=originY+speed*(sin(headingAngleRadians));
	  score++;
		if(speed<5){
			speed=speed+accel;
		}
		if(accel>0){
			accel=accel-0.1;
		}
		if(speed>0){
			speed=speed-0.01;
		}
		time();
		if(invincibility>0){
			invincibility--;
		}
}
void initialvalues(void){
	originX=240;
	originY=130;
	headingAngle=90;
	score=0.0;
	shieldhealth=3;
	totalscore=0;
	accel=0.0;
	invincibility=100;
}
void checkshipasteroids(struct asteroid *c){
    for( ; c ; c = c->next ) {
        if(c->asteroidX<(originX+8) && c->asteroidX>(originX-8)){
          if(c->asteroidY<(originY+8) && c->asteroidY>(originY-8)){
            if(shieldhealth>0){
							if(invincibility==0){
								shieldhealth--;
								invincibility=50;
							}
						} else if(shieldhealth<=0){
							if(invincibility==0){
								if(lives>0){
									lives--;
								}
								originX=240;
								originY=130;
								headingAngle=90;
								speed=0;
								totaltimealive=totaltimealive+timealive;
								score=0;
								invincibility=50;
							}
						}
          }
        }
    }
}

void checkmissilesasteroids(struct missile *a, struct asteroid *b) {
  for(; a ; a = a->next){
    for(; b ; b = b->next){
      if(a->x > (b->asteroidX-12) && a->x < (b->asteroidX+12)){
        if(a->y > (b->asteroidY-12) && a->y < (b->asteroidY+12)){
          a->ttl=0;
          b->asteroidTtl=0;
        }
      }

      }
    }
 }

 void update(struct missile *l){
    for( ; l ; l = l->next ) {
        l->x += l->v_x * Dt;
        l->y += l->v_y * Dt;
        if( l->x<0 || 480<l->x ) l->ttl=0;
        if( l->y<10 || 260<l->y ) l->ttl=0;
        l->ttl -= Dt;
        if( l->next->ttl<=0 ) {
            struct missile *expired = l->next;
            l->next = l->next->next;
            freenode(expired);
        }
    }
}

void asteroidupdate(struct asteroid *l){
    for( ; l ; l = l->next ) {
        l->asteroidX += l->asteroidV_x * Dt;
        l->asteroidY += l->asteroidV_y * Dt;
        if( l->asteroidX<-20 || 500<l->asteroidX ) l->asteroidTtl=0;
        if( l->asteroidY<25 || 280<l->asteroidY ) l->asteroidTtl=0;
        l->asteroidTtl -= Dt;
        if( l->next->asteroidTtl<=0 ) {
            struct asteroid *expired = l->next;
            l->next = l->next->next;
            asteroidfreenode(expired);
        }
    }
}
void wraparound(void){
  if(originX>480){
		originX=5;
	} else if(originX<0){
		originX=475;
	} else if(originY>260){
		originY=25;
	} else if(originY<20){
		originY=255;
	}
}

void time(void){
	timealive = (int)((score/100)+0.5);
}

void strike(struct missile *r){
    r->x = originX;
    r->y = originY;
    r->v_x = 200*(cos(headingAngleRadians));
    r->v_y = 200*(sin(headingAngleRadians));
    r->ttl = 200;
}
void strike(struct asteroid *r){
    r->asteroidX = randrange(10,470);
    r->asteroidY = randrange(10,250);
    r->asteroidV_x = randrange(-5,5);
    r->asteroidV_y = randrange(-5,5);
    r->asteroidTtl = randrange(900,1100);
}

void missile_system(void){
        struct missile *spark = allocnode();
        if(spark) {
            spark->next = active;
            active = spark;
            strike(spark);
        }
}

void asteroid_system(void){
        struct asteroid *asteroidspark = asteroidallocnode();
        if(asteroidspark) {
            asteroidspark->next = asteroidactive;
            asteroidactive = asteroidspark;
            strike(asteroidspark);
        }
}

void initialise_heap(void){
    int n;
    for( n=0 ; n<(heapsize-1) ; n++) {
        heap[n].next = &heap[n+1];
    }
    heap[n].next = NULL;
    freenodes = &heap[0];
}

void initialise_asteroidheap(void){
    int n;
    for( n=0 ; n<(asteroidHeapsize-1) ; n++) {
        asteroidheap[n].next = &asteroidheap[n+1];
    }
    asteroidheap[n].next = NULL;
    asteroidfreenodes = &asteroidheap[0];
}

node_t *allocnode(void){
    node_t *node = NULL;
    if( freenodes ) {
        node = freenodes;
        freenodes = freenodes->next;
    }
    return node;
}

asteroid_t *asteroidallocnode(void){
    asteroid_t *node = NULL;
    if( asteroidfreenodes ) {
        node = asteroidfreenodes;
        asteroidfreenodes = asteroidfreenodes->next;
    }
    return node;
}
void freenode(node_t *n){
    n->next = freenodes;
    freenodes = n;
}

void asteroidfreenode(asteroid_t *n){
    n->next = asteroidfreenodes;
    asteroidfreenodes = n;
}