/*
 * File:   ax12.c
 * Author: DenisT
 *
 * Created on 16 février 2016, 17:45
 */

#include "../libdspic/clock.h"
#include "../libdspic/dynamixel.h"
#include "../libdspic/CanDspic.h"
#include "../libdspic/pps.h"
#include <xc.h>
#include <libpic30.h>
 dynamixelType dyna;
void initAX12(void){
  
    ppsOutConfig(PPS_U1TX, 23);
    ppsInConfig(PPS_U1RX, 22);
    dynaConfigBus(UART_CH1,             // canal UART
                  1000000,              // baudrate de l'UART (1MHz par défaut)
                  TIMER_4);             // ID du timer à utiliser pour les timeout 
    
}
void AX12SetAngle(int pos) {
             // objet décrivant l'état de l'AX-12
    dynaConfigMot(&dyna, 4);            // initialise "l'objet" dyna
    dynaSetGoalSpeed(&dyna, 256);
    dynaSetGoalPosition(&dyna, pos);
}

int AimantIsMoving(void){
int move=dynaIsMoving(&dyna);
return(move);
}

void SortirAimant(void){
    AX12SetAngle(250);
}
void RentrerAimant(void){
AX12SetAngle(130);
}

void OuvrirPince(void){
AX12SetAngle(100);
}
void FermerPince(void){
AX12SetAngle(0);
}