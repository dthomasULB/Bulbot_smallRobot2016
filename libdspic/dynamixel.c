/**
 * @file dynamixel.c
 * @brief Librairie de communication avec les Dynamixel sur dsPIC33F.
 * @author Olivier Desenfans (version 2014: Yernaux Florence)
 * @author bULBot 2011-2012-2014
 */

// Include

#include "dynamixel.h"
#include "math.h"
#include "../libdspic/messagesDynamixel.h"
#include "../libdspic/timers.h"
#include "../libdspic/uart.h"
#include "../libdspic/pps.h"
#include <xc.h>
#include "../libdspic/clock.h"
#include <libpic30.h>

/****************************************************************************/
/*  DEFINES                                                                 */
/****************************************************************************/
#define ABS(x) ((x) < 0 ? - (x) : (x))
#define MUTE    0x01
#define TALKING 0x00

/****************************************************************************/
/*  VARIABLES GLOBALES                                                      */
/****************************************************************************/
int count_renvoi = 0;
unsigned int prDynUartCh = 0;     //!< Canal UART utilisé pour le bus Dynamixel
unsigned int prDynTimerId = 0;    //!< Timer utilisé pour gérer les timeout


/****************************************************************************/
/*  DECLARATION DES FONCTIONS PRIVEES                                       */
/****************************************************************************/
/**
 * @brief Calcul de checksum pour les messages Dynamixel.
 * @param[in] msg Message dont il faut calculer le checksum.
 * @returns chk Valeur du checksum.
 * @note La méthode de calcul est directement tirée de la datasheet des Dynamixel.
 * s'y référer pour plus d'informations.
 */
unsigned char prDynaChecksum(unsigned char* msg);
void prDynaReadData(dynamixelType *dyna, unsigned char address, unsigned char length, unsigned char* data);
void prDynaWriteData(dynamixelType *dyna, unsigned char address, unsigned char length, unsigned char* data);

/****************************************************************************/
/*  DEFINITION DES FONCTIONS                                                */
/****************************************************************************/
void dynaConfigBus(int uartCh, float baudrate, int timerId) {
    DIRECTION = 1;
    DIRECTION_TRIS = 0;
    uartConfig(uartCh, baudrate, UART_8N1_NO_HANDSHAKE);
    prDynUartCh = uartCh;
    timerSetup(timerId, 2);     // configure un timer à 2ms pour les timeout
    prDynTimerId = timerId;
}


void dynaConfigMot(dynamixelType *dyna, unsigned char id) {
    dyna->id = id;
    dyna->status = OPERATIONNEL;    // A tester avec un PING?
    dyna->error = 0;                // pas d'erreur (idem ci-dessus ?)
    if (id == ID_BROADCAST) {
        dyna->responding = MUTE;
    } else {
        dyna->responding = TALKING;
    }
}

void dynaChangeBaudrate(dynamixelType *dyna, unsigned char baudrate) {
    prDynaWriteData(dyna, P_BAUD_RATE, 1, &baudrate);
}

float dynReadPresentPosition(dynamixelType *dyna) {
    int data;

    prDynaReadData(dyna, P_PRESENT_POSITION_L, 2, (unsigned char*)&data);
    if (dyna->status == DEFAILLANT){
       return(-1);
    } else {
        return((300.0/1023)*data);
    }
}

int dynaReadTorqueEnable(dynamixelType *dyna) {
    unsigned char data;
    
    prDynaReadData(dyna, P_TORQUE_ENABLE, 1, &data);
    if (dyna->status == DEFAILLANT){
        data = 0xFF;
    }
    return(data); // =1 si le couple est actif, =0 sinon,  =0xFF si erreur!
}

void dynaTorqueEnable(dynamixelType *dyna) {
    unsigned char data = 1;
    
    prDynaWriteData(dyna, P_TORQUE_ENABLE, 1, &data);
}

void dynaTorqueDisable(dynamixelType *dyna) {
    unsigned char data = 0;
    
    prDynaWriteData(dyna, P_TORQUE_ENABLE, 1, &data);
}

int dynaReadTorqueLimit(dynamixelType *dyna) {
    unsigned int data;
    
    prDynaReadData(dyna, P_TORQUE_LIMIT_L, 2, (unsigned char*)&data);
    if (dyna->status == DEFAILLANT){
        data = 0xFFFF;
    }
    return(data); // =1 si le couple est actif, =0 sinon,  =0xFFFF si erreur!
}

int dynaReadCwAngleLimit(dynamixelType *dyna) {
    unsigned int data;
    
    prDynaReadData(dyna, P_CW_ANGLE_LIMIT_L, 2, (unsigned char*)&data);
    if (dyna->status == DEFAILLANT){
        data = 0xFFFF;
    }
    return(data); // =1 si le couple est actif, =0 sinon,  =0xFFFF si erreur!
}

int dynaReadCcwAngleLimit(dynamixelType *dyna) {
    unsigned int data;
    
    prDynaReadData(dyna, P_CCW_ANGLE_LIMIT_L, 2, (unsigned char*)&data);
    if (dyna->status == DEFAILLANT){
        data = 0xFFFF;
    }
    return(data); // =1 si le couple est actif, =0 sinon,  =0xFFFF si erreur!
}

void dynaSetCwAngleLimit(dynamixelType *dyna, unsigned int cwAngleLimit) {
    prDynaWriteData(dyna, P_CW_ANGLE_LIMIT_L, 2, (unsigned char*)&cwAngleLimit);
}

void dynaSetCcwAngleLimit(dynamixelType *dyna, unsigned int ccwAngleLimit) {
    prDynaWriteData(dyna, P_CCW_ANGLE_LIMIT_L, 2, (unsigned char*)&ccwAngleLimit);
}

void dynaLedOn(dynamixelType *dyna) {
    unsigned char data = 1;
    
    prDynaWriteData(dyna, P_LED, 1, &data);
}

void dynaLedOff(dynamixelType *dyna) {
    unsigned char data = 0;
    
    prDynaWriteData(dyna, P_LED, 1, &data);
}

void dynaSetGoalPosition(dynamixelType *dyna, float angle) {
    int goal;
    
    goal = 1023*angle/300;
    if (goal > 1023) {                          // saturation de l'angle à ses valeurs max/min
        goal = 1023;                            // goal=0 => 0°, goal=1023 => 300°
    } else if (goal < 0) {
        goal = 0;
    }
    prDynaWriteData(dyna, P_GOAL_POSITION_L, 2, (unsigned char*)&goal);
}

int dynaIsMoving(dynamixelType *dyna) {
    unsigned char data;
    
    prDynaReadData(dyna, P_MOVING, 1, &data);
    if (dyna->status == DEFAILLANT){
        data = 0xFF;
    }
    return(data); // =0x01 si en mouvement, =0x00 sinon :) = 0xFF si erreur!
}

void dynaStartEndlessTurn(dynamixelType *dyna) {
    unsigned int data[2] = {0,0};
    
    prDynaWriteData(dyna, P_CW_ANGLE_LIMIT_L, 4, (unsigned char*)data);
}

void dynaStopEndlessTurn(dynamixelType *dyna) {
     unsigned int data[2] = {0,1023};
    
    prDynaWriteData(dyna, P_CW_ANGLE_LIMIT_L, 4, (unsigned char*)data);
}

void dynaSetGoalSpeed(dynamixelType *dyna, int speed) {
    if (speed > 1023) {
        speed = 1023;
    } else if (speed < -1023) {
        speed = -1023;
    }
    if (speed < 0) {
        speed = 1024-speed;
    }
    prDynaWriteData(dyna, P_GOAL_SPEED_L, 2, (unsigned char*)&speed);
}

//void changeID(unsigned char nouvelleID, dynamixelType *dyna) {
//    unsigned char trameRecue[6];
//    dynamixelRxInfoType info;
//    unsigned char msg1[8] = {0xFF, 0xFF, dyna->id, 0x04, INST_WRITE, P_ID, nouvelleID, 0x00};
//    msg1[7] = checksum(msg1); // Calcul du checksum
//    unsigned char msg2[8] = {0xFF, 0xFF, nouvelleID, 0x04, INST_WRITE, P_ID, nouvelleID, 0x00};
//    msg2[7] = checksum(msg2); // Calcul de la checksum
//
//    // Remplissage de la trame
//    count_renvoi = 1;
//    while ((count_renvoi != 0) && (count_renvoi < NBRE_RENVOIS_MAX)) {
//        if (count_renvoi % 2 == 0) {
//            envoiMessageDynamixel(msg2);    // Envoi du message sur le nouvel ID (si erreur de reception mais que l'ordre a bien été envoyé)
//        } else {                            // count impair -> passe ici la 1ere fois
//            envoiMessageDynamixel(msg1);    // Envoi du message
//        }
//        if ((dyna->responding) == (TALKING)) { // si le dynamixel est censé répondre
//            info = receptionMessageDynamixel(trameRecue, 6);
//            CheckResend(info, dyna); // mets le count_renvoi à 0 si bonne reception et compréhension du message   
//        } else {
//            count_renvoi = 0;
//        }
//    }
//    if (count_renvoi >= NBRE_RENVOIS_MAX) { // pas de reaction après certain nombre de renvoi, on le considère comme mort
//        dyna->statut |= DEFAILLANT;
//    } else {
//        dyna->id = nouvelleID;
//    }
//}


//void initID(unsigned char nouvelleID, dynamixelType *dyna) {
//    unsigned char change;
//
//    dyna->id = ID_BROADCAST;
//    change = 0;
//    if (dyna->responding == TALKING) {
//        dyna->responding = MUTE;
//        change = 1;
//    }
//    changeID(nouvelleID, dyna);
//    if (change == 1) {
//        dyna->responding = TALKING;
//    }
//}
//
//
//
//
//
//
//unsigned char StatusCompute(dynamixelRxInfoType info) {
//    unsigned char statut;
//    
//    statut = 0;
//    if (info.statusChar & 0x04) {
//        statut |= OVERHEAT;
//    }// Surchauffe
//    if (info.statusChar & 0x20) {
//        statut |= BLOQUE;
//    } // pince bloquée
//    if (info.statusChar & 0x01) {
//        statut |= VOLTAGE_ERR;
//    } // voltage trop important
//    if (info.statusChar & 0x10) {
//        statut |= MESSAGE_ERR;
//    } // message reçu par le dynamixcel est  corrompu (checksum error) // a renvoyer
//    if (info.statusChar & 0x4A) {
//        statut |= WRONG_MESSAGE;
//    }// message reçu par le dynamixcel est erroné  (mauvaise instruction, out out of range)
//    if (info.statusChar & 0x0) {
//        statut = OPERATIONNEL;
//    }
//    return (statut);
//}
//
//
//void rotationSyncDynamixel(int goal[NBRE_DYNAMIXEL_MAX], unsigned char id[NBRE_DYNAMIXEL_MAX], int number, dynamixelType *dyna) {
//    unsigned char goalL[NBRE_DYNAMIXEL_MAX], goalH[NBRE_DYNAMIXEL_MAX];
//    unsigned char length, incr;
//    int tmp;
//
//    if (number > NBRE_DYNAMIXEL_MAX) {
//        number = NBRE_DYNAMIXEL_MAX;
//    }
//    if (number > 0) {
//        // Séparation des consignes en deux octets
//        for (incr = 0; incr < number; incr++) {
//            if (incr < number) {
//                goalL[incr] = (unsigned char) (int) (goal[incr] % 256);
//                goalH[incr] = (unsigned char) (int) (goal[incr] / 256);
//            } else {
//                goalL[incr] = 0;
//                goalH[incr] = 0;
//            }
//        }
//        tmp = 3 * number + 8;
//        length = 3 * number + 4;
//
//        unsigned char msg2[14] = {0xFF, 0xFF, ID_BROADCAST, 0xA, INST_SYNC_WRITE, P_GOAL_POSITION_L, 0x02, id[0], goalL[0], goalH[0], id[1], goalL[1], goalH[1], 0x00};
//        unsigned char msg3[17] = {0xFF, 0xFF, ID_BROADCAST, 0xD, INST_SYNC_WRITE, P_GOAL_POSITION_L, 0x02, id[0], goalL[0], goalH[0], id[1], goalL[1], goalH[1], id[2], goalL[2], goalH[2], 0x00};
//        unsigned char msg4[20] = {0xFF, 0xFF, ID_BROADCAST, 0x10, INST_SYNC_WRITE, P_GOAL_POSITION_L, 0x02, id[0], goalL[0], goalH[0], id[1], goalL[1], goalH[1], id[2], goalL[2], goalH[2], id[3], goalL[3], goalH[3], 0x00};
//        unsigned char msg5[23] = {0xFF, 0xFF, ID_BROADCAST, 0x13, INST_SYNC_WRITE, P_GOAL_POSITION_L, 0x02, id[0], goalL[0], goalH[0], id[1], goalL[1], goalH[1], id[2], goalL[2], goalH[2], id[3], goalL[3], goalH[3], id[4], goalL[4], goalH[4], 0x00};
//
//        switch (number) {
//            case 2:
//                msg2[13] = checksum(msg2);
//                envoiMessageDynamixel(msg2);
//                break;
//            case 3:
//                msg3[16] = checksum(msg3);
//                envoiMessageDynamixel(msg3);
//                break;
//            case 4:
//                msg4[19] = checksum(msg4);
//                envoiMessageDynamixel(msg4);
//                break;
//            case 5:
//                msg5[22] = checksum(msg5);
//                envoiMessageDynamixel(msg5);
//                break;
//            default:
//                // ERREUR !!!
//                break;
//        }
//    }
//
//}
//
//
//int activePaquetStatut(dynamixelType *dyna) {
//    int count = 1;
//    unsigned char state;
//
//    state = lectureRenvoiPaquet(dyna);
//    if (state == 0x02) {            // si renvoie son statut
//        dyna->responding = TALKING;
//        return (1);
//    } else if (state == 0xFF) {            // si dynamixel défaillant
//        dyna->statut = DEFAILLANT;
//        return (0);
//    } else {
//        // Remplissage de la trame
//        unsigned char msg[8] = {0xFF, 0xFF, dyna->id, 0x04, INST_WRITE, P_RETURN_LEVEL, 0x02, 0x00};
//        // {0xFF, 0xFF, id, 0x04, INST_WRITE, P_RETURN_LEVEL, A, 0x00};
//        // A=0x00 : aucune réponse
//        // A=0x01: repond uniquement au READ_DATA (spamme pas la ligne)
//        // A=0x02 : réponds à toutes les instructions
//        msg[7] = checksum(msg);         // Calcul du checksum
//        envoiMessageDynamixel(msg);     // Envoi du message
//        while ((state != 0x02) && (count < 50)) {
//            state = lectureRenvoiPaquet(dyna);
//            envoiMessageDynamixel(msg); // Envoi du message
//            count += 1;
//        }
//        if (count >= NBRE_RENVOIS_MAX) {
//            dyna->statut &= DEFAILLANT; // pas de reaction après certain nombre de renvoi, on le considère comme mort
//            return (0);
//        }// erreur
//        else {
//            dyna->responding = TALKING;
//            return (1);
//        } // opération réussie
//    }
//}
//
//
//int desactivePaquetStatut(dynamixelType *dyna) {
//    int count = 1;
//    unsigned char state;
//
//    state = lectureRenvoiPaquet(dyna);
//    if (state == 0x01) {            // si renvoie son statut
//        dyna->responding = MUTE;
//        return (1);
//    } else if (state == 0xFF) {     // si dynamixel défaillant
//        dyna->statut = DEFAILLANT;
//        return (0);
//    } else {
//        // Remplissage de la trame
//        unsigned char msg[8] = {0xFF, 0xFF, dyna->id, 0x04, INST_WRITE, P_RETURN_LEVEL, 0x01, 0x00};
//        // {0xFF, 0xFF, id, 0x04, INST_WRITE, P_RETURN_LEVEL, A, 0x00};
//        // A=0x00 : aucune réponse
//        // A=0x01: repond uniquement au READ_DATA (spamme pas la ligne)
//        // A=0x02 : réponds à toutes les instructions
//        msg[7] = checksum(msg);                     // Calcul du checksum
//        envoiMessageDynamixel(msg);                 // Envoi du message
//        while ((state != 0x01) && (count < 50)) {
//            state = lectureRenvoiPaquet(dyna);
//            envoiMessageDynamixel(msg); // Envoi du message
//            count += 1;
//        }
//        if (count > 50) {
//            dyna->statut |= DEFAILLANT; // pas de reaction après certain nombre de renvoi, on le considère comme mort
//            return (0);
//        } else {
//            dyna->responding = MUTE;
//            return (1);
//        }
//    }
//}
//
//
//
//
//unsigned char lectureRenvoiPaquet(dynamixelType *dyna) {
//    unsigned char trameRecue[7];
//    dynamixelRxInfoType info;
//    
//    count_renvoi = 1;
//    // Remplissage de la trame
//    unsigned char msg[8] = {0xFF, 0xFF, dyna->id, 0x04, INST_READ, P_RETURN_LEVEL, 0x01, 0x00};
//    msg[7] = checksum(msg);         // Calcul du checksum
//    while ((count_renvoi != 0) && (count_renvoi < NBRE_RENVOIS_MAX)) {
//        envoiMessageDynamixel(msg); // Envoi du message
//        // le dynamixel est toujours censé répondre à cet ordre
//        info = receptionMessageDynamixel(trameRecue, 7);
//        CheckResend(info, dyna); // mets le count_renvoi à 0 si bonne reception et compréhension du message
//    }
//    if (count_renvoi >= NBRE_RENVOIS_MAX) {
//        dyna->statut |= DEFAILLANT; // pas de reaction après certain nombre de renvoi, on le considère comme mort
//        return (0xFF);
//    }
//    // sinon, la trameRecue est fiable
//    return trameRecue[5]; // = 0x00, 0x01 ou 0x02
//}
//
//
//void AlarmLedOn(unsigned char statut, dynamixelType *dyna) {
//    unsigned char trameRecue[6];
//    dynamixelRxInfoType info;
//    unsigned char alarm = 0;
//    
//    if (statut & BLOQUE) {  // raisons pour faire blinker la led
//        alarm += 0x20;
//    }
//    if (statut & OVERHEAT) {
//        alarm += 0x04;
//    }
//    if (statut & VOLTAGE_ERR) {
//        alarm += 0x01;
//    }
//    if (statut & MESSAGE_ERR) {
//        alarm += 0x10;
//    }
//    if (statut & WRONG_MESSAGE) {
//        alarm += 0x4A;
//    }
//    count_renvoi = 1;
//    unsigned char msg[8] = {0xFF, 0xFF, dyna->id, 0x04, INST_WRITE, P_ALARM_LED, alarm, 0x00};
//    msg[7] = checksum(msg); // Calcul du checksum
//    while ((count_renvoi != 0) && (count_renvoi < NBRE_RENVOIS_MAX)) {
//        envoiMessageDynamixel(msg); // Envoi du message
//        if (dyna->responding == TALKING) { // si le dynamixel est censé répondre
//            info = receptionMessageDynamixel(trameRecue, 6);
//            CheckResend(info, dyna); // mets le count_renvoi à 0 si bonne reception et compréhension du message
//        } else {
//            count_renvoi = 0;
//        }
//    }
//    if (count_renvoi >= NBRE_RENVOIS_MAX) {
//        dyna->statut |= DEFAILLANT;
//    } // pas de reaction après certain nombre de renvoi, on le considère comme mort
//}
//
//
//void AlarmLedOff(dynamixelType *dyna) {
//    unsigned char trameRecue[6];
//    dynamixelRxInfoType info;
//    unsigned char msg[8] = {0xFF, 0xFF, dyna->id, 0x04, INST_WRITE, P_ALARM_LED, 0x00, 0x00};
//
//    count_renvoi = 1;
//    msg[7] = checksum(msg); // Calcul de la checksum
//    while ((count_renvoi != 0) && (count_renvoi < NBRE_RENVOIS_MAX)) {
//        envoiMessageDynamixel(msg); // Envoi du message
//        if (dyna->responding == TALKING) { // si le dynamixel est censé répondre
//            info = receptionMessageDynamixel(trameRecue, 6);
//            CheckResend(info, dyna); // mets le count_renvoi à 0 si bonne reception et compréhension du message
//        } else {
//            count_renvoi = 0;
//        }
//    }
//    if (count_renvoi >= NBRE_RENVOIS_MAX) {
//        dyna->statut |= DEFAILLANT;
//    } // pas de reaction après certain nombre de renvoi, on le considère comme mort
//}
//
//
//void ResetValues(dynamixelType *dyna) {
//    unsigned char trameRecue[6];
//    dynamixelRxInfoType info;
//    unsigned char msg[6] = {0xFF, 0xFF, dyna->id, 0x02, INST_RESET, 0x00};
//
//    count_renvoi = 1;
//    msg[5] = checksum(msg); // Calcul de la checksum
//    while ((count_renvoi != 0) && (count_renvoi < NBRE_RENVOIS_MAX)) {
//        envoiMessageDynamixel(msg); // Envoi du message
//        if (dyna->responding == TALKING) { // si le dynamixel est censé répondre
//            info = receptionMessageDynamixel(trameRecue, 6);
//            CheckResend(info, dyna); // mets le count_renvoi à 0 si bonne reception et compréhension du message
//        } else {
//            count_renvoi = 0;
//        }
//    }
//    if (count_renvoi >= NBRE_RENVOIS_MAX) {
//        dyna->statut |= DEFAILLANT;
//    } // pas de reaction après certain nombre de renvoi, on le considère comme mort
//}
//
//
//
//

//
//

//
//
//int StepTurn(dynamixelType *dyna, int speed, int stop[], int len, int number, int sens) {
//    int blocage = 0, repeat = 0; //torque;
//    int a[100], i, pos, index = 0, old;
//    int l = 0;
//
//    pos = lecturePositionDynamixel(dyna);
//    switch (sens) {
//        case 1: // sens clockwise EL->DY
//            for (i = 0; i < len; i++) {
//                if ((ABS(pos - stop[index])) > (ABS(pos - stop[i]))) {
//                    index = i;
//                }
//            }
//            index = index + 1;
//            if (index > (len - 1)) {
//                index = 0;
//            }
//            StartEndlessTurn(dyna);
//            __delay_ms(1000);
//            SetGoalSpeed(dyna, speed, sens);
//            i = 0;
//            while (i < number && (blocage == 0) && (dyna->statut == OPERATIONNEL)) {
//                old = pos;
//                pos = lecturePositionDynamixel(dyna);
//                if (ABS(pos - old) < 10) {
//                    repeat += 1;
//                } else {
//                    repeat = 0;
//                }
//                if (repeat > 10000) {
//                    blocage = 1;
//                    //ledOn(dyna);
//                }
//                a[l] = pos;
//                l = +1;
//                //stop[index];
//                if ((index == 0) && (pos > 400)) {
//                    while (pos != 0 && (dyna->statut == OPERATIONNEL)) {
//                        pos = lecturePositionDynamixel(dyna);
//                    }
//                }
//                if (pos > stop[index]) {
//                    //SetGoalSpeed(dyna,0,sens);
//                    //__delay_ms(5);
//                    //SetGoalSpeed(dyna,speed,sens);
//                    index += 1;
//                    i += 1;
//                    if (index > (len - 1)) {
//                        index = 0;
//                    }
//                }
//            }
//            SetGoalSpeed(dyna, 0, sens);
//            break;
//        case 0: // sens counterclockwise DY->EL
//            for (i = 0; i < len; i++) {
//                if ((ABS(pos - stop[index])) > (ABS(pos - stop[i]))) {
//                    index = i;
//                }
//            }
//            index = index - 1;
//            if (index < 0) {
//                index = (len - 1);
//            }
//            StartEndlessTurn(dyna);
//            __delay_ms(1000);
//            SetGoalSpeed(dyna, speed, sens);
//            i = 0;
//            while (i < number && (blocage == 0)&& (dyna->statut == OPERATIONNEL)) {
//                old = pos;
//                pos = lecturePositionDynamixel(dyna);
//                if (ABS(pos - old) < 10) {
//                    repeat += 1;
//                } else {
//                    repeat = 0;
//                }
//                //torque=lectureTorqueDynamixel(dyna);
//                if (repeat > 10000) {
//                    blocage = 1;
//                    //ledOn(dyna);
//                }
//                //a[0]=stop[index];
//                if ((index == (len - 1)) && (pos < 800)) {
//                    while (pos != 1023 && (dyna->statut == OPERATIONNEL)) {
//                        pos = lecturePositionDynamixel(dyna);
//                    }
//                }
//                if (pos < stop[index]) {
//                    //SetGoalSpeed(dyna,0,sens);
//                    //__delay_ms(5);
//                    //SetGoalSpeed(dyna,speed,sens);
//                    index = index - 1;
//                    i += 1;
//                    if (index < 0) {
//                        index = len - 1;
//                    }
//                }
//            }
//            SetGoalSpeed(dyna, 0, sens);
//            break;
//        default:
//            break;
//
//    }
//    return (!blocage); // return 1 si sucess et 0 si arrêté à cause d'un blocage
//}
//
//
//int lectureTorqueDynamixel(dynamixelType *dyna) {
//    int torque;
//    dynamixelRxInfoType info;
//    unsigned char trameRecue[8];
//    // Remplissage de la trame
//    unsigned char msg[8] = {0xFF, 0xFF, dyna->id, 0x04, INST_READ, P_PRESENT_LOAD_L, 0x02, 0x00};
//
//    count_renvoi = 1;
//    msg[7] = checksum(msg); // Calcul de la checksum
//    while ((count_renvoi != 0) && (count_renvoi < NBRE_RENVOIS_MAX)) {
//        envoiMessageDynamixel(msg);
//        info = receptionMessageDynamixel(trameRecue, 8);
//        CheckResend(info, dyna); // mets le count_renvoi à 0 si bonne reception et compréhension du message, update status du dynamixel
//    }
//    if (count_renvoi >= NBRE_RENVOIS_MAX) {     // pas de reaction après certain nombre de renvoi, on le considère comme mort
//        dyna->statut |= DEFAILLANT;
//        torque = 9999;
//    } else { // recombine les 2 bytes recus : Present Position(L) et Present(H)
//        torque = (int) (trameRecue[6] << 8) + (int) (trameRecue[5]);
//        if (torque >= 1024) {
//            torque -= 1024;
//        }
//    }
//    /* Dans le dynamixel, torque = (2^10)* sens + load */
//    return (torque);
//}
//
//
//int StepOver(dynamixelType *dyna, int speed, int number, int sens) {
//    int blocage = 0; //torque;
//    int pos, old;
//    int darkZone = 0;
//    int count_turn = 0;
//
//    switch (sens) {
//        case 1: // sens positif
//            StartEndlessTurn(dyna);
//            __delay_ms(500);
//            SetGoalSpeed(dyna, speed, sens);
//            while ((count_turn < number) && (blocage == 0)&& (dyna->statut == OPERATIONNEL)) {
//                old = pos;
//                pos = lecturePositionDynamixel(dyna);
//                // TEST POUR DETECTER BLOCAGE
//                /*
//                if(ABS(pos-old)<10)
//                {repeat+=1;}
//                else
//                {repeat=0;}
//                if(repeat>10000)
//                {blocage=1;}
//                 */
//                if (pos > 1000) {   // Detection de l'entrée en zone noire pour le dynamixel (entre 300 et 360°)
//                    darkZone = 1;
//                }
//                if ((darkZone == 1) && (pos > 400)) {
//                    while (pos != 0 && (dyna->statut == OPERATIONNEL)) {    // attends la sortie de la zone noire
//                        pos = lecturePositionDynamixel(dyna);
//                    }
//                }
//                if ((darkZone == 1) && (pos > 3)) {
//                    count_turn += 1;
//                    darkZone = 0; // fin de la zone noire détectée
//                }
//            }
//            SetGoalSpeed(dyna, 0, sens);
//            break;
//        case 0: // sens négatif
//            StartEndlessTurn(dyna);
//            __delay_ms(500);
//            SetGoalSpeed(dyna, speed, sens);
//            while ((count_turn < number) &&(blocage == 0)&& (dyna->statut == OPERATIONNEL)) {
//                old = pos;
//                pos = lecturePositionDynamixel(dyna);
//                // TEST POUR DETECTER BLOCAGE
//                //if(ABS(pos-old)<10)
//                //{repeat+=1;}
//                //else
//                //{repeat=0;}
//                //if(repeat>10000)
//                //{blocage=1;}
//                if (pos < 5) {  // Detection de l'entrée en zone noire pour le dynamixel (entre 300 et 360°)
//                    darkZone = 1;
//                }
//                if ((darkZone == 1) &&(pos < 800)) {
//                    while (pos != 1023 && (dyna->statut == OPERATIONNEL)) {
//                        pos = lecturePositionDynamixel(dyna);
//                    }
//                }
//                if ((darkZone == 1) && (pos < 1020)) {
//                    count_turn += 1;
//                    darkZone = 0; // fin de la zone noire détectée
//                }
//            }
//            SetGoalSpeed(dyna, 0, sens);
//            break;
//        default:
//            break;
//    }
//    return (!blocage); // return 1 si sucess et 0 si arrêté à cause d'un blocage ou si dynamixel défaillant
//}
//
//
//void rotationDynamixelDegre(int degre, dynamixelType *dyna) {
//    int goal;
//    unsigned char posL, posH;
//    unsigned char trameRecue[6];
//    dynamixelRxInfoType info;
//
//    goal = AngleToReg(degre);
//    if (goal > 1023) {
//        goal = 1023;
//    } else if (goal < 0) {
//        goal = 0;
//    } // verif pour être surs qu'on ne dépasse pas les valeurs d'angle min
//    // SÈparation de la consigne en deux octets
//    posL = (unsigned char) ((int) goal % 256);
//    posH = (unsigned char) ((int) goal / 256);
//    count_renvoi = 1;
//    // Remplissage de la trame
//    unsigned char msg[9] = {0xFF, 0xFF, dyna->id, 0x05, INST_WRITE, P_GOAL_POSITION_L, posL, posH, 0x00};
//    // Commence à écrire posL à l'adresse P_GOAL_POSITION_L puis écris posH à l'adresse suivante (P_GOAL_POSITION_H)
//    msg[8] = checksum(msg); // Calcul de la checksum
//    while ((count_renvoi != 0) && (count_renvoi < NBRE_RENVOIS_MAX)) {
//        envoiMessageDynamixel(msg); // Envoi du message
//        if (dyna->responding == TALKING) { // si le dynamixel est censé répondre
//            info = receptionMessageDynamixel(trameRecue, 6);
//            CheckResend(info, dyna); // mets le count_renvoi à 0 si bonne reception et compréhension du message
//        } else {
//            count_renvoi = 0;
//        }
//    }
//    if (count_renvoi >= NBRE_RENVOIS_MAX) {
//        dyna->statut |= DEFAILLANT;
//    }// pas de reaction après certain nombre de renvoi, on le considère comme mort
//}
//
//
//void InitDynamixel(dynamixelType *dyna, int pos) {
//    torqueEnable(dyna);
//    SetGoalSpeed(dyna, 0, 1);
//    StopEndlessTurn(dyna);
//    if (pos >= 0) {
//        rotationDynamixel(pos, dyna);
//    }
//}
//
//int AngleToReg(int angle) {
//    float tmp = 0;
//    int reg;
//    tmp = (float) (angle)*(float) (1023) / (float) (300);
//    reg = ceil(tmp - 0.5);
//    return (reg);
//}
//
//int RegtoAngle(int reg) {
//    float tmp = 0;
//    int angle;
//    tmp = (float) (reg)*(float) (300) / (float) (1023);
//    angle = ceil(tmp - 0.5);
//    return (angle);
//}
//
//void Turn360(dynamixelType dyna, int speed, int sens) {
//    int z = 0;
//    int stop[2] = {341, 954}; // pas de 180
//    int count = 0;
//    // Pour des tours de :
//    //int stop[len]={80, 695};
//    //int stop[len]={341, 954}; // pas de 180
//    //int stop[len]={34, 341, 647, 954}; // pas de 90
//    //int stop[len]={3, 204, 409, 613, 818, 1010}; // pas de 60
//
//    if (speed > 1023) speed = 1023;
//    if (speed < 0) speed = 0;
//    while (z == 0 && count < 3) {
//        z = StepTurn(&dyna, speed, stop, 2, 2, sens);
//        count += 1;
//    }
//}


/****************************************************************************/
/*  DEFINITION DES FONCTIONS PRIVEES                                        */
/****************************************************************************/
unsigned char prDynaChecksum(unsigned char* msg) {
    unsigned char chk = 0, i, tmp;

    tmp = 3 + msg[3];
    for (i=2; i<tmp; i++) {
        chk += msg[i];
    }
    chk = ~chk;     // bitwise NOT
    return (chk);
}


int prDynaCheckStatusPacket(dynamixelType *dyna, unsigned char* msg) {
    int success = 1;
    
    if ((msg[0] != 0xFF) || (msg[1] != 0xFF)) {         // vérification des 2 1er octets du préambule
        success = 0;
        dyna->status = ERR_ACQUITTEMENT;
    } else if (msg[2] != dyna->id) {                    // Vérification de l'ID du message
        success = 0;
        dyna->status = ERR_ACQUITTEMENT;
    } else if (msg[msg[3]+3] != prDynaChecksum(msg)) {  // Vérification du checksum
        success = 0;
        dyna->status = ERR_ACQUITTEMENT;
    } else {
        dyna->error = msg[4];                           // La trame est correcte, on récupère l'octet d'erreurs
        if (msg[4] & 0x10) {
            success = 0;                                // Le dynamixel a détecté une erreur de checksum
            dyna->status = ERR_MESSAGE;
        }
    }        
    return (success);
}



// Fonctions implémentant les instructions de base des dynamixel (cf. pg 19 du User's manual des AX-12)
///////////////////////////////////////////////////////////////////////////////////////////////////////

void dynaPing(dynamixelType *dyna) {
    int i, count;
    unsigned char msg[6] = {0xFF, 0xFF, dyna->id, 0x02, INST_PING, 0x00};
    unsigned char answerPacket[6];
    
    msg[5] = prDynaChecksum(msg);
    count = 1;
    timerStart(prDynTimerId);
    while ((count != 0) && (count < NBRE_RENVOIS_MAX)) {
        DIRECTION = 0;
        for (i=0; i<6; i++) {                       // Envoi du message
            uartSendChar(prDynUartCh, msg[i]);
        }
        while (!uartTxIdle(prDynUartCh));             // on attend que la transmission soit finie
        DIRECTION = 1;                              // Retour en écoute
        while (uartRxDataAvailable(prDynUartCh)) {    // Vidange du buffer de réception (nécessaire ?)
            uartGetChar(prDynUartCh);
        }
        if (dyna->responding == TALKING) { // si le dynamixel est censé répondre
            i = 0;
            timerReset(prDynTimerId);
            while ((i < 6) && (!timerFlag(prDynTimerId))) {
                while ((!uartRxDataAvailable(prDynUartCh)) && (!timerFlag(prDynTimerId)));
                while (uartRxDataAvailable(prDynUartCh)) {
                    answerPacket[i] = uartGetChar(prDynUartCh);
                    i++;
                }
            }
            if (timerFlag(prDynTimerId)) {
                count++;
            } else if (prDynaCheckStatusPacket(dyna, answerPacket)) {
                count = 0;
            } else {
                count++;
            }
        }
    }
    timerStop(prDynTimerId);
    if (count != 0) {
        dyna->status = DEFAILLANT;
    } // pas de reaction après certain nombre de renvoi, on le considère comme mort
}


void prDynaWriteData(dynamixelType *dyna, unsigned char address, unsigned char length, unsigned char* data) {
    int i, count;
    unsigned char msg[60];
    unsigned char answerPacket[60];

    // On commence par vérifier si on n'essaye pas d'écrire en dehors de la table
    if (address+length > 49) {
        while(1);
    }
    // on prépare la trame à envoyer (cf. pg10 et pg19 du User's manula des AX-12)
    msg[0] = 0xFF;
    msg[1] = 0xFF;
    msg[2] = dyna->id;
    msg[3] = length+3;
    msg[4] = INST_WRITE_DATA;
    msg[5] = address;
    for (i=0; i<length; i++) {
        msg[6+i] = data[i];
    }
    msg[6+length] = prDynaChecksum(msg);
    // on essaye d'envoyer la trame
    dyna->status = OPERATIONNEL;
    count = 1;
    timerStart(prDynTimerId);     // démarrage du timeout
    while ((count != 0) && (count < NBRE_RENVOIS_MAX)) {
        DIRECTION = 0;                                      // passage en émission
        for (i=0; i<7+length; i++) {                        // Envoi du message
            uartSendChar(prDynUartCh, msg[i]);
        }
        while (!uartTxIdle(prDynUartCh));                     // on attend que la transmission soit finie
        DIRECTION = 1;                                      // Retour en écoute
        while (uartRxDataAvailable(prDynUartCh)) {            // Vidange du buffer de réception (nécessaire ?)
            uartGetChar(prDynUartCh);
        }
        if (dyna->responding == TALKING) {                  // si le dynamixel est censé répondre
            i = 0;
            timerReset(prDynTimerId);                         // on redémarre un timeout
            while ((i < 6) && (!timerFlag(prDynTimerId))) {   // on attend d'avoir reçu la trame de statut ou la fin du timeout
                if (uartRxDataAvailable(prDynUartCh)) {
                    answerPacket[i] = uartGetChar(prDynUartCh);
                    i++;
                }
            }
            // ensuite, on vérifie ce qui s'est passé
            if (timerFlag(prDynTimerId)) {    // en cas de timeout, on incrémente le compteur d'essais
                count++;
            } else if (prDynaCheckStatusPacket(dyna, answerPacket)) {   // si la trame reçue est correcte, on a fini
                count = 0;
            } else {        // sinon, on incrémente le compteur d'essais
                count++;
            }
        }
    }
    // après avoir bien reçu la trame de statut ou épuisé le nombre d'essais, on arrête le timeout
    timerStop(prDynTimerId);
    if (count == 0) {           // et on met à jour le statut de moteur
        dyna->status |= OPERATIONNEL;
    } else {
        dyna->status |= DEFAILLANT;
    }
}


void prDynaReadData(dynamixelType *dyna, unsigned char address, unsigned char length, unsigned char* data) {
    int i, count;
    unsigned char msg[8];
    unsigned char answerPacket[60];

    if (address+length > 49) {         // out of range
        while(1);
    }
    msg[0] = 0xFF;
    msg[1] = 0xFF;
    msg[2] = dyna->id;
    msg[3] = 4;
    msg[4] = INST_READ;
    msg[5] = address;
    msg[6] = length;
    msg[7] = prDynaChecksum(msg);
    
    dyna->status = OPERATIONNEL;
    count = 1;
    timerStart(prDynTimerId);
    while ((count != 0) && (count < NBRE_RENVOIS_MAX)) {
        DIRECTION = 0;
        for (i=0; i<8; i++) {                       // Envoi du message
            uartSendChar(prDynUartCh, msg[i]);
        }
        while (!uartTxIdle(prDynUartCh));             // on attend que la transmission soit finie
        DIRECTION = 1;                              // Retour en écoute
        while (uartRxDataAvailable(prDynUartCh)) {    // Vidange du buffer de réception (nécessaire ?)
            uartGetChar(prDynUartCh);
        }
        if (dyna->responding == TALKING) { // si le dynamixel est censé répondre
            i = 0;
            timerReset(prDynTimerId);
            while ((i < length+6) && (!timerFlag(prDynTimerId))) {
                if (uartRxDataAvailable(prDynUartCh)) {
                    answerPacket[i] = uartGetChar(prDynUartCh);
                    i++;
                }
            }
            if (timerFlag(prDynTimerId)) {
                count++;
            } else if (prDynaCheckStatusPacket(dyna, answerPacket)) {
                count = 0;
            } else {
                count++;
            }
        }
    }
    timerStop(prDynTimerId);
    if (count == 0) {
        for (i=0; i<length; i++) {
            data[i] = answerPacket[5+i];
        }
    } else {
        dyna->status = DEFAILLANT;
    } // pas de reaction après certain nombre de renvoi, on le considère comme mort
}
