#include "configware.h"
#include "BLDC.h"
#include "../libdspic/pps.h"
#include "../libdspic/pwm.h"
#include "../libdspic/timers.h"
#include <xc.h>


#define PWM_PERIOD	400
#define PWM_MIN		1   //PWM_PERIOD/100
#define PWM_MAX		399	//(PWM_PERIOD*99)/100

// Pattes du driver moteurs
#define PWM_RA          P1DC1
#define PWM_RB          P1DC2
#define PWM_RC          OC2RS
#define PWM_LA          OC3RS
#define PWM_LB          OC4RS
#define PWM_LC          OC1RS
#define RST_RAn         LATBbits.LATB15
#define RST_RAn_TRIS    TRISBbits.TRISB15
#define RST_RBn         LATAbits.LATA7
#define RST_RBn_TRIS    TRISAbits.TRISA7
#define RST_RCn         LATAbits.LATA10
#define RST_RCn_TRIS    TRISAbits.TRISA10
#define RST_LAn         LATAbits.LATA8
#define RST_LAn_TRIS    TRISAbits.TRISA8
#define RST_LBn         LATCbits.LATC1
#define RST_LBn_TRIS    TRISCbits.TRISC1
#define RST_LCn         LATBbits.LATB3
#define RST_LCn_TRIS    TRISBbits.TRISB3
#define HALL_RA         PORTCbits.RC7
#define HALL_RB         PORTCbits.RC8
#define HALL_RC         PORTCbits.RC9
#define HALL_LA         PORTBbits.RB8
#define HALL_LB         PORTBbits.RB9
#define HALL_LC         PORTCbits.RC6


int hallValueR, hallValueL;
int oldHallValueR, oldHallValueL;
int s16MotVt, s16MotVr;										// Vitesses linéaire et angulaire en tick/period
int s16TmpLeft = 0, s16TmpRight = 0;
int s16HallCntR = 0; int s16HallCntL = 0;
int s16OldHallCntR = 0; int s16OldHallCntL = 0;				// buffer des anciennes valeurs des capteurs à effet Hall
struct {
	int rightPwm;
	int leftPwm;
	int rightCw;
	int leftCw;
} privateBldcPwm;


inline void BldcUpdateSpeed(void);

// Change Notification interrupt : détermine la nouvelle phase des moteurs BLDC et met à jour les compteurs de ticks moteurs
// dans le sens horlogique, un moteur BLDC suit la séquence de phases suivante :
// 1-3-2-6-4-5, en considérant les signaux des capteurs à effet Hall comme un nombre binaire : CBA
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
	IFS1bits.CNIF = 0;											// clear IF
	oldHallValueR = hallValueR;
	oldHallValueL = hallValueL;
	hallValueR = HALL_RC*4 + HALL_RB*2 + HALL_RA*1;
	hallValueL = HALL_LC*4 + HALL_LB*2 + HALL_LA*1;
    if (hallValueR != oldHallValueR) {
		switch (hallValueR) {
			case 1:
				if (oldHallValueR == 3) s16HallCntR++;   else   s16HallCntR--;
				break;
			case 3:
				if (oldHallValueR == 2) s16HallCntR++;   else   s16HallCntR--;
				break;
			case 2:
				if (oldHallValueR == 6) s16HallCntR++;   else   s16HallCntR--;
				break;
			case 6:
				if (oldHallValueR == 4) s16HallCntR++;   else   s16HallCntR--;
				break;
			case 4:
				if (oldHallValueR == 5) s16HallCntR++;   else   s16HallCntR--;
				break;
			case 5:
				if (oldHallValueR == 1) s16HallCntR++;   else   s16HallCntR--;
				break;
			default:
				// TODO : gérer les cas d'erreurs de lecture des capteurs à effet Hall
				break;
		}
    } 
    if(hallValueL !=oldHallValueL) {
		switch (hallValueL) {
			case 1:
				if (oldHallValueL == 3) s16HallCntL++;   else   s16HallCntL--;
				break;
			case 3:
				if (oldHallValueL == 2) s16HallCntL++;   else   s16HallCntL--;
				break;
			case 2:
				if (oldHallValueL == 6) s16HallCntL++;   else   s16HallCntL--;
				break;
			case 6:
				if (oldHallValueL == 4) s16HallCntL++;   else   s16HallCntL--;
				break;
			case 4:
				if (oldHallValueL == 5) s16HallCntL++;   else   s16HallCntL--;
				break;
			case 5:
				if (oldHallValueL == 1) s16HallCntL++;   else   s16HallCntL--;
				break;
			default:
				// TODO : gérer les cas d'erreurs de lecture des capteurs à effet Hall
				break;
		}
    }    
    BldcUpdateSpeed(); // on applique les nouvelles commandes aux moteurs
}


void motorsInit(void) {
	// assignation des I/Os des PWMs
	RPOR1bits.RP2R = 18;	// OC1 -> RP2	(PWM_RC)
	RPOR6bits.RP12R = 19;	// OC2 -> RP12	(PWM_LC)
	RPOR9bits.RP18R = 20;	// OC3 -> RP18	(PWM_RA)
	RPOR8bits.RP16R = 21;	// OC4 -> RP16	(PWM_RB)
	motorsDisable();			// Initialement, les moteurs sont désactivés
	// configuration des resets en sortie
	RST_RAn_TRIS = 0;
	RST_RBn_TRIS = 0;
	RST_RCn_TRIS = 0;
	RST_LAn_TRIS = 0;
	RST_LBn_TRIS = 0;
	RST_LCn_TRIS = 0;
    /* Configure Timer 2 */
	T2CONbits.TON = 0;			// Stop any 16-bit Timer2 operation
	T2CONbits.TCKPS = 0;		// Prescaler 1:1
	TMR2 = 0;					// Clear Timer
	PR2 = PWM_PERIOD;			// Load period value : 50us = 2000 * 25ns (40MIPS)
	T2CONbits.TON = 1;			// Start Timer
	/* Configure the OC modules */
	OC1RS = 0;					// Initialement, on veut un rapport cyclique nul
	OC1R = 0;					// On initialise aussi OCxRS pour éviter un glitch à la 1ere période
	OC1CONbits.OCM = 6;			// mode PWM
	OC2RS = 0;
	OC2R = 0;
	OC2CONbits.OCM = 6;
	OC3RS = 0;
	OC3R = 0;
	OC3CONbits.OCM = 6;
	OC4R = 0;
	OC4RS = 0;
	OC4CONbits.OCM = 6;
	// configuration des MCPWM
	P1TPER = PWM_PERIOD;		// définit la fréquence des PWM (20kHZ)
	PWM1CON1bits.PEN2L = 1;		// définit PWM1L1 comme sortie du MCPWM
	PWM1CON1bits.PEN1H = 1;		// définit PWM1H2 comme sortie du MCPWM
	PWM1CON1bits.PMOD1 = 1;
	PWM1CON1bits.PMOD2 = 1;
	P1TCONbits.PTEN = 1;		// Active le module PWM
	// Activation des interruptions pour les pattes CN des capteurs à effet Hall
    CNEN2bits.CN17IE = 1;
    CNEN2bits.CN18IE = 1;
    CNEN2bits.CN21IE = 1;
    CNEN2bits.CN22IE = 1;
    CNEN2bits.CN19IE = 1;
    CNEN2bits.CN20IE = 1;
	// TODO : vérifier si c'est nécessaire
    //CNPU2 = 0x01E6; // enable internal pullups
    IFS1bits.CNIF = 0; // clear CNIF
    IEC1bits.CNIE = 1; // enable CN interrupt
	// Lecture de la position initiale du moteur
	oldHallValueR = HALL_RC*4 + HALL_RB*2 + HALL_RA*1;
	//oldHallValueR = 2;
	oldHallValueL = HALL_LC*4 + HALL_LB*2 + HALL_LA*1;
//	oldHallValueL = 2;
	hallValueR = oldHallValueR;
	hallValueL = oldHallValueL;
	privateBldcPwm.rightPwm = 0;
	privateBldcPwm.leftPwm = 0;
	privateBldcPwm.rightCw = 0;
	privateBldcPwm.leftCw = 0;
	motorsDisable();
}

void motorsEnable(void) {
    PWM_RA = 0;   PWM_RB = 0;   PWM_RC = 0;
    PWM_LA = 0;   PWM_LB = 0;   PWM_LC = 0;
	RST_RAn = 1;   RST_RBn = 1;   RST_RCn = 1;
	RST_LAn = 1;   RST_LBn = 1;   RST_LCn = 1;
}

void motorsDisable(void) {
    PWM_RA = 0;   PWM_RB = 0;   PWM_RC = 0;
    PWM_LA = 0;   PWM_LB = 0;   PWM_LC = 0;
	RST_RAn = 0;   RST_RBn = 0;   RST_RCn = 0;
	RST_LAn = 0;   RST_LBn = 0;   RST_LCn = 0;
}


void motorsSetSpeed(float dutyCycleRight, float dutyCycleLeft) {
	// TODO ajouter une saturation pour le rapport cyclique max
	if (dutyCycleRight >= 0) {
		privateBldcPwm.rightPwm = (int)(dutyCycleRight*PWM_PERIOD);
		privateBldcPwm.rightCw = 0;
	} else {
		privateBldcPwm.rightPwm = -(int)(dutyCycleRight*PWM_PERIOD);
		privateBldcPwm.rightCw = 1;
	}
	if (dutyCycleLeft >= 0) {
		privateBldcPwm.leftPwm = (int)(dutyCycleLeft*PWM_PERIOD);
		privateBldcPwm.leftCw = 1;
	} else {
		privateBldcPwm.leftPwm = -(int)(dutyCycleLeft*PWM_PERIOD);
		privateBldcPwm.leftCw = 0;
	}
	if (privateBldcPwm.rightPwm > PWM_MAX) {
		privateBldcPwm.rightPwm = PWM_MAX;
	}
	if (privateBldcPwm.leftPwm > PWM_MAX) {
		privateBldcPwm.leftPwm = PWM_MAX;
	}
	BldcUpdateSpeed();
}


inline void BldcUpdateSpeed(void) {
	if (privateBldcPwm.rightCw == 1) {
		switch (hallValueR) {
			case 1:																		// phase 1
				PWM_RA = 2*privateBldcPwm.rightPwm; PWM_RB = 0; PWM_RC = PWM_MIN;			// A-high, B-HiZ, C-low
				RST_RAn = 1;   RST_RBn = 0;   RST_RCn = 1;
				break;
			case 2:																		//phase 2
				PWM_RA = PWM_MIN; PWM_RB = 2*privateBldcPwm.rightPwm; PWM_RC = 0;				// A-low, B-high, C-HiZ
				RST_RAn = 1;   RST_RBn = 1;   RST_RCn = 0;
				break;
			case 3:																		//phase 3
				PWM_RA = 0; PWM_RB = 2*privateBldcPwm.rightPwm; PWM_RC = PWM_MIN;				// A-HiZ, B-high, C-low
				RST_RAn = 0;   RST_RBn = 1;   RST_RCn = 1;
				break;
			case 4:																		//phase 4
				PWM_RA = 0; PWM_RB = PWM_MIN; PWM_RC = privateBldcPwm.rightPwm;				// A-HiZ, B-low, C-high
				RST_RAn = 0;   RST_RBn = 1;   RST_RCn = 1;
				break;
			case 5:																		//phase 5
				PWM_RA = 2*privateBldcPwm.rightPwm;   PWM_RB = PWM_MIN;   PWM_RC = 0;		// A-high, B-low, C-HiZ
				RST_RAn = 1;   RST_RBn = 1;   RST_RCn = 0;
				break;
			case 6:																		//phase 6
				PWM_RA = PWM_MIN; PWM_RB = 0; PWM_RC = privateBldcPwm.rightPwm;				// A-low, B-HiZ, C-high
				RST_RAn = 1;   RST_RBn = 0;   RST_RCn = 1;
				break;
			default:
				PWM_RA = 0; PWM_RB = 0; PWM_RC = 0;
				RST_RAn = 0;   RST_RBn = 0;   RST_RCn = 0;
				break;
		}
	} else {
		switch (hallValueR) {
			case 1:																		// phase 1
				PWM_RA = PWM_MIN; PWM_RB = 0; PWM_RC = privateBldcPwm.rightPwm;				// A-low, B-HiZ, C-high
				RST_RAn = 1;   RST_RBn = 0;   RST_RCn = 1;
				break;
			case 2:																		//phase 2
				PWM_RA = 2*privateBldcPwm.rightPwm; PWM_RB = PWM_MIN; PWM_RC = 0;			// A-high, B-low, C-HiZ
				RST_RAn = 1;   RST_RBn = 1;   RST_RCn = 0;
				break;
			case 3:																		//phase 3
				PWM_RA = 0; PWM_RB = PWM_MIN; PWM_RC = privateBldcPwm.rightPwm;				// A-HiZ, B-low, C-high
				RST_RAn = 0;   RST_RBn = 1;   RST_RCn = 1;
				break;
			case 4:																		//phase 4
				PWM_RA = 0; PWM_RB =2*privateBldcPwm.rightPwm; PWM_RC = PWM_MIN;				// A-HiZ, B-high, C-low
				RST_RAn = 0;   RST_RBn = 1;   RST_RCn = 1;
				break;
			case 5:																		//phase 5
				PWM_RA = PWM_MIN;   PWM_RB = 2*privateBldcPwm.rightPwm;   PWM_RC = 0;			// A-low, B-high, C-HiZ
				RST_RAn = 1;   RST_RBn = 1;   RST_RCn = 0;
				break;
			case 6:																		//phase 6
				PWM_RA = 2*privateBldcPwm.rightPwm; PWM_RB = 0; PWM_RC = PWM_MIN;			// A-high, B-HiZ, C-low
				RST_RAn = 1;   RST_RBn = 0;   RST_RCn = 1;
				break;
			default:
				PWM_RA = 0; PWM_RB = 0; PWM_RC = 0;
				RST_RAn = 0;   RST_RBn = 0;   RST_RCn = 0;
				break;
		}
	}
	if (privateBldcPwm.leftCw == 1) {
		switch (hallValueL) {
			case 1:																		// phase 1
				PWM_LA = privateBldcPwm.leftPwm; PWM_LB = 0; PWM_LC = PWM_MIN;				// A-high, B-HiZ, C-low
				RST_LAn = 1;   RST_LBn = 0;   RST_LCn = 1;
				break;
			case 2:																		//phase 2
				PWM_LA = PWM_MIN; PWM_LB = privateBldcPwm.leftPwm; PWM_LC = 0;				// A-low, B-high, C-HiZ
				RST_LAn = 1;   RST_LBn = 1;   RST_LCn = 0;
				break;
			case 3:																		//phase 3
				PWM_LA = 0; PWM_LB = privateBldcPwm.leftPwm; PWM_LC = PWM_MIN;				// A-HiZ, B-high, C-low
				RST_LAn = 0;   RST_LBn = 1;   RST_LCn = 1;
				break;
			case 4:																		//phase 4
				PWM_LA = 0; PWM_LB = PWM_MIN; PWM_LC = privateBldcPwm.leftPwm;				// A-HiZ, B-low, C-high
				RST_LAn = 0;   RST_LBn = 1;   RST_LCn = 1;
				break;
			case 5:																		//phase 5
				PWM_LA = privateBldcPwm.leftPwm;   PWM_LB = PWM_MIN;   PWM_LC = 0;			// A-high, B-low, C-HiZ
				RST_LAn = 1;   RST_LBn = 1;   RST_LCn = 0;
				break;
			case 6:																		//phase 6
				PWM_LA = PWM_MIN; PWM_LB = 0; PWM_LC = privateBldcPwm.leftPwm;				// A-low, B-HiZ, C-high
				RST_LAn = 1;   RST_LBn = 0;   RST_LCn = 1;
				break;
			default:
				PWM_LA = 0; PWM_LB = 0; PWM_LC = 0;
				RST_LAn = 0;   RST_LBn = 0;   RST_LCn = 0;
				break;
		}
	} else {
		switch (hallValueL) {
			case 1:																		// phase 1
				PWM_LA = PWM_MIN; PWM_LB = 0; PWM_LC = privateBldcPwm.leftPwm;				// A-low, B-HiZ, C-high
				RST_LAn = 1;   RST_LBn = 0;   RST_LCn = 1;
				break;
			case 2:																		//phase 2
				PWM_LA = privateBldcPwm.leftPwm; PWM_LB =PWM_MIN; PWM_LC = 0;				// A-high, B-low, C-HiZ
				RST_LAn = 1;   RST_LBn = 1;   RST_LCn = 0;
				break;
			case 3:																		//phase 3
				PWM_LA = 0; PWM_LB = PWM_MIN; PWM_LC = privateBldcPwm.leftPwm;				// A-HiZ, B-low, C-high
				RST_LAn = 0;   RST_LBn = 1;   RST_LCn = 1;
				break;
			case 4:																		//phase 4
				PWM_LA = 0; PWM_LB = privateBldcPwm.leftPwm; PWM_LC = PWM_MIN;				// A-HiZ, B-high, C-low
				RST_LAn = 0;   RST_LBn = 1;   RST_LCn = 1;
				break;
			case 5:																		//phase 5
				PWM_LA = PWM_MIN;   PWM_LB = privateBldcPwm.leftPwm;   PWM_LC = 0;			// A-low, B-high, C-HiZ
				RST_LAn = 1;   RST_LBn = 1;   RST_LCn = 0;
				break;
			case 6:																		//phase 6
				PWM_LA = privateBldcPwm.leftPwm; PWM_LB = 0; PWM_LC = PWM_MIN;				// A-high, B-HiZ, C-low
				RST_LAn = 1;   RST_LBn = 0;   RST_LCn = 1;
				break;
			default:
				PWM_LA = 0; PWM_LB = 0; PWM_LC = 0;
				RST_LAn = 0;   RST_LBn = 0;   RST_LCn = 0;
				break;
		}
	}
}
