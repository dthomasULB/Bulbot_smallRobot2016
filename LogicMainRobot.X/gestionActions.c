/**
 * @file gestionActions.c
 * @author bULBot 2011-2012
 * @author Olivier Desenfans
 * @brief Implémentation du module d'actions du robot.  
 */
/*
#include "gestionActions.h"
#include "gestionPropulsion.h"
#include "basicActions.h"
#include "servoClap.h"
#include "../libdspic/servo.h"
#include "timer.h"
#include "spio.h"
#include "ax12.h"

const positionInteger clap1StartPos = {240, 150, -900};
const positionInteger clap1EndPos = {400, 150, 0};
const positionInteger clap2StartPos = {740, 150, -900};
const positionInteger clap2EndPos = {900, 150, 900};

const positionInteger Door1_Start_pos = {2500, 1850, 1800};
const positionInteger Door2_end_pos = {2000, 1850, 1800};
const positionInteger Fish_start = {2200, 150, 1800};
const positionInteger Fish_net = {1200, 150, 1800};
const positionInteger Fish_bordure = {1700, 150, 1800};

infoActionType demarrageJauneFct(int option);
infoActionType retourVertFct(int option);
infoActionType demarrageVertFct(int option);
infoActionType TestArriere(int option);
infoActionType TestAvant(int option);

//actionType actionsJaune[NB_ACTIONS_JAUNE] = {{DEFAULT_ACTION, demarrageJauneFct},{DEFAULT_ACTION, clapChezNousJaune}};
//actionType actionsVert[NB_ACTIONS_VERT] =  {{DEFAULT_ACTION, retourVertFct},{DEFAULT_ACTION, Fishing}};//,{DEFAULT_ACTION, retourVertFct}};


infoActionType demarrageJauneFct(int option) {
    static infoActionType infoAction = {ACTION_PAS_COMMENCEE, 0, 1, ACTION_TRAJECTOIRE, {1000, 1000, 0}};
    //sortirServoClap(); // TEST
    infoAction.statut = trajectoryBasicAction(infoAction.position);
    //rentrerServoClap(); // TEST
    return (infoAction);
}

infoActionType TestArriere(int option) {
    static infoActionType infoAction = {ACTION_PAS_COMMENCEE, 0, 1, ACTION_TRAJECTOIRE, {-2000, -1000, -1800}};
    infoAction.statut = trajectoryBasicAction(infoAction.position);
    return (infoAction);
}
infoActionType TestAvant(int option) {
    static infoActionType infoAction = {ACTION_PAS_COMMENCEE, 0, 1, ACTION_TRAJECTOIRE, {0, 0, 0}};
    infoAction.statut = translationBasicAction(1000, 1000, 200);
    return (infoAction);
}

infoActionType retourVertFct(int option) {
  static infoActionType infoAction = {ACTION_PAS_COMMENCEE, 0, 1, ACTION_TRAJECTOIRE, {2500, 1700, 1800}};
//  RentrerAimant();
//while(AimantIsMoving()){}
   infoAction.statut = trajectoryBasicAction(infoAction.position);
  
    return (infoAction);
}
  
infoActionType demarrageVertFct(int option) {
    static infoActionType infoAction = {ACTION_PAS_COMMENCEE,   // statut de l'action
                                        0,                      // Etape actuelle
                                        2,                      // Nombre d'étapes
                                        ACTION_TRAJECTOIRE,     // Type de l'étape
                                        {0, 0, 0}};             // Destination de l'étape (si pertinent)
    actionStatutType trajStatut;
   enum {
        GOTO_DOOR1_START = 0,
        GOTO_DOOR2_END = 1,
        ACTION_RESET = 3,
        FINI = 255
    }etape = infoAction.etapeEnCours;
 
   switch (option) {
        case RESET_ACTION:
           etape = FINI;
           infoAction.statut = ACTION_FINIE;
            break;
 //      case DEFAULT_ACTION:
  //          etape = GOTO_DOOR1_START;
  //          infoAction.statut = ACTION_EN_COURS;
  //          option = ACTION_STARTED;
  //          break;
  //      ACTION_STATED:
  //          break;
        default:
            break;
    }
        switch (etape) {
            case GOTO_DOOR1_START:
                trajStatut = trajectoryBasicAction(Door1_Start_pos);
                 infoAction.statut = ACTION_EN_COURS;
                if (trajStatut == ACTION_FINIE) {
                    infoAction.etapeEnCours = GOTO_DOOR2_END;
                }
                else  if (trajStatut == ACTION_ERREUR) {
                    infoAction.statut = ACTION_ERREUR;
                    etape = FINI;
                }
                break;
            case GOTO_DOOR2_END:
                trajStatut = trajectoryBasicAction(Door2_end_pos);
                if (trajStatut == ACTION_FINIE) {
                    infoAction.statut = ACTION_FINIE;
                    etape = FINI;
                }
               if (trajStatut == ACTION_ERREUR) {
                    infoAction.statut = ACTION_REMISE;
                    etape = FINI;
                }
                break;
            case FINI:
                etape = 0;
                infoAction.statut = ACTION_FINIE;
            default:
                break;
}
    return (infoAction);
}

infoActionType Fishing(int option) {
    static infoActionType infoAction = {ACTION_PAS_COMMENCEE,   // statut de l'action
                                        0,                      // Etape actuelle
                                        2,                      // Nombre d'étapes
                                        ACTION_ACTIONNEURS,     // Type de l'étape
                                        {0, 0, 0}};             // Destination de l'étape (si pertinent)
    actionStatutType trajStatut;
    enum {
        GOTO_FISH_START = 0,
        GOTO_FISH_END = 1,
        FINI = 255
    } etape = infoAction.etapeEnCours;

    infoAction.statut = ACTION_PAS_COMMENCEE;
//    switch (option) {
//        case RESET_ACTION:
//            etape = FINI;
//            infoAction.statut = ACTION_FINIE;
//            break;
//        case DEFAULT_ACTION:
//            etape = GOTO_FISH_START;
//            infoAction.statut = ACTION_EN_COURS;
            
//            break;
//        default:
//            break;
//    }
        switch (etape) {
            case GOTO_FISH_START:
                trajStatut = trajectoryBasicAction(Fish_start);
                if (trajStatut == ACTION_FINIE) {
                    SortirAimant();
                    ElectroAimant=1;
                    while(AimantIsMoving()){}
                    infoAction.etapeEnCours = GOTO_FISH_END;
                    etape= GOTO_FISH_END;
                    
                    
                }
                else  if (trajStatut == ACTION_ERREUR) {
                    infoAction.statut = ACTION_REMISE;
                    etape = FINI;
                }
                break;
            case GOTO_FISH_END:
                RentrerAimant();
                while(AimantIsMoving()){}
                trajStatut = trajectoryBasicAction(Fish_net);
                if (trajStatut == ACTION_FINIE) {
                    SortirAimant();
                    while(AimantIsMoving()){}
                    ElectroAimant=0;
                    infoAction.statut = ACTION_FINIE;
                    etape = FINI;
                    
                    
                }
               if (trajStatut == ACTION_ERREUR) {
                    infoAction.statut = ACTION_REMISE;
                    etape = FINI;
                    SortirAimant();
                    while(AimantIsMoving()){}
                    ElectroAimant=0;
                }
           //    if (compareXY(propulsionGetPosition(), Fish_bordure)) {      // on rentre le bras pour ne pas toucher le clap de l'adversaire
           //         RentrerAimant();
           //     }
                break;
            default:
                break;
}
    return (infoAction);
}

infoActionType clapChezNousJaune(int option) {
    static infoActionType infoAction = {ACTION_PAS_COMMENCEE,   // statut de l'action
                                        0,                      // Etape actuelle
                                        4,                      // Nombre d'étapes
                                        ACTION_ACTIONNEURS,     // Type de l'étape
                                        {0, 0, 0}};             // Destination de l'étape (si pertinent)
    actionStatutType trajStatut;
    enum {
        GOTO_CLAP1_START = 0,
        DEPLOIEMENT_BRAS = 1,
        GOTO_CLAP2_END = 2,
        REPLIEMENT_BRAS = 3,
        GOTO_CLAP2_START = 4,
        GOTO_CLAP1_END = 5,
        FINI = 255
    } etape = GOTO_CLAP1_START;

    infoAction.statut = ACTION_PAS_COMMENCEE;
    switch (option) {
        case RESET_ACTION:
            rentrerServoClap();
            etape = FINI;
            infoAction.statut = ACTION_FINIE;
            break;
        case DEFAULT_ACTION:
            etape = GOTO_CLAP1_START;
            infoAction.statut = ACTION_EN_COURS;
            break;
        case CLAP1_ONLY:
            etape = GOTO_CLAP1_START;
            infoAction.statut = ACTION_EN_COURS;
            break;
        case CLAP2_ONLY:
            etape = GOTO_CLAP2_START;
            infoAction.statut = ACTION_EN_COURS;
            break;
        default:
            break;
    }
    while (etape != FINI) {
        switch (etape) {
            case GOTO_CLAP1_START:
                trajStatut = trajectoryBasicAction(clap1StartPos);
                if (trajStatut == ACTION_FINIE) {
                    etape = DEPLOIEMENT_BRAS;
                } else if (trajStatut == ACTION_ERREUR) {
                    infoAction.statut = ACTION_REMISE;
                    etape = FINI;
                }
                break;
            case GOTO_CLAP2_START:
                trajStatut = trajectoryBasicAction(clap2StartPos);
                if (trajStatut == ACTION_FINIE) {
                    etape = DEPLOIEMENT_BRAS;
                } else if (trajStatut == ACTION_ERREUR) {
                    infoAction.statut = ACTION_REMISE;
                    etape = FINI;
                }
                break;
            case DEPLOIEMENT_BRAS:
                sortirServoClap();
                // on ne met pas de délai, on suppose que le bras sera sorti à temps pdt le mouvment
                if (option == CLAP1_ONLY) {
                    etape = GOTO_CLAP1_END;
                } else {
                    etape = GOTO_CLAP2_END;
                }
                break;
            case GOTO_CLAP1_END:
                trajStatut = trajectoryBasicAction(clap1EndPos);
                if (trajStatut == ACTION_FINIE) {
                    etape = REPLIEMENT_BRAS;
                } else if (trajStatut == ACTION_ERREUR) {
                    infoAction.statut = ACTION_REMISE;
                    etape = FINI;
                }
                break;
            case GOTO_CLAP2_END:
                trajStatut = trajectoryBasicAction(clap2EndPos);
                if (trajStatut == ACTION_FINIE) {
                    etape = REPLIEMENT_BRAS;
                } else if (trajStatut == ACTION_ERREUR) {
                    infoAction.statut = ACTION_REMISE;
                    etape = FINI;
                }
                if (compareXY(propulsionGetPosition(), Fish_bordure)) {      // on rentre le bras pour ne pas toucher le clap de l'adversaire
                    rentrerServoClap();
                }
                if (compareXY(propulsionGetPosition(), clap2StartPos)) {    // on ressort le bras pour notre 2ème clap
                    sortirServoClap();
                }
                break;
            case REPLIEMENT_BRAS:
                rentrerServoClap();
                infoAction.statut = ACTION_FINIE;
                etape = FINI;
                break;
            default:
                break;
        }
    }

    return (infoAction);
}



//	unsigned int detObstAvantStatut[5];				//<! Statut de la détection d'obstacle à l'avant du robot.
//                        switch (actionChoisie.action->etapeEnCours) {
//                            case ACTION_PROPULSION:
//                                switch (propulsionGetStatus()) {
//                                    case RELATIVE_MOVE:
//                                    case TRAJECTORY:
//                                        // on attend que le mouvement soit fini
//                                        break;
//                                    case STANDING:
//                                        // le mouvement est fini, on passe à l'étape suivante
//                                        indiceEtape++;
//                                        etatLogique = INIT_ETAPE;
//                                        break;
//                                    case TRAJ_START_OUT:
//                                    case TRAJ_END_OUT:
//                                    case TRAJ_START_OBS:
//                                    case TRAJ_END_OBS:
//                                    case TRAJ_NO_WAY:
//                                        // la rajectoire n'a pas trouvé de chemin valable, on abandonne (A AMELIORER)
//                                        matchStatus = OVER;
//                                        break;
//                                    case TEST:  // ne doit jamais arriver en match, on repasse la prop en STANDING
//                                        propulsionDisable();
//                                        while(propulsionGetStatus() != DISABLED);       // on attend que l'ordre soit exécuté
//                                        propulsionEnable();
//                                        while(propulsionGetStatus() != STANDING);   // on attend que l'ordre soit exécuté
//                                        etatLogique = INIT_ETAPE;                   // on recommence l'étape (bonne idée ?)
//                                        break;
//                                    default:    // ne doit jamais arriver
//                                        indiceEtape++;
//                                        etatLogique = INIT_ETAPE;
//                                        break;
//                                }
//                                if (detObstAvantStatut[0] && SHARPS_ENABLE) {
//                                    propulsionStopNow();
//                                    etatLogique = INIT_ETAPE;
//                                }
//                                break;
//                            case ACTION_ACTIONNEURS:
//                                if (ActionGetStatus() == WAIT) {
//                                    indiceEtape++;
//                                    etatLogique = INIT_ETAPE;
//                                }
//                                break;
//                            default:
//                                indiceEtape++;
//                                etatLogique = INIT_ETAPE;
//                                break;
//                        }
//						break;
//					case IDLE:
//						break;
//					default:
//						break;
*/