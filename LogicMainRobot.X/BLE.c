/*
 * File:   BLE.c
 * Author: DenisT
 *
 * Created on 4 avril 2016, 17:56
 */

#include "dataTypes.h"
#include "../libdspic/clock.h"
#include "../libdspic/CanDspic.h"
#include "../libdspic/pps.h"
#include "../libdspic/uart.h"
#include <libpic30.h>
#include <xc.h>
#include "gestionPropulsion.h"
#include <libpic30.h>
#include <pps.h>
#include "BLE.h"

unsigned char END_MSG = 0x0D;
char dataSF[4] = "SF,1";
int NbOctets=0;
unsigned char dataSS[11] = "SS,30000000";
StatutsRadio StatutRadio;
#define RADIO_RX_DATA_SIZE		250					//!< taille du buffer de réception
unsigned char radioRxData[RADIO_RX_DATA_SIZE];		//!< buffer de réception
int radioRxDataNb = 0;								//!< nombre d'octets en attente dans le buffer de réception
int radioRxDataStartPtr = 0;						//!< pointeur vers le plus ancien octet du buffer de réception
int radioRxDataEndPtr = 0;							//!< pointeur vers le plus récent octet du buffer de réception
unsigned char dataSR[11] = "SR,32000000";
#define RADIO_TX_DATA_SIZE		250					//!< taille du buffer d'émission
unsigned char radioTxData[RADIO_TX_DATA_SIZE];		//!< buffer d'émission
int radioTxDataNb = RADIO_TX_DATA_SIZE;				//!< place disponible (en octets) dans le buffer d'émission
int radioTxDataStartPtr = 0;						//!< pointeur vers le plus ancien octet du buffer d'émission
int radioTxDataEndPtr = 0;							//!< pointeur vers le plus récent octet du buffer d'émission
unsigned char dataReset[3] = "R,1";

obstacleType AllyPos={16,16,16};
int TaskActionUpToDate = 0;

char scan[20];
int TaskAction[2];    
#define SW_WAKE         (LATCbits.LATC0)
// ascii-'0'
void initBLE(void) {
 
    ppsOutConfig(PPS_U2TX, 8);
    ppsInConfig(PPS_U2RX, 9);
    uartConfig(UART_CH2, 115200, UART_8N1_NO_HANDSHAKE);
    IFS1bits.U2TXIF = 0;
    uartRxIsrEnable(UART_CH2);
    uartTxIsrEnable(UART_CH2);
    SW_WAKE = 1;            // Passe en mode commande
    while (StatutRadio != MODE_COMMAND);
    radioSendString(dataSF);
    radioSendString(dataSS);
    radioSendString(dataSR);
    radioSendString(dataReset);
    while (StatutRadio != CONNECTED);
    radioSendString("I");
}
// on remplit un buffer software quand l'hadrwarre est vide on check si l'autre est vide ou pas (intterrupt) si non on remplit l'hardware.

void __attribute__((__interrupt__, auto_psv)) _U2TXInterrupt(void) {
       IFS1bits.U2TXIF = 0;
	while ((radioTxDataNb < RADIO_TX_DATA_SIZE) && uartTxReady(UART_CH2)) {
		uartSendChar(UART_CH2,radioTxData[radioTxDataStartPtr]);

		radioTxDataStartPtr++;

		if (radioTxDataStartPtr >= RADIO_TX_DATA_SIZE) {
			radioTxDataStartPtr = 0;
		}
		// data counter is decremented
		radioTxDataNb++;
	}
}
 
void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void){
    IFS1bits.U2RXIF = 0;             // Rentre dans l'interrupt mais vide ???
    while (U2STAbits.URXDA)	{
        radioRxDataNb++;
		radioRxData[radioRxDataEndPtr] = U2RXREG;	
		radioRxDataEndPtr++;
	if (radioRxDataEndPtr == RADIO_RX_DATA_SIZE) {
			radioRxDataEndPtr = 0;
    }
    }
    // Faudrait check la gueule de se qu'il rentre et update des variables avec
    // genre AllyPos
    // on passe ici que pdt l'init et la connexion
    if (radioRxData[radioRxDataEndPtr-1] == 0x0A && StatutRadio != CONNECTED){
        DectectedReponse reponse = detectReponse(radioRxData,radioRxDataEndPtr,radioRxDataNb);
        switch (StatutRadio){
            case(UNINITIALISED):  // on check si on est en mode commande
                StatutRadio = MODE_COMMAND;
                if (reponse != CMD){
                    StatutRadio = UNINITIALISED;
                }
                radioRxDataNb =0;
                break;
            case(MODE_COMMAND):
                switch(reponse){
                    case AOK:
                        radioRxDataNb =0;
                        break;
                    case REBOOT:
                        radioRxDataNb =0;
                        break;
                    case CMD:
                        radioRxDataNb =0;
                        break;
                    case CONNECTED_BLE:
                        radioRxDataNb =0;
                        radioRxDataStartPtr = radioRxDataEndPtr;
                        StatutRadio = CONNECTED;
                        
                        break;
                    default:
                        radioRxDataNb =0;
                        break;
                    //ResetBLE(); 
                    // on est jsute en AOK  ou en END si erreur
                }
                break;
            case(NOT_CONNECTED):
                break;
            case(CONNECTED):
                break;
            default:
                 break;  
    }
       
}
    else if (StatutRadio == CONNECTED){
        scan[radioRxDataNb-1] = radioRxData[radioRxDataEndPtr-1];
        if (scan[radioRxDataNb-1] == '@'){ // Fin de message
            updateData(scan);
            radioRxDataNb = 0;
            scan[20];
        }
    }
}

void updateData(char* data){
    update whatToUpdate;
    if (*(data) == 'T'){
        whatToUpdate = TASK_ACTION;
        updateTaskAction(data);
    }   
    else if (*(data) == 'P'){
        whatToUpdate = POSITION_ALLY;
        updatePosAlly(data);
    }
    else{
        whatToUpdate= OTHER;
}
}

void updateTaskAction(char* data){
    TaskAction[0]=(*(data+1) - '0');
    TaskAction[1]=(*(data+3) - '0');
    TaskActionUpToDate = 1;
}

int isTaskActionUpToDate(void){
    return(TaskActionUpToDate);
}

int* getTaskAction(void){
    if (TaskActionUpToDate = 1){
        TaskActionUpToDate = 0;
    return(TaskAction);
    }
}

void updatePosAlly(char* data){

    AllyPos.x = (*(data+2)-'0')*1000 + (*(data+3)-'0')*100 + (*(data+4)-'0')*10 + (*(data+5)-'0');
    AllyPos.y = (*(data+7)-'0')*1000 + (*(data+8)-'0')*100 + (*(data+9)-'0')*10 + (*(data+10)-'0');

    //AllyPos.alpha = (*data+7)*1000 + (*data+8)*100 + (*data+9)*10 + (*data+10);
}

DectectedReponse detectReponse(char* data,int start,int nbr){
    // AOK CMD REBOOT END ERR CONNECTED
   // int i = 0;
	//while (*(data+i) != 0x0D) { // tant qu'on est pas sur une fin de mot
    DectectedReponse reponse;
    reponse = ERR;
    data = data + start-nbr;  // on place le pointeur au début de la réponse
        if (*(data) == 'C'){
            if (*(data+1) == 'M'){
                if (*(data+2) == 'D'){
                   reponse =CMD;
                }
            }
            else  if (*(data+1) == 'o'){
                if (*(data+2) == 'n'){
                    reponse= CONNECTED_BLE;
                }
            }
        }    
        if (*(data) == 'A'){
            if (*(data+1) == 'O'){
                if (*(data+2) == 'K'){
                    reponse=AOK;
                }
            }
        }
        if (*(data) == 'R'){
            if (*(data+1) == 'e'){
                if (*(data+2) == 'b'){
                    reponse=REBOOT;
                }
            }
        }
    

		//i++;
	
            return (reponse);
}



inline char radioGetChar(void) {
	char data;
	int test = 1;

	while(test) {
		uartRxIsrDisable(UART_CH2);								// on désactive l'interruption de réception pour manipuler les variables de l'ISR
		if(radioRxDataNb > 0) {							// on attend qu'il y ait au moins un octet à lire dans le buffer de réception
			radioRxDataNb--;									// on met à jour radioRxDataNb
			data = radioRxData[radioRxDataStartPtr];			// on lit l'octet le plus ancien du buffer de réception
			if (++radioRxDataStartPtr >= RADIO_RX_DATA_SIZE) {	// on met à jour le pointeur vers l'octet le plus ancien du buffer
				radioRxDataStartPtr = 0;
			}
			test = 0;
		}
		uartRxIsrEnable(UART_CH2);									// on réactive l'interruption
	}
	return(data);
}

inline void radioSendChar(char data) {
	int test = 1;

	while(test) {
		uartTxIsrDisable(UART_CH2);								// on désactive l'interruption de réception pour manipuler les variables de l'ISR
		if (radioTxDataNb > 0) {							// on attend qu'on puisse écrire au moins un octet dans le buffer d'émission)
			radioTxDataNb--;									// on met à jour radioTxDataNb
			radioTxData[radioTxDataEndPtr] = data;				// on écrit l'octet à la fin du buffer d'émission
			if (++radioTxDataEndPtr >= RADIO_TX_DATA_SIZE) {	// on met à jour le pointeur vers la fin du buffer
				radioTxDataEndPtr = 0;
			}
			test = 0;
		}
		uartTxIsrEnable(UART_CH2);									// on réactive l'interruption
	}
	if (U2STAbits.UTXBF == 0) {							// Si l'UART n'est pas en train d'envoyer un octet (le buffer d'émission était vide)
		IFS1bits.U2TXIF = 1;							// on active "manuellement" l'ISR pour démarrer l'envoi
	}
}

void radioSendString(char* data) {
	int i = 0;

	while (*(data+i) != 0) {
		radioSendChar(*(data+i));
		i++;
	}
    radioSendChar(END_MSG);
}

int radioGetInt(void) {
	union {
		int i;
		char c[2];
	} data;
	int i;

	for (i=0; i<2;i++) {
		data.c[i] = radioGetChar();
	}
	return(data.i);
}

void radioSendInt(int data) {
	radioSendChar((char)(data & 0xFF));			// on envoie l'octet de poids faible
	radioSendChar((char)((data >> 8) & 0xFF));		// on en voie l'octet de poids fort
}


float radioGetFloat(void) {
	union {
		float f;
		char c[4];
	} data;
	int i;

	for (i=0; i<4;i++) {
		data.c[i] = radioGetChar();
	}
	return(data.f);
}


void radioSendFloat(float data) {
	union {
		float f;
		char c[4];
	} tmp;
	int i;

	tmp.f = data;					// on copie le réel à envoyer dans la varaible temporaire pour pouvoir le manipuler
	for (i=0; i<4;i++) {
		radioSendChar(tmp.c[i]);	// on envoie les 4 octets du réel un par un
	}
}

void ResetBLE(void){
    while (StatutRadio != MODE_COMMAND);
    radioSendString(dataSF);
    radioSendString(dataSS);
    radioSendString(dataSR);
    radioSendString(dataReset);
    while (StatutRadio != CONNECTED);
}

inline int radioGetRxBufferSpace(void) {
	return (radioRxDataNb);
}

obstacleType getAllyPos(void){
    return(AllyPos);
}

