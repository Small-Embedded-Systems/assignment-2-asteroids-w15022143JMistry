/* Jaimine Mistry W15022143	*/
typedef struct missile {
    float x,y;
    float v_x, v_y;
    float ttl;
    struct missile *next;
} node_t;

typedef struct asteroid {
    float asteroidX,asteroidY;
    float asteroidV_x, asteroidV_y;
    float asteroidTtl;
    struct asteroid *next;
} asteroid_t;


extern struct asteroid *asteroidactive;
extern float originX;
extern float originY;
extern int lives;
extern double speed;
extern int shieldhealth;
extern int totalscore;
extern double accel;
extern int timealive;
extern int totaltimealive;
extern int invincibility;
extern const int heapsize;
extern const int asteroidHeapsize;
extern int headingAngle;
extern float headingAngleRadians;
extern float pointX;
extern float pointY;
extern float leftX;
extern float leftY;
extern float rightX;
extern float rightY;
extern double score;
extern struct missile *active;


void strike(struct asteroid *r);
void missile_system(void);
void asteroid_system(void);
void initialise_heap(void);
void initialise_asteroidheap(void);
node_t *allocnode(void);
asteroid_t *asteroidallocnode(void);
void freenode(node_t *n);
void asteroidfreenode(asteroid_t *n);
void initialvalues(void);
void physics(void);
void checkshipasteroids(struct asteroid *c);
void checkmissilesasteroids(struct missile *a, struct asteroid *b);
void update(struct missile *l);
void asteroidupdate(struct asteroid *l);
void wraparound(void);
void time(void);
void strike(struct missile *r);
