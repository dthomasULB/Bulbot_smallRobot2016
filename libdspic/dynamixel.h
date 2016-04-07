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
//! Bit de direction pour l'UART Half Duplex connecté aux servomoteurs Dynamixel.
#define DIRECTION           PORTCbits.RC8
#define DIRECTION_TRIS      TRISCbits.TRISC8
#define ID_BROADCAST        0xFE    //!< ID de broadcast sur le bus Dynamixel.
#define NBRE_RENVOIS_MAX    3       //<! Nombre maximum de renvois d'un message pour les Dynamixel.
#define NBRE_DYNAMIXEL_MAX  4       //!< Nombre max de dynamixcel chainés


// statut de l'actionneur
typedef enum {
    DEFAILLANT = 0,         // le moteur ne répond pas aux commandes
    OPERATIONNEL = 1,       // le moteur fonctionne correctement
    BLOQUE = 4,             // le moteur est bloqué mécaniquement
    SURCHAUFFE = 8,         // le moteur est en surchauffe
    ERR_ALIM = 16,          // la tension d'alimentation est en dehors de la gamme prévue
    ERR_MESSAGE = 32,       // le moteur a reçu une trame mal formatée
    ERR_ACQUITTEMENT = 64   // la réponse du moteur est mal formatée
} dynaStatus;


/****************************************************************************/
/*  TYPES                                                                   */
/****************************************************************************/
typedef struct {
    unsigned char id;       //!< ID du dynamixel
    unsigned char error;    //!< Bits d'erreur du dynamixel
    dynaStatus status;      //!< Statut du dynamixel
    /*! Le dynamixel peut etre configuré en mode:
     *  - répond par son statut à tous les messages qui lui sont adressés (TALKING)
        - ne répond qu'aux instructions READ avec les paramètres demandés (MUTE)  */
    unsigned char responding;
} dynamixelType;


/****************************************************************************/
/*  FUNCTIONS                                                               */
/****************************************************************************/
/**
 * @brief configure les périphériques nécessaires à la librairie Dynamixel
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
 * @brief enoie une commande PING à un actionneur.
 * @details Utilise la commande Ping pour mettre à jour le statut
 * de l'actionneur @p id.
 * @param[in] id ID du moteur concerné.
 */
void dynaPing(dynamixelType *dyna);

/**
 * @brief Permet de passer le baudrate en mode rapide (1Mbps) ou en mode lent (200kbps).
 */
void dynaChangeBaudrate(dynamixelType *dyna, unsigned char baudrate);

/**
 * @brief Allume la led du dynamixel correspondant à l'ID
 * @param ID du dynamixel.
 */
void dynaLedOn(dynamixelType *dyna);
/**
 * @brief Eteind la led du dynamixel correspondant à l'ID
 * @param ID du dynamixel.
 */
void dynaLedOff(dynamixelType *dyna);

// Fonctions liées au contrôle du couple
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
 * @details Oriente le moteur spÈcifiÈ par @p id dans la position @p goal.
 * @param[in] goal Position angulaire ? atteindre.
 * goal=1023 ou = 0x3FF => 300°
   goal=511 ou 0x1FF => 150°
   goal=0 ou 0x00 =>0°
 * @param[in] id ID du moteur à commander.
 */
void dynaSetGoalPosition(dynamixelType *dyna, float angle);
/**
 * @brief Vérifie si un actionneur Dynamixel est actuellement en mouvement.
 * @param[in] id ID du moteur concerné.
 * @param[out] Booléen indiquant si le moteur est en mouvement ou non.
 */
int dynaIsMoving(dynamixelType *dyna);

/**
 * @brief Lecture de la position angulaire d'un moteur.
 * @param[in] id ID du moteur dont il faut lire la position.
 * @returns Position de l'actionneur et informations sur la rÈception.
 */
float dynReadPresentPosition(dynamixelType *dyna);


void dynaStartEndlessTurn(dynamixelType *dyna);
void dynaStopEndlessTurn(dynamixelType *dyna);
void dynaSetGoalSpeed(dynamixelType *dyna, int speed);
int StepTurn(dynamixelType *dyna, int speed, int stop[], int len, int number, int sens);

/**
 * @brief Orientation de plusieurs moteurs simultanément
 * @param[in] goal[] chaque élément du vecteur est la consigne de position angulaire pour chaque moteur.
 * @param[in] id[] chaque élément du vecteur est l'ID du moteur correspondant
 * @param[in] number est le nombre de servo controllés en même temps (min 2 et max 4)
 */
void rotationSyncDynamixel(int goal[NBRE_DYNAMIXEL_MAX], unsigned char id[NBRE_DYNAMIXEL_MAX], int number, dynamixelType *dyna);



/**
 * @brief Réinitialise les infos d'un moteur déjà créé
 * @param[in] *dyna Pointeur vers le moteur à réinitialiser
 * @return Aucun
 */
void ResetValues(dynamixelType *dyna);
/**
 * @brief Réinitialise les infos de tous les moteurs déjà créé
 * @param Aucun
 * @return Aucun
 */
void ResetAllValues();
/**
 * @brief Renvoie le status du moteur selon l'info reçue
 * @param[in] info reçue par le moteur
 * @return Statut du moteur
 */
//unsigned char StatusCompute(dynamixelRxInfoType info);

/**
 * @brief Set l'alarm led du dynamixel (blink quand erreur)
 * @param[in] ID du dynamixel.
 * @param[in] Erreur à laquelle on est sensible (OVERHEAT, BLOQUE, MESSAGE ERRONE, ...)
 */
void AlarmLedOn(unsigned char statut, dynamixelType *dyna);
/**
 * @brief Eteinds l'alarm led
 * @param[in] ID du dynamixel.
 */
void AlarmLedOff(dynamixelType *dyna);
/**
 * @brief Change l'ID du moteur défini par l'ancienneID.
 * @param[in] ancienneID ID actuelle du moteur.
 * @param[in] nouvelleID Valeur de la nouvelle ID.
 */
void changeID(unsigned char nouvelleID, dynamixelType *);
/**
 * @brief Initialise l'ID d'un moteur
 * @param[in] nouvelleID Valeur de la nouvelle ID.
 * @note Le moteur doit être le seul connecté au bus Dynamixel.
 * @note Fonction à utiliser uniquement pour configurer les moteurs.
 */
void initID(unsigned char nouvelleID, dynamixelType *);
/**
 * @brief Activation du renvoi d'un paquet de statut pour tout message envoyÈ.
 * @param[in] id ID du moteur concernÈ.
 * @returns BoolÈen confirmant que l'opÈration s'est bien rÈalisÈe.
 */
int activePaquetStatut(dynamixelType *dyna);
/**
 * @brief DÈsactivation du renvoi d'un paquet de statut pour tout message envoyÈ.
 * @note Le paquet de statut est toujours envoyÈ en cas d'une instruction de lecture.
 * @param[in] id ID du moteur concernÈ.
 * @returns BoolÈen confirmant que l'opÈration s'est bien rÈalisÈe. Renvoie -1 si
 * overflow du buffer de rÈception lors de la lecture.
 */
int desactivePaquetStatut(dynamixelType *dyna);

/**
 * @brief Lecture de l'octet de configuration du renvoi de paquet de statut.
 * @param[in] id ID du moteur concernÈ.
 * @returns Valeur de l'octet de configuration. Renvoie -1 si
 * overflow du buffer de rÈception lors de la lecture.
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
