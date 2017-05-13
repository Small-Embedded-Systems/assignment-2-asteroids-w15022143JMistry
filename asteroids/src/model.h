/* Jaimine Mistry W15022143	*/
/* Model of Asteroids */
struct point {
    float x,y;
};
typedef struct point coordinate_t;
typedef struct point vector_t;

struct ship {
    coordinate_t p;
    vector_t     v;
};

struct rock {
    coordinate_t p;
    struct rock *next;
};

struct missile {
    coordinate_t p;
    struct missile *next;
};

void physics(void);
