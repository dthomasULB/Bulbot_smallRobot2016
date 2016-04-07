# 1 "Regulator.c"
# 1 "C:\\Users\\DenisT\\Desktop\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\PropBLDC.X//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "Regulator.c"
# 1 "Configware.h" 1




void pllConfig(void);
void canPinAssign(void);
# 2 "Regulator.c" 2
# 1 "globals.h" 1



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
# 5 "globals.h" 2

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
# 3 "Regulator.c" 2
# 1 "Consigne.h" 1




# 1 "../can/CanProp.h" 1
# 6 "Consigne.h" 2

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
# 4 "Regulator.c" 2
# 1 "motors.h" 1
void motorsInit(void);
void motorsEnable(void);
void motorsDisable(void);
void motorsSetSpeed(float dcR, float dcL);
# 5 "Regulator.c" 2
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
# 6 "Regulator.c" 2
# 1 "odoLibre.h" 1


void odoInit(void);


void calculeOdometrie(void);

inline relativePosType odoGetRelVel(void);

inline relativePosType odoGetRelPos(void);

inline absolutePosType odoGetAbsPos(void);


inline void odoSetAbsPos(absolutePosType newPos);
# 7 "Regulator.c" 2
# 1 "Regulator.h" 1
typedef enum {
 PATINAGE_DETECTED = 1,
 NO_PATINAGE = 0
} regType;

void regInit(void);
regType regCompute(void);
# 8 "Regulator.c" 2
# 18 "Regulator.c"
float prRegOldDcLeft, prRegOldDcRight;


void regInit(void) {
 prRegOldDcLeft = 0;
 prRegOldDcRight = 0;
}

regType regCompute(void) {
 relativePosType odoPos = odoGetRelPos();
 relativePosType csgPos = csgGetPos();
 relativePosType odoVel = odoGetRelVel();
 relativePosType csgVel = csgGetVel();
 float errT, errR, errVt, errVr;
 float dcTrans, dcRot, dcLeft, dcRight;


 errT = csgPos.l - odoPos.l;
 errR = csgPos.r - odoPos.r;
 errVt = csgVel.l - odoVel.l;
 errVr = csgVel.r - odoVel.r;

 dcTrans = 12*errT + 1*errVt;
 dcRot = 2.8*errR + 50E-3*errVr;


 dcRight = dcTrans + dcRot;
 dcLeft = dcTrans - dcRot;

 if ((dcRight - prRegOldDcRight) > 0.1) {
  dcRight = prRegOldDcRight + 0.1;
 } else if ((prRegOldDcRight - dcRight) > 0.1) {
  dcRight = prRegOldDcRight - 0.1;
 }
 prRegOldDcRight = dcRight;
 if ((dcLeft - prRegOldDcLeft) > 0.1) {
  dcLeft = prRegOldDcLeft + 0.1;
 } else if ((prRegOldDcLeft - dcLeft) > 0.1) {
  dcLeft = prRegOldDcLeft - 0.1;
 }
 prRegOldDcLeft = dcLeft;
 motorsSetSpeed(dcRight, dcLeft);

 if ((fabsf(errT) > 50E-3) || (fabsf(errR) > (5*(3.14159))/180)) {
        return(PATINAGE_DETECTED);
 } else {
  return(NO_PATINAGE);
 }
}
