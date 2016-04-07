# 1 "consigne.c"
# 1 "C:\\Users\\DenisT\\Desktop\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\PropBLDC.X//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "consigne.c"
# 1 "Configware.h" 1




void pllConfig(void);
void canPinAssign(void);
# 2 "consigne.c" 2
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
# 3 "consigne.c" 2
# 1 "Constantes.h" 1
# 4 "consigne.c" 2
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
# 5 "consigne.c" 2





relativePosType prCsgPos;
relativePosType prCsgFinalPos;
relativePosType prCsgVel;
relativePosType prCsgNomVel;
relativePosType prCsgNomAcc;
relativePosType prMinDist;
csgStatusType prCsgStatus;



csgStatusType csgInit(relativePosType nomVel, relativePosType nomAcc) {
 prCsgPos.l = 0;
 prCsgFinalPos.l = 0;
 prCsgVel.l = 0;
 prCsgNomVel.l = nomVel.l;
 prCsgNomAcc.l = nomAcc.l;
 prMinDist.l = prCsgNomAcc.l*((1/100.0)*(1/100.0)/2);

 prCsgPos.r = 0;
 prCsgFinalPos.r = 0;
 prCsgVel.r = 0;
 prCsgNomVel.r = nomVel.r;
 prCsgNomAcc.r = nomAcc.r;
 prMinDist.r = prCsgNomAcc.r*((1/100.0)*(1/100.0)/2);
 prCsgStatus = CSG_STANDING;
 return(prCsgStatus);
}


void csgSetFinalPos(relativePosType finalPos) {
 prCsgFinalPos.l = finalPos.l;
 prCsgFinalPos.r = finalPos.r;
 prCsgStatus = CSG_MOVING;
}


inline void csgSetNomAcc(relativePosType nomAcc) {
 if (nomAcc.l >=0) {
  prCsgNomAcc.l = nomAcc.l;
 } else {
  prCsgNomAcc.l = -nomAcc.l;
 }
 if (nomAcc.r >= 0) {
  prCsgNomAcc.r = nomAcc.r;
 } else {
  prCsgNomAcc.r = -nomAcc.r;
 }
 prMinDist.l = prCsgNomAcc.l*((1/100.0)*(1/100.0)/2);
 prMinDist.r = prCsgNomAcc.r*((1/100.0)*(1/100.0)/2);
}


inline void csgSetNomVel(relativePosType nomVel) {
 if (nomVel.l >= 0) {
  prCsgNomVel.l = nomVel.l;
 } else {
  prCsgNomVel.l = -nomVel.l;
 }
 if (nomVel.r >= 0) {
  prCsgNomVel.r = nomVel.r;
 } else {
  prCsgNomVel.r = -nomVel.r;
 }
}


inline relativePosType csgGetVel(void) {
 return(prCsgVel);
}


inline relativePosType csgGetPos(void) {
 return(prCsgPos);
}


inline relativePosType csgGetNomVel(void) {
 return(prCsgNomVel);
}


inline relativePosType csgGetNomAcc(void) {
 return(prCsgNomAcc);
}


inline relativePosType csgGetFinalPos(void) {
 return(prCsgFinalPos);
}


inline csgStatusType csgGetState(void) {
    return(prCsgStatus);
}

csgStatusType csgCompute(void) {
 float tmp;
 float acc;
 float sqrVel;
 csgStatusType state;

 state = CSG_STANDING;
 tmp = (((prCsgFinalPos.l - prCsgPos.l) < 0) ? -(prCsgFinalPos.l - prCsgPos.l) : (prCsgFinalPos.l - prCsgPos.l));
 if (tmp <= prMinDist.l) {
  prCsgVel.l = 0;
  prCsgPos.l = prCsgFinalPos.l;
 } else {
  state = CSG_MOVING;
  sqrVel = prCsgVel.l*prCsgVel.l;
  tmp = prCsgPos.l + prCsgVel.l*(1/100.0) + (((prCsgVel.l) < 0) ? -1 : 1)*sqrVel/(2*prCsgNomAcc.l);
  if (prCsgPos.l < prCsgFinalPos.l) {
   if (tmp > prCsgFinalPos.l) {
    acc = sqrVel/(2*(prCsgPos.l - prCsgFinalPos.l));
   } else if (prCsgVel.l < prCsgNomVel.l) {
    if (prCsgVel.l < prCsgNomVel.l-prCsgNomAcc.l*(1/100.0)) {
     acc = prCsgNomAcc.l;
    } else {
     acc = (prCsgNomVel.l - prCsgVel.l)*100.0;
    }
   } else {
    acc = 0;
   }
  } else {
   if (tmp < prCsgFinalPos.l) {
    acc = sqrVel/(2*(prCsgPos.l - prCsgFinalPos.l));
   } else if (prCsgVel.l > -prCsgNomVel.l) {
    if (prCsgVel.l > prCsgNomAcc.l*(1/100.0) - prCsgNomVel.l) {
     acc = -prCsgNomAcc.l;
    } else {
     acc = -(prCsgNomVel.l + prCsgVel.l)*100.0;
    }
   } else {
    acc = 0;
   }
  }
  prCsgPos.l += prCsgVel.l*(1/100.0) + acc*((1/100.0)*(1/100.0)/2);
  prCsgVel.l += acc*(1/100.0);
 }

 if ((((prCsgFinalPos.r - prCsgPos.r) < 0) ? -(prCsgFinalPos.r - prCsgPos.r) : (prCsgFinalPos.r - prCsgPos.r)) <= prMinDist.r) {
  prCsgVel.r = 0;
  prCsgPos.r = prCsgFinalPos.r;
 } else {
  state = CSG_MOVING;
  sqrVel = prCsgVel.r*prCsgVel.r;
  tmp = prCsgPos.r + prCsgVel.r*(1/100.0) + (((prCsgVel.r) < 0) ? -1 : 1)*sqrVel/(2*prCsgNomAcc.r);
  if (prCsgPos.r < prCsgFinalPos.r) {
   if (tmp > prCsgFinalPos.r) {
    acc = sqrVel/(2*(prCsgPos.r - prCsgFinalPos.r));
   } else if (prCsgVel.r < prCsgNomVel.r) {
    if (prCsgVel.r < prCsgNomVel.r-prCsgNomAcc.r*(1/100.0)) {
     acc = prCsgNomAcc.r;
    } else {
     acc = (prCsgNomVel.r - prCsgVel.r)*100.0;
    }
   } else {
    acc = 0;
   }
  } else {
   if (tmp < prCsgFinalPos.r) {
    acc = sqrVel/(2*(prCsgPos.r - prCsgFinalPos.r));
   } else if (prCsgVel.r > -prCsgNomVel.r) {
    if (prCsgVel.r > prCsgNomAcc.r*(1/100.0) - prCsgNomVel.r) {
     acc = -prCsgNomAcc.r;
    } else {
     acc = -(prCsgNomVel.r + prCsgVel.r)*100.0;
    }
   } else {
    acc = 0;
   }
  }
  prCsgPos.r += prCsgVel.r*(1/100.0) + acc*((1/100.0)*(1/100.0)/2);
  prCsgVel.r += acc*(1/100.0);
 }
 prCsgStatus = state;
 return(prCsgStatus);
}
