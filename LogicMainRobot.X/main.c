/*!
 * @file main.c
 * @author Olivier Desenfans - Michel Os�e
 * @author bULBot 2015
 * @brief Gestion de la carte-maitre du robot.
 * @details Impl�mentation de l'intelligence haut niveau du robot
 * et coordination des diff�rents modules.
 */


#include "dataTypes.h"
#include "gestionActions.h"
#include "basicActions.h"
#include "gestionPropulsion.h"
#include "spio.h"
#include "adc.h"
#include "timer.h"
#include "Globals.h"
#include "sharp.h"
#include "ax12.h"
#include "uart.h"
#include "servoClap.h"
#include "../Can/CanNetwork.h"
#include "../libdspic/CanDspic.h"
#include "../libdspic/clock.h"
#include "../libdspic/servo.h"
#include <math.h>
#include "BLE.h"
#include <libpic30.h>


_FWDT(FWDTEN_OFF) // on d�sactive le Watchdog
_FOSCSEL(FNOSC_FRC);
// enables clock switching and configure the primary oscillator for a 10MHz crystal
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FGS(GSS_OFF & //
	GCP_OFF & //
	GWRP_OFF); //
_FICD(ICS_PGD1); // <-- � changer selon les cas


#define LOGI_SHARP_MESURE   (CN_LOGIQUE*0x10)

//////////////////////////////
//	Constantes				//
/////////////////////////////
const positionInteger positionInitialeJaune = {500, 1000, 0};        //! Position initiale pour l'�quipe jaune.
const positionInteger positionInitialeVert = {2500 , 1000, 1800};  //! Position initiale pour l'�quipe verte.1800
obstacleType AllyObs = {0 , 0, 0};

//////////////////////////////////
//  PROTOTYPES DES FONCTIONS    //
//////////////////////////////////
actionType choixAction(void);
actionType gestionErreur(actionType currentAction);
/*
 Faut d�finir les actions mots/cl�s
 Actions possibles de l'ann�e
 ("se d�placer","d�placer","g�ner","stocker","prendre","recona�tre","tirer","empiler","pousser")
 infoAction 
 infoAction actions2016 = {porte,poisson,sable,coquiallage}
 
 
 
 
 */



//////////////////////////////
//	Variables globales 		//
//////////////////////////////
unsigned int nbActions;             //<! d�finit le nombre total d'actions � ex�cuter
actionType *ordreActions;           //<! Tableau d'actions � effectuer dans l'ordre
match matchStatus = INIT;           //<! Etat du match.
int mesureSharp;                    //<! Mesure du Sharp

//Denis
detectionSharpType detectionSharpMain;
int STOPED_OBS=0;
infoActionType infoAction;
int EnvoiSharpActif = 1;
propIsObstacleType obstacle;
positionInteger oldPos;


const positionInteger Zero = {0, 0, 0};
actionType Porte[3]= {{{2500, 1850, 1800}, AUCUNE_ACTION,seDeplacer,A_FAIRE},{{2500, 1850, 1800}, AUCUNE_ACTION,pousser,A_FAIRE},{{2000, 1850, 1800}, AUCUNE_ACTION,seDeplacer,A_FAIRE}}; 
actionType Poisson[3]= {{{2200,150, 1800}, AUCUNE_ACTION,seDeplacer,A_FAIRE},{{2200, 150, 1800}, ACTIONNEUR,prendre,A_FAIRE,},{{1200, 150, 1800}, AUCUNE_ACTION,seDeplacer,A_FAIRE}}; 
actionPossible ActionPossible[2] = {{3,40,0,&Poisson},{3,20000,0,&Porte}};
positionInteger RESET ={-1,-1,-1};
int Repeat;
int newTache = 1;


/**
 * @fn int main(void)
 * @brief Fonction main du programme.
 */
int main(void) {
	// D�claration des variables locales.
    match oldMatchStatus = OVER;            // Etat pr�c�dent duu match (pour les actions d'entr�e)
	actionType choix;                  //<! Pointeur vers l'action en cours.
	positionInteger positionInitiale;       //<! Position initiale du robot sur la table
	team equipe;                            //<! Equipe actuelle.

//    propIsObstacleType test;
	pllConfig();					// Configuration de la PLL de l'horloge interne pour tourner � 40MIPS
	assignSPIO();					// Assignation des pins du dSPIC.
    servoInit(4, TIMER_2, 10);      // initialise 1 servo, utilisant le timer2 � 10ms
    
    timerSetup(TIMER_5, 50);
    TMR5 = 0;
    initAX12();                 // Init de l'AX12
	// Initialisation du CAN
    
	CanInitialisation(CN_LOGIQUE);
	propulsionInitCan();
    CanDeclarationProduction(CN_LOGIQUE*0x10, &matchStatus, sizeof(matchStatus));
    CanDeclarationProduction(CN_LOGIQUE*0x10, &mesureSharp, sizeof(mesureSharp));
	ACTIVATE_CAN_INTERRUPTS = 1;
	//msTimerInit();                  // Initialisation du timer des millisecondes, n'est utilis� que pour waitXms (TODO: enlever en m�m temps que waitXms)

	while(1) {
		if (getMatchTimerFlag()) {
			matchStatus = OVER;
		}
		// Machine d'�tat de la logique
	switch (matchStatus) {
            case INIT:                  // Etat initial, phase pr�c�dant le match
                if (matchStatus != oldMatchStatus) {
                    oldMatchStatus = matchStatus;
                    CanEnvoiProduction(&matchStatus);
                    matchTimerInit();				// Initialisation du timer de match
                    initServoClap();
                    initADC();
                   // RentrerAimant();
                    initBLE();
                    if (EnvoiSharpActif == 1){
                        timerStart(TIMER_5);
                        IEC1bits.T5IE = 1;
                    }     
                }
                if (!GOUPILLE_OTEE) {
                    matchStatus = PRE_MATCH;
                }
                break;
            case PRE_MATCH:             // Le robot attend le d�but du match. On peut encore choisir la couleur
 /*               if (detectionObstacleSharp().isObstacleDetected && cool){
//                  FermerPince();
                }
                else{               
//                 OuvrirPince();
                }*/
                if (radioGetRxBufferSpace() > 0){
                    radioGetChar();
                }
                if (matchStatus != oldMatchStatus) {
                    oldMatchStatus = matchStatus;
                    CanEnvoiProduction(&matchStatus);
                }

				if (BOUTON_EQUIPE == JAUNE) {
					equipe = JAUNE;
					positionInitiale = positionInitialeJaune;
					//ordreActions = actionsJaune;
					nbActions = NB_ACTIONS_JAUNE;
				} else {
					equipe = VERT;
					positionInitiale = positionInitialeVert;
					//ordreActions = actionsVert;
					nbActions = NB_ACTIONS_VERT;
				}
				// TRANSITIONS
				if (GOUPILLE_OTEE) {                                                        // si la goupille est retir�e, le match commence
					StartMatchTimer();                                                      // on lance le timer de match (90s))
                    propulsionEnable();  // on active la propulsion
                   // msTimerStart();
                    
                    while(propulsionGetStatus() != STANDING);                               // on attend que l'ordre soit ex�cut�
					propulsionSetPosition(positionInitiale);                                // On initialise la position de la propulsion
                    while(!compareXYAlpha(propulsionGetPosition(), positionInitiale));     // on attend que l'ordre soit ex�cut�
                    choix = choixAction();                                                  // S�lection de la prochaine action => c'est dans cette fonction qu'il faut mettre de l'IA
					matchStatus = ONGOING;

				}
				break;
            case ONGOING: // Le match est lanc�

                if (matchStatus != oldMatchStatus) {
                    oldMatchStatus = matchStatus;
                    CanEnvoiProduction(&matchStatus);
                }

                infoAction = choix.ptr2Fct(choix.dest,choix.methode);
                

                
                if (canReceivedOrderFlag) {
                    canReceivedOrderFlag = 0;
                    if (canReceivedCommand == LOGI_SHARP_MESURE) {
                        EnvoiSharpActif = canReceivedData[0];
                   }
                }

                // On met � jour la position de l'autre robot

                //propulsionAddObstacle(getAllyPos());

                
                switch(infoAction.statut) {
                    case ACTION_PAS_COMMENCEE:
                    case ACTION_EN_COURS:
                        // on attend la fin de l'action
                        break;
                    case ACTION_FINIE:
                    case ACTION_REMISE:
                        choix = choixAction();                  // S�lection de la prochaine action => c'est dans cette fonction qu'il faut mettre de l'IA
                        break;
                    case ACTION_ERREUR:
                        matchStatus = ERROR;

                    default:
                        break;
                }
                break;
            case OVER:
                if (matchStatus != oldMatchStatus) {
                    oldMatchStatus = matchStatus;
                    CanEnvoiProduction(&matchStatus);
                    propulsionDisable();
                }
                if (!GOUPILLE_OTEE) {
                    matchStatus = INIT;
                }
                break;
            case ERROR:
                if (matchStatus != oldMatchStatus) {
                    oldMatchStatus = matchStatus;
                    CanEnvoiProduction(&matchStatus);
                }
                choix = gestionErreur(choix);
                matchStatus = ONGOING;
                break;
            default:
                matchStatus = ERROR;
                break;
        }
        
        
   }

    return 0;
}


actionType choixAction() {
      // on arr�te l'int�rruption quand on choisi une action
    actionType TacheChoisie;
	static unsigned int indiceAction = 0;		//<! d�finit l'action en cours
    static unsigned int indiceTache;
    int oldIndiceTache;
    int temps[2]={0,0};
    int tmp;
    int* tmp2;
    int itache;
    int iaction;
   
    radioSendString("NewTask");
    while(!isTaskActionUpToDate());
    tmp2 = getTaskAction();
    indiceTache = *tmp2;
    indiceAction = *(tmp2+1);
    radioSendString("AOK");
     /*
            if (STOPED_OBS == 1) {
            ActionPossible[indiceTache].done = REPORTEE; // Ralentie � cause d'un obstacle
            STOPED_OBS++;
            newTache = 1;
            }

            
        if (indiceAction == ActionPossible[indiceTache].numAction || newTache){
           // on doit choisir une nouvelle t�che)
            newTache = 0;
            for (itache=0; itache < 2;itache++){
                positionInteger fictivePos = propulsionGetPosition();
                for (iaction=0; iaction < ActionPossible[itache].numAction;iaction++) {
                    if(ActionPossible[itache].action[iaction].done == A_FAIRE){             // Si l'�tape est r�solue ou non
                    tmp=computeTime(ActionPossible[itache].action[iaction].dest,fictivePos);
                    if (ActionPossible[itache].action[iaction].methode == ACTIONNEUR){
                    tmp += 4000; // on compte 6 seconde par actionneur (ex: p�cher les poissons)
                    }
                    
                    temps[itache] += tmp;
                    fictivePos = ActionPossible[itache].action[iaction].dest;
                    }
            }
                switch(ActionPossible[itache].done){
                    case(A_FAIRE):
                        temps[itache] = (int) (ActionPossible[itache].point/temps[itache]);
                        break;
                    case(REPORTEE):
                        ActionPossible[indiceTache].done =A_FAIRE;
                        temps[itache]= (int) (ActionPossible[itache].point/(temps[itache]+3000)); // retard = +3 sec
                        break;
                    case(FAITE):
                        temps[itache]= 0;
                        break;
                    default:
                        break;
        }
            }
                oldIndiceTache = indiceTache;
                indiceTache = find_maximun(temps);
                if (oldIndiceTache != indiceTache){            // Si on change on r�initialise les actions
                    indiceAction = 0;
                if (ActionPossible[oldIndiceTache].done != FAITE){ // Si la t�che pr�c�dente n'a pas �t� finie.
                    for (iaction=0; iaction < ActionPossible[oldIndiceTache].numAction;iaction++){
                        ActionPossible[oldIndiceTache].action[iaction].done = A_FAIRE;       // on remet toute actions d�j� FAITE � A_FAIRE
                 }
                 }
        }
                ActionPossible[indiceTache].done = FAITE;
        }
        else if (Repeat == 0) {                     // si on continue simplement la t�che en cours
                ActionPossible[indiceTache].action[indiceAction].done = FAITE; // L'action pr�c�dente a �t� execut�e.
                indiceAction++;
            }
           
        else{                                   // repeat l'action (si on a eu un START_TRAJ_OBST)
                Repeat = 0;
            }
            
 
*/
      TacheChoisie= ActionPossible[indiceTache].action[indiceAction];
      
	return(TacheChoisie);
}



actionType gestionErreur(actionType currentAction) {

    actionType nextAction={Zero,0, noActionFct};
    infoActionType infoAction;
    positionInteger curPos = propulsionGetPosition();
    infoAction = currentAction.ptr2Fct(currentAction.dest,currentAction.methode);
    trajectoryBasicAction(RESET); 
    switch(infoAction.typeEtapeEnCours) {
        case ACTION_TRAJECTOIRE:
            switch (propulsionGetStatus()) {
                case STANDING:
                case TRAJECTORY:
                case RELATIVE_MOVE:
              if (STOPED_OBS == 1){
                  radioSendString("OBST");
               //   radioSendString(detectionSharpMain.obstacleInfo.x);
               //   radioSendString(detectionSharpMain.obstacleInfo.y);
                  radioSendString("@");
                nextAction = choixAction();
            }
            else if (STOPED_OBS == 0){
                nextAction = choixAction();
                radioSendString("ERROR@");
            }    
            else if (STOPED_OBS == 2){
                nextAction = choixAction();
                radioSendString("ERROR@");
            }                  

                    break;
                case TRAJ_NO_WAY:                       // si on n'a pas trouv� de chemin, c'est qu'il y a un obstacle dans le chemin
                  //  nextAction = choixAction();         // on passe la main
                case TRAJ_START_OBS:
                case TRAJ_START_OUT:            // pour les autres cas d'erreur trajectoire, pas encore de solution impl�ment�e               
                case TRAJ_END_OUT:
                case TRAJ_END_OBS:
                    propulsionEnable();
                    while(propulsionGetStatus() != STANDING);
                    curPos.x = (int) curPos.x-100*cos(DEG2RAD(curPos.alpha));             // On sort du carr� de l'obstacle pour red�marrer
                    curPos.y = (int) curPos.y-100*sin(DEG2RAD(curPos.alpha));
                    nextAction.ptr2Fct = seDeplacer;
                    nextAction.methode = 0;
                    nextAction.dest = curPos ;
                    Repeat=1;
                    break;
 
                default:
                    break;
            }
            
            break;
        case ACTION_PROPULSION:
            break;
        case ACTION_ACTIONNEURS:
            if (STOPED_OBS != 0){
                nextAction = currentAction;
            }

    default:
        nextAction = currentAction;
        break;
    }
    return(nextAction);
}


// INTERRUPT SHARP
void __attribute__((interrupt, auto_psv)) _T5Interrupt(void) {
	IFS1bits.T5IF = 0;		// R�initialisation du flag
    //TMR5 = 0;
    actionType stop;
    
    if (STOPED_OBS == 0){ 
        detectionSharpMain = detectionObstacleSharp();
        if (detectionSharpMain.isObstacleDetected ){          
            
            propulsionIsObstacle(detectionSharpMain.obstacleInfo); 
            __delay_ms(1);
            obstacle = propulsionGetObstacle();
            if (detectionSharpMain.obstacleInfo.x > 2950 || detectionSharpMain.obstacleInfo.y > 1950){ // ne doit pas rester c'est la propulsion qui devrait le faire
                obstacle = PROP_IS_UNMOVABLE_OBSTACLE;
            }
          if (obstacle == PROP_IS_NO_OBSTACLE && matchStatus != ERROR ){
                stop.ptr2Fct = StopNowFct;
                stop.dest = RESET;
                stop.methode = 0;
                infoAction = stop.ptr2Fct(stop.dest,stop.methode);
                matchStatus = ERROR;
                while (ABS(detectionSharpMain.obstacleInfo.x) < 1.0){
                detectionSharpMain = detectionObstacleSharp();
                }
                propulsionAddObstacle(detectionSharpMain.obstacleInfo);
                STOPED_OBS = 1;
                oldPos = propulsionGetPosition();
        }
    }
  }
    else if (STOPED_OBS == 2){ // on d�sactive la vision tant qu'il a pas fait 45�
        positionInteger pos = propulsionGetPosition();
        if (400 < (compareAlpha(pos,oldPos))){
            STOPED_OBS =0;
            detectionObstacleSharp(); // vide le buffer de l'ADC (sinon on aura les anciennes coordon�es � la prochaine vision)
            detectionObstacleSharp();
        }
    }
}

