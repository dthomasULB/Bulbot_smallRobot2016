/**
 * @file dynamixel.h
 * @brief Fichier header pour communication avec servomoteurs Dynamixel.
 * @author Olivier Desenfans (version 2014: Yernaux Florence)
 * @author bULBot 2011-2012-2014
 */

#ifndef DEF_DYNAMIXEL_H
#define DEF_DYNAMIXEL_H


#include "../libdspic/uart.h"
#include "../libdspic/timers.h"


/****************************************************************************/
/*  DEFINES                                                                 */
/****************************************************************************/
//! Bit de direction pour l'UART Half Duplex connect� aux servomoteurs Dynamixel.
#define DIRECTION           PORTCbits.RC8
#define DIRECTION_TRIS      TRISCbits.TRISC8
#define ID_BROADCAST        0xFE    //!< ID de broadcast sur le bus Dynamixel.
#define NBRE_RENVOIS_MAX    3       //<! Nombre maximum de renvois d'un message pour les Dynamixel.
#define NBRE_DYNAMIXEL_MAX  4       //!< Nombre max de dynamixcel chain�s


// statut de l'actionneur
typedef enum {
    DEFAILLANT = 0,         // le moteur ne r�pond pas aux commandes
    OPERATIONNEL = 1,       // le moteur fonctionne correctement
    BLOQUE = 4,             // le moteur est bloqu� m�caniquement
    SURCHAUFFE = 8,         // le moteur est en surchauffe
    ERR_ALIM = 16,          // la tension d'alimentation est en dehors de la gamme pr�vue
    ERR_MESSAGE = 32,       // le moteur a re�u une trame mal format�e
    ERR_ACQUITTEMENT = 64   // la r�ponse du moteur est mal format�e
} dynaStatus;


/****************************************************************************/
/*  TYPES                                                                   */
/****************************************************************************/
typedef struct {
    unsigned char id;       //!< ID du dynamixel
    unsigned char error;    //!< Bits d'erreur du dynamixel
    dynaStatus status;      //!< Statut du dynamixel
    /*! Le dynamixel peut etre configur� en mode:
     *  - r�pond par son statut � tous les messages qui lui sont adress�s (TALKING)
        - ne r�pond qu'aux instructions READ avec les param�tres demand�s (MUTE)  */
    unsigned char responding;
} dynamixelType;


/****************************************************************************/
/*  FUNCTIONS                                                               */
/****************************************************************************/
/**
 * @brief configure les p�riph�riques n�cessaires � la librairie Dynamixel
 * @param msg
 * @return 
 */
void dynaConfigBus(int uartCh, float baudrate, int timerId);
/**
 * @brief Ajoute un nouveau moteur au bus Dynamixel
 * @param[in] *dyna Pointeur vers une structure dynamixelType qui contiendra les infos du nouveau moteur.
 * @param[in] id ID du nouveau moteur
 * @returns Aucun
 */
void dynaConfigMot(dynamixelType *dyna, unsigned char id);

/**
 * @brief enoie une commande PING � un actionneur.
 * @details Utilise la commande Ping pour mettre � jour le statut
 * de l'actionneur @p id.
 * @param[in] id ID du moteur concern�.
 */
void dynaPing(dynamixelType *dyna);

/**
 * @brief Permet de passer le baudrate en mode rapide (1Mbps) ou en mode lent (200kbps).
 */
void dynaChangeBaudrate(dynamixelType *dyna, unsigned char baudrate);

/**
 * @brief Allume la led du dynamixel correspondant � l'ID
 * @param ID du dynamixel.
 */
void dynaLedOn(dynamixelType *dyna);
/**
 * @brief Eteind la led du dynamixel correspondant � l'ID
 * @param ID du dynamixel.
 */
void dynaLedOff(dynamixelType *dyna);

// Fonctions li�es au contr�le du couple
////////////////////////////////////////////////////////////////////////////////

int dynaReadTorqueEnable(dynamixelType *dyna);
int dynaReadTorqueLimit(dynamixelType *dyna);
void dynaSetTorqueLimit(dynamixelType *dyna, int goal);
void dynaTorqueEnable(dynamixelType *dyna);
void dynaTorqueDisable(dynamixelType *dyna);

int dynaReadCwAngleLimit(dynamixelType *dyna);
int dynaReadCcwAngleLimit(dynamixelType *dyna);
void dynaSetCwAngleLimit(dynamixelType *dyna, unsigned int cwAngleLimit);
void dynaSetCcwAngleLimit(dynamixelType *dyna, unsigned int ccwAngleLimit);
/**
 * @brief Orientation d'un moteur Dynamixel.
 * @details Oriente le moteur sp�cifi� par @p id dans la position @p goal.
 * @param[in] goal Position angulaire ? atteindre.
 * goal=1023 ou = 0x3FF => 300�
   goal=511 ou 0x1FF => 150�
   goal=0 ou 0x00 =>0�
 * @param[in] id ID du moteur � commander.
 */
void dynaSetGoalPosition(dynamixelType *dyna, float angle);
/**
 * @brief V�rifie si un actionneur Dynamixel est actuellement en mouvement.
 * @param[in] id ID du moteur concern�.
 * @param[out] Bool�en indiquant si le moteur est en mouvement ou non.
 */
int dynaIsMoving(dynamixelType *dyna);

/**
 * @brief Lecture de la position angulaire d'un moteur.
 * @param[in] id ID du moteur dont il faut lire la position.
 * @returns Position de l'actionneur et informations sur la r�ception.
 */
float dynReadPresentPosition(dynamixelType *dyna);


void dynaStartEndlessTurn(dynamixelType *dyna);
void dynaStopEndlessTurn(dynamixelType *dyna);
void dynaSetGoalSpeed(dynamixelType *dyna, int speed);
int StepTurn(dynamixelType *dyna, int speed, int stop[], int len, int number, int sens);

/**
 * @brief Orientation de plusieurs moteurs simultan�ment
 * @param[in] goal[] chaque �l�ment du vecteur est la consigne de position angulaire pour chaque moteur.
 * @param[in] id[] chaque �l�ment du vecteur est l'ID du moteur correspondant
 * @param[in] number est le nombre de servo controll�s en m�me temps (min 2 et max 4)
 */
void rotationSyncDynamixel(int goal[NBRE_DYNAMIXEL_MAX], unsigned char id[NBRE_DYNAMIXEL_MAX], int number, dynamixelType *dyna);



/**
 * @brief R�initialise les infos d'un moteur d�j� cr��
 * @param[in] *dyna Pointeur vers le moteur � r�initialiser
 * @return Aucun
 */
void ResetValues(dynamixelType *dyna);
/**
 * @brief R�initialise les infos de tous les moteurs d�j� cr��
 * @param Aucun
 * @return Aucun
 */
void ResetAllValues();
/**
 * @brief Renvoie le status du moteur selon l'info re�ue
 * @param[in] info re�ue par le moteur
 * @return Statut du moteur
 */
//unsigned char StatusCompute(dynamixelRxInfoType info);

/**
 * @brief Set l'alarm led du dynamixel (blink quand erreur)
 * @param[in] ID du dynamixel.
 * @param[in] Erreur � laquelle on est sensible (OVERHEAT, BLOQUE, MESSAGE ERRONE, ...)
 */
void AlarmLedOn(unsigned char statut, dynamixelType *dyna);
/**
 * @brief Eteinds l'alarm led
 * @param[in] ID du dynamixel.
 */
void AlarmLedOff(dynamixelType *dyna);
/**
 * @brief Change l'ID du moteur d�fini par l'ancienneID.
 * @param[in] ancienneID ID actuelle du moteur.
 * @param[in] nouvelleID Valeur de la nouvelle ID.
 */
void changeID(unsigned char nouvelleID, dynamixelType *);
/**
 * @brief Initialise l'ID d'un moteur
 * @param[in] nouvelleID Valeur de la nouvelle ID.
 * @note Le moteur doit �tre le seul connect� au bus Dynamixel.
 * @note Fonction � utiliser uniquement pour configurer les moteurs.
 */
void initID(unsigned char nouvelleID, dynamixelType *);
/**
 * @brief Activation du renvoi d'un paquet de statut pour tout message envoy�.
 * @param[in] id ID du moteur concern�.
 * @returns Bool�en confirmant que l'op�ration s'est bien r�alis�e.
 */
int activePaquetStatut(dynamixelType *dyna);
/**
 * @brief D�sactivation du renvoi d'un paquet de statut pour tout message envoy�.
 * @note Le paquet de statut est toujours envoy� en cas d'une instruction de lecture.
 * @param[in] id ID du moteur concern�.
 * @returns Bool�en confirmant que l'op�ration s'est bien r�alis�e. Renvoie -1 si
 * overflow du buffer de r�ception lors de la lecture.
 */
int desactivePaquetStatut(dynamixelType *dyna);

/**
 * @brief Lecture de l'octet de configuration du renvoi de paquet de statut.
 * @param[in] id ID du moteur concern�.
 * @returns Valeur de l'octet de configuration. Renvoie -1 si
 * overflow du buffer de r�ception lors de la lecture.
 */
unsigned char lectureRenvoiPaquet(dynamixelType *dyna);
int lectureTorqueDynamixel(dynamixelType *dyna);
int StepOver(dynamixelType *dyna, int speed, int number, int sens);
void rotationDynamixelDegre(int, dynamixelType *dyna);
void InitDynamixel(dynamixelType *dyna, int pos);
int AngleToReg(int angle);
int RegtoAngle(int reg);
void Turn360(dynamixelType dyna, int speed, int sens);


#endif
