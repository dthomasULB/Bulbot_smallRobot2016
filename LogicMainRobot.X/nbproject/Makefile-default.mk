#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LogicMainRobot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LogicMainRobot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Can/CanAction.c ../libdspic/clock.c ../libdspic/pps.c ../libdspic/CanDspic.c ../libdspic/CanInterruptsDspic.c ../libdspic/servo.c ../libdspic/pwm.c ../libdspic/timers.c ../libdspic/adc.c ../libdspic/dynamixel.c ../libdspic/uart.c main.c timer.c spio.c gestionActions.c gestionPropulsion.c basicActions.c sharp.c ax12.c BLE.c servoClap.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360890593/CanAction.o ${OBJECTDIR}/_ext/289022629/clock.o ${OBJECTDIR}/_ext/289022629/pps.o ${OBJECTDIR}/_ext/289022629/CanDspic.o ${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o ${OBJECTDIR}/_ext/289022629/servo.o ${OBJECTDIR}/_ext/289022629/pwm.o ${OBJECTDIR}/_ext/289022629/timers.o ${OBJECTDIR}/_ext/289022629/adc.o ${OBJECTDIR}/_ext/289022629/dynamixel.o ${OBJECTDIR}/_ext/289022629/uart.o ${OBJECTDIR}/main.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/spio.o ${OBJECTDIR}/gestionActions.o ${OBJECTDIR}/gestionPropulsion.o ${OBJECTDIR}/basicActions.o ${OBJECTDIR}/sharp.o ${OBJECTDIR}/ax12.o ${OBJECTDIR}/BLE.o ${OBJECTDIR}/servoClap.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360890593/CanAction.o.d ${OBJECTDIR}/_ext/289022629/clock.o.d ${OBJECTDIR}/_ext/289022629/pps.o.d ${OBJECTDIR}/_ext/289022629/CanDspic.o.d ${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o.d ${OBJECTDIR}/_ext/289022629/servo.o.d ${OBJECTDIR}/_ext/289022629/pwm.o.d ${OBJECTDIR}/_ext/289022629/timers.o.d ${OBJECTDIR}/_ext/289022629/adc.o.d ${OBJECTDIR}/_ext/289022629/dynamixel.o.d ${OBJECTDIR}/_ext/289022629/uart.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/timer.o.d ${OBJECTDIR}/spio.o.d ${OBJECTDIR}/gestionActions.o.d ${OBJECTDIR}/gestionPropulsion.o.d ${OBJECTDIR}/basicActions.o.d ${OBJECTDIR}/sharp.o.d ${OBJECTDIR}/ax12.o.d ${OBJECTDIR}/BLE.o.d ${OBJECTDIR}/servoClap.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360890593/CanAction.o ${OBJECTDIR}/_ext/289022629/clock.o ${OBJECTDIR}/_ext/289022629/pps.o ${OBJECTDIR}/_ext/289022629/CanDspic.o ${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o ${OBJECTDIR}/_ext/289022629/servo.o ${OBJECTDIR}/_ext/289022629/pwm.o ${OBJECTDIR}/_ext/289022629/timers.o ${OBJECTDIR}/_ext/289022629/adc.o ${OBJECTDIR}/_ext/289022629/dynamixel.o ${OBJECTDIR}/_ext/289022629/uart.o ${OBJECTDIR}/main.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/spio.o ${OBJECTDIR}/gestionActions.o ${OBJECTDIR}/gestionPropulsion.o ${OBJECTDIR}/basicActions.o ${OBJECTDIR}/sharp.o ${OBJECTDIR}/ax12.o ${OBJECTDIR}/BLE.o ${OBJECTDIR}/servoClap.o

# Source Files
SOURCEFILES=../Can/CanAction.c ../libdspic/clock.c ../libdspic/pps.c ../libdspic/CanDspic.c ../libdspic/CanInterruptsDspic.c ../libdspic/servo.c ../libdspic/pwm.c ../libdspic/timers.c ../libdspic/adc.c ../libdspic/dynamixel.c ../libdspic/uart.c main.c timer.c spio.c gestionActions.c gestionPropulsion.c basicActions.c sharp.c ax12.c BLE.c servoClap.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/LogicMainRobot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360890593/CanAction.o: ../Can/CanAction.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360890593" 
	@${RM} ${OBJECTDIR}/_ext/1360890593/CanAction.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360890593/CanAction.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Can/CanAction.c  -o ${OBJECTDIR}/_ext/1360890593/CanAction.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360890593/CanAction.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360890593/CanAction.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/clock.o: ../libdspic/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/clock.c  -o ${OBJECTDIR}/_ext/289022629/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/pps.o: ../libdspic/pps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/pps.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/pps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/pps.c  -o ${OBJECTDIR}/_ext/289022629/pps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/pps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/pps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/CanDspic.o: ../libdspic/CanDspic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/CanDspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/CanDspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/CanDspic.c  -o ${OBJECTDIR}/_ext/289022629/CanDspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/CanDspic.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/CanDspic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o: ../libdspic/CanInterruptsDspic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/CanInterruptsDspic.c  -o ${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/servo.o: ../libdspic/servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/servo.c  -o ${OBJECTDIR}/_ext/289022629/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/servo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/servo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/pwm.o: ../libdspic/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/pwm.c  -o ${OBJECTDIR}/_ext/289022629/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/timers.o: ../libdspic/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/timers.c  -o ${OBJECTDIR}/_ext/289022629/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/adc.o: ../libdspic/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/adc.c  -o ${OBJECTDIR}/_ext/289022629/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/dynamixel.o: ../libdspic/dynamixel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/dynamixel.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/dynamixel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/dynamixel.c  -o ${OBJECTDIR}/_ext/289022629/dynamixel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/dynamixel.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/dynamixel.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/uart.o: ../libdspic/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/uart.c  -o ${OBJECTDIR}/_ext/289022629/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/timer.o: timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer.c  -o ${OBJECTDIR}/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/spio.o: spio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spio.o.d 
	@${RM} ${OBJECTDIR}/spio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spio.c  -o ${OBJECTDIR}/spio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/spio.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/spio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/gestionActions.o: gestionActions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gestionActions.o.d 
	@${RM} ${OBJECTDIR}/gestionActions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gestionActions.c  -o ${OBJECTDIR}/gestionActions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/gestionActions.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/gestionActions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/gestionPropulsion.o: gestionPropulsion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gestionPropulsion.o.d 
	@${RM} ${OBJECTDIR}/gestionPropulsion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gestionPropulsion.c  -o ${OBJECTDIR}/gestionPropulsion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/gestionPropulsion.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/gestionPropulsion.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/basicActions.o: basicActions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/basicActions.o.d 
	@${RM} ${OBJECTDIR}/basicActions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  basicActions.c  -o ${OBJECTDIR}/basicActions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/basicActions.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/basicActions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sharp.o: sharp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sharp.o.d 
	@${RM} ${OBJECTDIR}/sharp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sharp.c  -o ${OBJECTDIR}/sharp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sharp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/sharp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ax12.o: ax12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ax12.o.d 
	@${RM} ${OBJECTDIR}/ax12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ax12.c  -o ${OBJECTDIR}/ax12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ax12.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/ax12.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BLE.o: BLE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BLE.o.d 
	@${RM} ${OBJECTDIR}/BLE.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BLE.c  -o ${OBJECTDIR}/BLE.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BLE.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/BLE.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/servoClap.o: servoClap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/servoClap.o.d 
	@${RM} ${OBJECTDIR}/servoClap.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  servoClap.c  -o ${OBJECTDIR}/servoClap.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/servoClap.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/servoClap.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1360890593/CanAction.o: ../Can/CanAction.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360890593" 
	@${RM} ${OBJECTDIR}/_ext/1360890593/CanAction.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360890593/CanAction.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Can/CanAction.c  -o ${OBJECTDIR}/_ext/1360890593/CanAction.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360890593/CanAction.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360890593/CanAction.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/clock.o: ../libdspic/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/clock.c  -o ${OBJECTDIR}/_ext/289022629/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/clock.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/pps.o: ../libdspic/pps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/pps.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/pps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/pps.c  -o ${OBJECTDIR}/_ext/289022629/pps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/pps.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/pps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/CanDspic.o: ../libdspic/CanDspic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/CanDspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/CanDspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/CanDspic.c  -o ${OBJECTDIR}/_ext/289022629/CanDspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/CanDspic.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/CanDspic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o: ../libdspic/CanInterruptsDspic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/CanInterruptsDspic.c  -o ${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/CanInterruptsDspic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/servo.o: ../libdspic/servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/servo.c  -o ${OBJECTDIR}/_ext/289022629/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/servo.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/servo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/pwm.o: ../libdspic/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/pwm.c  -o ${OBJECTDIR}/_ext/289022629/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/pwm.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/timers.o: ../libdspic/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/timers.c  -o ${OBJECTDIR}/_ext/289022629/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/timers.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/adc.o: ../libdspic/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/adc.c  -o ${OBJECTDIR}/_ext/289022629/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/adc.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/dynamixel.o: ../libdspic/dynamixel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/dynamixel.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/dynamixel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/dynamixel.c  -o ${OBJECTDIR}/_ext/289022629/dynamixel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/dynamixel.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/dynamixel.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/289022629/uart.o: ../libdspic/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/289022629" 
	@${RM} ${OBJECTDIR}/_ext/289022629/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/289022629/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libdspic/uart.c  -o ${OBJECTDIR}/_ext/289022629/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/289022629/uart.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/289022629/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/timer.o: timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer.c  -o ${OBJECTDIR}/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timer.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/spio.o: spio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spio.o.d 
	@${RM} ${OBJECTDIR}/spio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spio.c  -o ${OBJECTDIR}/spio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/spio.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/spio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/gestionActions.o: gestionActions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gestionActions.o.d 
	@${RM} ${OBJECTDIR}/gestionActions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gestionActions.c  -o ${OBJECTDIR}/gestionActions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/gestionActions.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/gestionActions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/gestionPropulsion.o: gestionPropulsion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gestionPropulsion.o.d 
	@${RM} ${OBJECTDIR}/gestionPropulsion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gestionPropulsion.c  -o ${OBJECTDIR}/gestionPropulsion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/gestionPropulsion.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/gestionPropulsion.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/basicActions.o: basicActions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/basicActions.o.d 
	@${RM} ${OBJECTDIR}/basicActions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  basicActions.c  -o ${OBJECTDIR}/basicActions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/basicActions.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/basicActions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sharp.o: sharp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sharp.o.d 
	@${RM} ${OBJECTDIR}/sharp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sharp.c  -o ${OBJECTDIR}/sharp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sharp.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/sharp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ax12.o: ax12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ax12.o.d 
	@${RM} ${OBJECTDIR}/ax12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ax12.c  -o ${OBJECTDIR}/ax12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ax12.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/ax12.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/BLE.o: BLE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BLE.o.d 
	@${RM} ${OBJECTDIR}/BLE.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BLE.c  -o ${OBJECTDIR}/BLE.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BLE.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/BLE.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/servoClap.o: servoClap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/servoClap.o.d 
	@${RM} ${OBJECTDIR}/servoClap.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  servoClap.c  -o ${OBJECTDIR}/servoClap.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/servoClap.o.d"        -g -omf=elf   -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/servoClap.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/LogicMainRobot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/LogicMainRobot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/LogicMainRobot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/LogicMainRobot.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf   -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/LogicMainRobot.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
