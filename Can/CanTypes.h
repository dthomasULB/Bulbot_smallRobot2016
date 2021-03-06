/* 
 * File:   CanTypes.h
 * Author: Yernaux
 *
 * Created on 23 mars 2014, 11:50
 */

#ifndef CANTYPES_H
#define	CANTYPES_H

/**
 * @brief D�finition de la structure de donn�es pour le codage d'une position absolue sur le bus CAN
 */
typedef struct {
    int x; /** Position en X, en mm */
    int y; /** Position en Y, en mm */
    int alpha; /** Orientation par rapport � l'axe X dans le sens trigonom�trique, en deg/10 */
} positionInteger;

/**
 * @brief D�finition de la structure de donn�es pour le codage d'une position[vitesse] relative sur le bus CAN
 */
typedef struct {
    int l; /** Position[vitesse] logitudinale, en mm[mm/s] */
    int r; /** Position[vitesse] angulaire, en deg/10[(deg/10)/s] */
} relativeCoordInteger;


#define	NO_LENGTH	0
#define	START_OUT	250
#define	END_OUT		251
#define	START_OBST	252
#define	END_OBST	253
#define	NO_WAY		254

/**
 * @brief D�finition des �tats possibles du statut la propulsion
 */
typedef enum {
    DISABLED = 0,
    STANDING = 1,
    RELATIVE_MOVE = 2,
    TRAJECTORY = 3,
    TEST = 4,
    TRAJ_START_OUT = START_OUT,
    TRAJ_END_OUT = END_OUT,
    TRAJ_START_OBS = START_OBST,
    TRAJ_END_OBS = END_OBST,
    TRAJ_NO_WAY = NO_WAY
} propStateType;

typedef enum {
    PROP_IS_NO_OBSTACLE = 0,
    PROP_IS_UNMOVABLE_OBSTACLE = 1,
    PROP_IS_MOVABLE_OBSTACLE = 2
} propIsObstacleType;

typedef struct {
	float x;      // abscisse du coin inf�rieur gauche du carr�
	float y;      // ordonn�e du coin inf�rieur gauche du carr�
    float size;   // longueur du c�t� du carr�
} obstacleType;




#endif	/* CANTYPES_H */

