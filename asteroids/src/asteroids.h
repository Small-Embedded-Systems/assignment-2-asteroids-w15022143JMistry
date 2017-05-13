/* Jaimine Mistry W15022143	*/

extern float elapsed_time; /* duration of how long the ship has been active */
extern int   score;        /* total points */
extern int   lives;        /* lives remaining */
extern struct ship player;
extern struct rock *asteroids; /* range of rocks / pointer to linked-list */
extern struct missile *shots;  /* range of missiles / pointer to linked-list */
extern const float Dt; /* Time sneeded for consistent motion */
