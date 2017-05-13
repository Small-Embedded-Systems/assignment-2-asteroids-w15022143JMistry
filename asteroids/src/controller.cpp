/* Jaimine Mistry W15022143	*/
/* Controller */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <mbed.h>

/* asteroids */
#include "model.h"
#include "asteroids.h"
/* Joystick 5-way switch
*/
enum position { left,down,right,up,centre };
DigitalIn joystick[] = {P5_0, P5_1, P5_4, P5_2, P5_3};

void controls(void)
{

}
