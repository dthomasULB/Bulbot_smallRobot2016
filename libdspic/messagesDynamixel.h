/*
 * @file messagesDynamixel.h
 * @brief D»finition des diff»rents types de messages pour les servomoteurs Dynamixel.
 * @author bULBot 2011-2012
 * @details D»finition des instructions et des addresses dans la m»moire des servomoteurs.
 * Elles sont r»parties entre EEPROM (sauvegard»es) et RAM (volatile).
 */

#ifndef DEF_MESSAGESDYNAMIXEL_H
#define DEF_MESSAGESDYNAMIXEL_H


/*
 * Instructions (p19 Datasheet AX-12)
 */
#define INST_PING 0x01      // No action, used to obtain the status packet
#define INST_READ 0x02      // Reading values in control table
#define INST_WRITE_DATA 0x03     // Writing value to the control table
#define INST_REG_WRITE 0x04 // Write data when ACTION instruction is given
#define INST_ACTION 0x05    // trigger for the REG_WRITE instruction
#define INST_RESET 0x06     // Set default values for control table
#define INST_SYNC_WRITE 0x83    //Control many Dynamixel actuators at the same time

// ?
#define INST_DIGITAL_RESET 0x07
#define INST_SYSTEM_READ 0x0C
#define INST_SYSTEM_WRITE 0x0D

#define INST_SYNC_REG_WRITE 0x84


/*
 * CONTROL TABLE
 * Donn»es en EEPROM: sauvegard»es aprÀs la mise hors tension.
 * Voir la datasheet des Dynamixel pour les donn»es en lecture seule ou
 * en lecture/»criture.
 */

#define P_MODEL_NUMBER_L 0x0
#define P_MODEL_NUMBER_H 0x1
#define P_VERSION 0x2
#define P_ID 0x3
#define P_BAUD_RATE 0x4
#define P_RETURN_DELAY_TIME 0x5
#define P_CW_ANGLE_LIMIT_L 0x6
#define P_CW_ANGLE_LIMIT_H 0x7
#define P_CCW_ANGLE_LIMIT_L 0x8
#define P_CCW_ANGLE_LIMIT_H 0x9
#define P_SYSTEM_DATA2 0xA
#define P_LIMIT_TEMPERATURE 0xB
#define P_DOWN_LIMIT_VOLTAGE 0xC
#define P_UP_LIMIT_VOLTAGE 0xD
#define P_MAX_TORQUE_L 0xE
#define P_MAX_TORQUE_H 0xF
#define P_RETURN_LEVEL 0x10
#define P_ALARM_LED 0x11
#define P_ALARM_SHUTDOWN 0x12
#define P_OPERATING_MODE 0x13
#define P_DOWN_CALIBRATION_L 0x14
#define P_DOWN_CALIBRATION_H 0x15
#define P_UP_CALIBRATION_L 0x16
#define P_UP_CALIBRATION_H 0x17



/*
 * CONTROL TABLE
 * Donn»es en RAM: remises ? leur valeur initiale ? la mise sous tension.
 */
#define P_TORQUE_ENABLE 0x18
#define P_LED 0x19
#define P_CW_COMPLIANCE_MARGIN 0x1A
#define P_CCW_COMPLIANCE_MARGIN 0x1B
#define P_CW_COMPLIANCE_SLOPE 0x1C
#define P_CCW_COMPLIANCE_SLOPE 0x1D
#define P_GOAL_POSITION_L 0x1E
#define P_GOAL_POSITION_H 0x1F
#define P_GOAL_SPEED_L 0x20
#define P_GOAL_SPEED_H 0x21
#define P_TORQUE_LIMIT_L 0x22
#define P_TORQUE_LIMIT_H 0x23
#define P_PRESENT_POSITION_L 0x24
#define P_PRESENT_POSITION_H 0x25
#define P_PRESENT_SPEED_L 0x26
#define P_PRESENT_SPEED_H 0x27
#define P_PRESENT_LOAD_L 0x28
#define P_PRESENT_LOAD_H 0x29
#define P_PRESENT_VOLTAGE 0x2A
#define P_PRESENT_TEMPERATURE 0x2B
#define P_REGISTERED_INSTRUCTION 0x2C
#define P_PAUSE_TIME 0x2D
#define P_MOVING 0x2E
#define P_LOCK 0x2F
#define P_PUNCH_L 0x30
#define P_PUNCH_H 0x31


#endif
