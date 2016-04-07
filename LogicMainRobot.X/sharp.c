/**
 * @file sharp.c
 * @author bULBot 2011-2012
 * @brief Implémentation des fonctions de contrôle des capteurs sharp.
 */


#include "../libdspic/adc.h"
#include "gestionPropulsion.h"
#include "sharp.h"
#include <math.h>
#include "globals.h"

//#define DEG2RAD(x) (x*(PI/1800))


detectionSharpType detectionObstacleSharp() {
    int sharpMes;
    detectionSharpType detectionSharpTest;
    positionInteger curPos;
    
	sharpMes = conversionADC(INPUT_SHARP_AVANT);
	if (sharpMes > SEUIL_COLLISION_AVANT) {
            detectionSharpTest.isObstacleDetected = 1;
            curPos = propulsionGetPosition();
            detectionSharpTest.obstacleInfo.x = (float)curPos.x + (float)(cos((curPos.alpha*PI)/1800.0)*DISTANCE_OBSTACLE_AVANT);
            detectionSharpTest.obstacleInfo.y = (float)curPos.y + (float)(sin((curPos.alpha*PI)/1800.0)*DISTANCE_OBSTACLE_AVANT);// on centre l'obstacle
            
    } else if(sharpMes < SEUIL_COLLISION_AVANT-HYSTERESE_AVANT) {
		detectionSharpTest.isObstacleDetected = 0;
    }
    return (detectionSharpTest);
}
