# 1 "mouvements.c"
# 1 "C:\\Users\\DenisT\\Desktop\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\PropBLDC.X//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "mouvements.c"
# 1 "Globals.h" 1



# 1 "../can/CanTypes.h" 1
# 14 "../can/CanTypes.h"
typedef struct {
    int x;
    int y;
    int alpha;
} positionInteger;




typedef struct {
    int l;
    int r;
} relativeCoordInteger;
# 39 "../can/CanTypes.h"
typedef enum {
    DISABLED = 0,
    STANDING = 1,
    RELATIVE_MOVE = 2,
    TRAJECTORY = 3,
    TEST = 4,
    TRAJ_START_OUT = 250,
    TRAJ_END_OUT = 251,
    TRAJ_START_OBS = 252,
    TRAJ_END_OBS = 253,
    TRAJ_NO_WAY = 254
} propStateType;

typedef enum {
    PROP_IS_NO_OBSTACLE = 0,
    PROP_IS_UNMOVABLE_OBSTACLE = 1,
    PROP_IS_MOVABLE_OBSTACLE = 2
} propIsObstacleType;

typedef struct {
 float x;
 float y;
    float size;
} obstacleType;
# 5 "Globals.h" 2

typedef struct {
 float x;
 float y;
 float alpha;
} absolutePosType;

typedef struct {
    float l;
    float r;
} relativePosType;

typedef struct {
    float acc;
    float vel;
    float length;
} translationParamType;

typedef struct {
    float acc;
    float vel;
    float angle;
} rotationParamType;


positionInteger positionFloatToInteger(absolutePosType posFl);
relativeCoordInteger relativeCoordFloatToInteger(relativePosType posFl);
float satureAngle(float angle);
# 2 "mouvements.c" 2
# 1 "consigne.h" 1




# 1 "../can/CanProp.h" 1
# 6 "consigne.h" 2

 typedef enum {
  CSG_STANDING = 0,
  CSG_MOVING = 1
 } csgStatusType;




 csgStatusType csgInit(relativePosType nomVel, relativePosType nomAcc);

 csgStatusType csgCompute(void);

 void csgSetNomAcc(relativePosType nomAcc);

 void csgSetNomVel(relativePosType nomVel);

 void csgSetFinalPos(relativePosType finalPos);

 relativePosType csgGetVel(void);

 relativePosType csgGetPos(void);

 csgStatusType csgGetState(void);

 relativePosType csgGetNomAcc(void);

 relativePosType csgGetNomVel(void);

 relativePosType csgGetFinalPos(void);
# 3 "mouvements.c" 2
# 1 "c:\\program files (x86)\\microchip\\xc16\\v1.21\\bin\\bin\\../..\\include/stdlib.h" 1 3 4






# 1 "c:\\program files (x86)\\microchip\\xc16\\v1.21\\bin\\bin\\../..\\include/stddef.h" 1 3 4



typedef int ptrdiff_t;
typedef unsigned int size_t;
typedef short unsigned int wchar_t;







extern int errno;
# 8 "c:\\program files (x86)\\microchip\\xc16\\v1.21\\bin\\bin\\../..\\include/stdlib.h" 2 3 4
# 24 "c:\\program files (x86)\\microchip\\xc16\\v1.21\\bin\\bin\\../..\\include/stdlib.h" 3 4
typedef struct {
 int quot;
 int rem;
} div_t;
typedef struct {
 unsigned quot;
 unsigned rem;
} udiv_t;
typedef struct {
 long quot;
 long rem;
} ldiv_t;
typedef struct {
 unsigned long quot;
 unsigned long rem;
} uldiv_t;
# 49 "c:\\program files (x86)\\microchip\\xc16\\v1.21\\bin\\bin\\../..\\include/stdlib.h" 3 4
extern double atof(const char *);
extern double strtod(const char *, char **);
# 60 "c:\\program files (x86)\\microchip\\xc16\\v1.21\\bin\\bin\\../..\\include/stdlib.h" 3 4
extern int atoi(const char *);
extern unsigned xtoi(const char *);
extern long atol(const char *);
extern long strtol(const char *, char **, int);
extern unsigned long strtoul(const char *, char **, int);

extern long long atoll(const char *);
extern long long strtoll(const char *, char **, int);
extern unsigned long long strtoull(const char *, char **, int);

extern int rand(void);
extern void srand(unsigned int);
extern void * calloc(size_t, size_t);
extern div_t div(int numer, int denom);
extern udiv_t udiv(unsigned numer, unsigned denom);
extern ldiv_t ldiv(long numer, long denom);
extern uldiv_t uldiv(unsigned long numer,unsigned long denom);




extern void * malloc(size_t);
extern void free(void *);
extern void * realloc(void *, size_t);

extern void



abort(void);

extern void



exit(int);

extern int atexit(void (*)(void));
extern char * getenv(const char *);
extern char ** environ;




extern int system(char *);


extern void qsort(void *, size_t, size_t, int (*)(const void *, const void *));
extern void * bsearch(const void *, void *, size_t, size_t, int(*)(const void *, const void *));
extern int abs(int);
extern long labs(long);

extern char * itoa(char * buf, int val, int base);
extern char * utoa(char * buf, unsigned val, int base);
extern char * ltoa(char * buf, long val, int base);


extern char * ultoa(char * buf, unsigned long val, int base);
# 4 "mouvements.c" 2
# 1 "c:\\program files (x86)\\microchip\\xc16\\v1.21\\bin\\bin\\../..\\include/math.h" 1 3 4
# 38 "c:\\program files (x86)\\microchip\\xc16\\v1.21\\bin\\bin\\../..\\include/math.h" 3 4
float acosf(float);
float asinf(float);
float atanf(float);
float atan2f(float, float);
float cosf(float);
float sinf(float);
float tanf(float);
float coshf(float);
float sinhf(float);
float tanhf(float);
float expf(float);
float frexpf(float, int *);
float ldexpf(float, int);
float logf(float);
float log10f(float);





float modff(float, void *);



float powf(float, float);
float sqrtf(float);
float ceilf(float);
float fabsf(float);
float floorf(float);
float fmodf(float, float);






long double acosl(long double);
long double asinl(long double);
long double atanl(long double);
long double atan2l(long double, long double);
long double cosl(long double);
long double sinl(long double);
long double tanl(long double);
long double coshl(long double);
long double sinhl(long double);
long double tanhl(long double);
long double expl(long double);
long double frexpl(long double, int *);
long double ldexpl(long double, int);
long double logl(long double);
long double log10l(long double);
long double modfl(long double, long double *);
long double powl(long double, long double);
long double sqrtl(long double);
long double ceill(long double);
long double fabsl(long double);
long double floorl(long double);
long double fmodl(long double, long double);
# 138 "c:\\program files (x86)\\microchip\\xc16\\v1.21\\bin\\bin\\../..\\include/math.h" 3 4
unsigned long __udiv3216(unsigned long, unsigned int);
         long __div3216(long, int);
# 5 "mouvements.c" 2


void addTranslation(translationParamType param) {
 relativePosType tmp;

 tmp.r = 0;
 tmp.l = param.acc;
 csgSetNomAcc(tmp);
 tmp.l = param.vel;
 csgSetNomVel(tmp);
 tmp = csgGetPos();
 tmp.l += param.length;
 csgSetFinalPos(tmp);
}


void addRotation(rotationParamType param) {
 relativePosType tmp;

 tmp.l = 0;
 tmp.r = param.acc;
 csgSetNomAcc(tmp);
 tmp.r = param.vel;
 csgSetNomVel(tmp);
 tmp = csgGetPos();
 tmp.r += param.angle;
 csgSetFinalPos(tmp);
}


void stopNow(void) {
 relativePosType vel, acc, pos;

 vel = csgGetVel();
 acc = csgGetNomAcc();
 pos = csgGetPos();



 if (vel.l >0) {
  pos.l += vel.l*vel.l/(3*2*acc.l);
 } else if(vel.l < 0){
  pos.l -= vel.l*vel.l/(3*2*acc.l);
 }
 if (vel.r >0) {
  pos.r += vel.r*vel.r/(3*2*acc.r);
 } else if(vel.r < 0){
  pos.r -= vel.r*vel.r/(3*2*acc.r);
 }
 csgSetFinalPos(pos);
}


relativePosType calcSegment(absolutePosType curPos, absolutePosType newPos, int backward) {
 float x, y;
  relativePosType seg;

 x = newPos.x - curPos.x;
 y = newPos.y - curPos.y;
 seg.l = sqrtf(x*x + y*y);
 seg.r = satureAngle(atan2f(y, x) - curPos.alpha);
    if (backward ==1){
        seg.l=-seg.l;
        seg.r = seg.r - (3.14159);
    }
 return(seg);
}
