# 1 "globals.c"
# 1 "C:\\Users\\DenisT\\Desktop\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\PropBLDC.X//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "globals.c"
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
# 2 "globals.c" 2


inline float satureAngle(float angle) {
 while (angle > (3.14159)) angle -= 2*(3.14159);
 while (angle < -(3.14159)) angle += 2*(3.14159);
 return(angle);
}
