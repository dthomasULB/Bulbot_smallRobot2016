# 1 "GenerTraj.c"
# 1 "C:\\Users\\DenisT\\Desktop\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\PropBLDC.X//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "GenerTraj.c"



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
# 5 "GenerTraj.c" 2
# 1 "GenerTraj.h" 1
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
# 2 "GenerTraj.h" 2
# 1 "../Can/CanTypes.h" 1
# 3 "GenerTraj.h" 2




typedef struct {
 char a;
 char b;
 char dir;
} mapPosType;

void trajInit(void);


int findTrajectoire(absolutePosType rpStart, absolutePosType rpEnd, absolutePosType rpPath[]);

void trajAddObstacle(obstacleType obstacle);
void trajRemoveObstacle(obstacleType obstacle);
propIsObstacleType trajIsObstacleInMap(obstacleType obstacle);
# 6 "GenerTraj.c" 2
# 46 "GenerTraj.c"
typedef enum {
    UNPR = 0,
    DONE = 1,
    OBST = 2,
    MOVE_OBST = 3
} tileStatusType;

typedef struct {
    int d;
    char dir;
    tileStatusType done;
    int prec;
} dijkstra_st;


dijkstra_st dkNodes[(30*20)];




# 1 "test2_2016.h" 1
const tileStatusType initialMap[(30*20)] =
{ OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, OBST,
  OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST
  };
# 67 "GenerTraj.c" 2





void trajInit(void) {
    unsigned int i;

    for (i = 0; i < (30*20); i++) {
        dkNodes[i].d = 30000;
        dkNodes[i].dir = 0;
        dkNodes[i].done = initialMap[i];
        dkNodes[i].prec = -1;
    }
}


inline mapPosType RPtoMP(absolutePosType rpPos) {
    mapPosType mpPos;

    mpPos.a = (rpPos.x - 0)*10 ;
    mpPos.b = (rpPos.y - 0)*10 ;
    if (rpPos.alpha >= 0) {
        mpPos.dir = (rpPos.alpha + (3.14159) / 8) / ((3.14159) / 4);
    } else {
        mpPos.dir = (rpPos.alpha - (3.14159) / 8) / ((3.14159) / 4);
    }
    return (mpPos);
}


inline absolutePosType MPtoRP(mapPosType mpPos) {
    absolutePosType rpPos;

    rpPos.x = 0 + 0.1 * mpPos.a;
    rpPos.y = 0 + 0.1 * mpPos.b;
    rpPos.alpha = mpPos.dir * (3.14159) / 4;
    return (rpPos);
}

inline float computeSegAngle(absolutePosType rpP0, absolutePosType rpP1) {
    return (satureAngle(atan2f(rpP1.y - rpP0.y, rpP1.x - rpP0.x)));
}


inline void resetDijkstraVect(void) {
    unsigned int i;

    for (i = 0; i < (30*20); i++) {
        dkNodes[i].d = 30000;
        dkNodes[i].dir = 0;
        if (dkNodes[i].done == DONE) {
            dkNodes[i].done = UNPR;
        }
        dkNodes[i].prec = -1;
    }
}

inline void deleteNode(int curNode) {
    dkNodes[curNode].done = DONE;
}

inline void trajAddObstacle(obstacleType obstacle) {
    int a, b;
    mapPosType mpObsPos, mpObsSize;
    absolutePosType tmp;

    tmp.x = obstacle.x;
    tmp.y = obstacle.y;
    mpObsPos = RPtoMP(tmp);
    tmp.x = obstacle.size;
    tmp.y = obstacle.size;
    mpObsSize = RPtoMP(tmp);
    for (a = 0; a < mpObsSize.a; a++) {
        for (b = 0; b < mpObsSize.b; b++) {
            if (dkNodes[20 * (a + mpObsPos.a) + b + mpObsPos.b].done != OBST) {
                dkNodes[20 * (a + mpObsPos.a) + b + mpObsPos.b].done = MOVE_OBST;
            }
        }
    }
}

inline void trajRemoveObstacle(obstacleType obstacle) {
    int a, b;
    mapPosType mpObsPos, mpObsSize;
    absolutePosType tmp;

    tmp.x = obstacle.x;
    tmp.y = obstacle.y;
    mpObsPos = RPtoMP(tmp);
    tmp.x = obstacle.size;
    tmp.y = obstacle.size;
    mpObsSize = RPtoMP(tmp);
    for (a = 0; a < mpObsSize.a; a++) {
        for (b = 0; b < mpObsSize.b; b++) {
            if (dkNodes[20 * (a + mpObsPos.a) + b + mpObsPos.b].done == MOVE_OBST) {
                dkNodes[20 * (a + mpObsPos.a) + b + mpObsPos.b].done = UNPR;
            }
        }
    }
}

inline int findNeigbours(int curNode, int *neigbours) {
    int a, b, i, minA, maxA, minB, maxB, dA, dB, nb;

    a = curNode / 20;
    b = curNode - 20*a;
    nb = 0;
    if (a == 0) minA = 0;
    else minA = -1;
    if (a == 30 - 1) maxA = 0;
    else maxA = 1;
    if (b == 0) minB = 0;
    else minB = -1;
    if (b == 20 - 1) maxB = 0;
    else maxB = 1;
    for (dA = minA; dA <= maxA; dA++) {
        for (dB = minB; dB <= maxB; dB++) {
            i = curNode + 20 * dA + dB;
            if (dkNodes[i].done == UNPR) {
                neigbours[nb] = i;
                nb++;
            }
        }
    }
    return (nb);
}

inline int findNextNode(void) {
    int i, j;

    i = 0;
    while ((dkNodes[i].done != UNPR) && (i < (30*20))) {
        i++;
    }
    if (i >= (30*20)) {
        return (-1);
    }
    for (j = i; j < (30*20); j++) {
        if ((dkNodes[j].done == UNPR) && (dkNodes[j].d < dkNodes[i].d)) {
            i = j;
        }
    }
    return (i);
}

inline int atanMP(int b, int a) {
    switch (a) {
        case -1:
            switch (b) {
                case -1: return (-3);
                    break;
                case 0: return (4);
                    break;
                case 1: return (3);
                    break;
            }
            break;
        case 0:
            switch (b) {
                case -1: return (-2);
                    break;
                case 0: return (127);
                    break;
                case 1: return (2);
                    break;
            }
            break;
        case 1:
            switch (b) {
                case -1: return (-1);
                    break;
                case 0: return (0);
                    break;
                case 1: return (1);
                    break;
            }
            break;
    }
    return (127);
}

inline void updateDistance(int neigbour, int curNode, int endNode) {
    int a1, b1, a2, b2, dir, dist;

    a1 = curNode / 20;
    b1 = curNode - 20*a1;
    a2 = neigbour / 20;
    b2 = neigbour - 20*a2;
    dir = atanMP(b2 - b1, a2 - a1);

    dist = 2 * ((((a1 - a2) < 0) ? -(a1 - a2) : (a1 - a2)) + (((b1 - b2) < 0) ? -(b1 - b2) : (b1 - b2)));
    if (dist > 3) {
        dist = 3;
    }
    dist += dkNodes[curNode].d;
    if (dir != dkNodes[curNode].dir) {
        dist++;
    }
    if ((neigbour == endNode) && (dir != dkNodes[endNode].dir))
        dist++;


    if ((dist < dkNodes[neigbour].d) || ((dist == dkNodes[neigbour].d) && (dir == dkNodes[endNode].dir))) {
        dkNodes[neigbour].d = dist;
        dkNodes[neigbour].prec = curNode;
        dkNodes[neigbour].dir = dir;
    }
}
# 288 "GenerTraj.c"
inline int findPath(mapPosType mpStart, mapPosType mpEnd, mapPosType mpPath[]) {
    int curNode;
    int startNode;
    int endNode;
    int neigbours[8];
    int i, nb;
    mapPosType mpTmp;


    resetDijkstraVect();

    if ( (dkNodes[20 * mpStart.a + mpStart.b].done == OBST) ||
         (dkNodes[20 * mpStart.a + mpStart.b].done == MOVE_OBST) ) {
        dkNodes[20 * mpStart.a + mpStart.b].done = UNPR;
        return 252;
    } else if ( (dkNodes[20 * mpEnd.a + mpEnd.b].done == OBST) ||
                (dkNodes[20 * mpEnd.a + mpEnd.b].done == MOVE_OBST) ) {
        dkNodes[20 * mpStart.a + mpStart.b].done = UNPR;
        return 253;
    }
    if ((mpStart.a == mpEnd.a) && (mpStart.b == mpEnd.b)) {
        mpPath[0].a = mpStart.a;
        mpPath[0].b = mpStart.b;
        mpPath[1].b = mpEnd.a;
        mpPath[1].b = mpEnd.b;
        return (2);
    }

    startNode = 20 * mpStart.a + mpStart.b;
    endNode = 20 * mpEnd.a + mpEnd.b;
    dkNodes[startNode].d = 0;
    curNode = startNode;

    while (curNode != endNode) {
        deleteNode(curNode);
        nb = findNeigbours(curNode, neigbours);
        for (i = 0; i < nb; i++) {
            updateDistance(neigbours[i], curNode, endNode);
        }
        curNode = findNextNode();
        if (curNode == -1) {
            return (254);
        }
    }

    mpPath[0].a = curNode / 20;
    mpPath[0].b = curNode - 20*mpPath[0].a;
    mpPath[0].dir = dkNodes[curNode].dir;
    nb = 1;
    while (curNode != startNode) {
        curNode = dkNodes[curNode].prec;
        if (curNode == -1) {
            return ( 254);
        }
        mpPath[nb].a = curNode / 20;;
        mpPath[nb].b = curNode - 20*mpPath[nb].a;
        mpPath[nb].dir = dkNodes[curNode].dir;
        nb++;
    }

    for (i = 0; i < nb / 2; i++) {
        mpTmp.a = mpPath[i].a;
        mpTmp.b = mpPath[i].b;
        mpTmp.dir = mpPath[i].dir;
        mpPath[i].a = mpPath[nb - i - 1].a;
        mpPath[i].b = mpPath[nb - i - 1].b;
        mpPath[i].dir = mpPath[nb - i - 1].dir;
        mpPath[nb - i - 1].a = mpTmp.a;
        mpPath[nb - i - 1].b = mpTmp.b;
        mpPath[nb - i - 1].dir = mpTmp.dir;
    }
    return (nb);
}

inline int convertPath(absolutePosType rpStart, absolutePosType rpEnd, int pathSize, mapPosType mpPath[], absolutePosType rpPath[]) {
    unsigned int i;
    signed int length;
    signed int curDir, newDir;


    rpPath[0].x = rpStart.x;
    rpPath[0].y = rpStart.y;
    length = 1;



    curDir = atanMP(mpPath[1].b - mpPath[0].b, mpPath[1].a - mpPath[0].a);
    for (i = 1; i < pathSize - 1; i++) {
        newDir = atanMP(mpPath[i].b - mpPath[i - 1].b, mpPath[i].a - mpPath[i - 1].a);
        if (mpPath[i].dir != curDir) {
            rpPath[length] = MPtoRP(mpPath[i - 1]);
            length++;
            curDir = newDir;
        }
    }

    rpPath[0].alpha = computeSegAngle(rpPath[0], rpPath[1]);

    rpPath[length].x = rpEnd.x;
    rpPath[length].y = rpEnd.y;
    rpPath[length].alpha = rpEnd.alpha;

    rpPath[length - 1].alpha = computeSegAngle(rpPath[length - 1], rpPath[length]);

    return (length);
}

propIsObstacleType trajIsObstacleInMap(obstacleType obstacle){
    mapPosType mpPoint;

    absolutePosType tmp;
    tmp.x = obstacle.x;
    tmp.y = obstacle.y;
    mpPoint = RPtoMP(tmp);


    if ((dkNodes[20 * mpPoint.a + mpPoint.b].done == OBST || 30 < mpPoint.a) || 20 < mpPoint.b) {
        return (PROP_IS_UNMOVABLE_OBSTACLE);
    } else if (dkNodes[20 * mpPoint.a + mpPoint.b].done == MOVE_OBST){
        return (PROP_IS_MOVABLE_OBSTACLE);
    } else {
        return (PROP_IS_NO_OBSTACLE);
    }

}




int findTrajectoire(absolutePosType rpStart, absolutePosType rpEnd, absolutePosType rpPath[]) {
    mapPosType mpStart, mpEnd;
    mapPosType mpPath[200];
    int trajLength;



    if ((rpStart.x < 0) || (rpStart.x > 3.0) || (rpStart.y < 0) || (rpStart.y > 2.0)) {
        return 250;
    } else if ((rpEnd.x < 0) || (rpEnd.x > 3.0) || (rpEnd.y < 0) || (rpEnd.y > 2.0)) {
        return 251;
    }
    if ((rpStart.x == rpEnd.x) && (rpStart.y == rpEnd.y)) {
        return (0);
    }

    mpStart = RPtoMP(rpStart);
    mpEnd = RPtoMP(rpEnd);
    trajLength = findPath(mpStart, mpEnd, mpPath);
    if (250 > trajLength && trajLength > 1 ) {
        trajLength = convertPath(rpStart, rpEnd, trajLength, mpPath, rpPath);
    }


    return trajLength;
}
