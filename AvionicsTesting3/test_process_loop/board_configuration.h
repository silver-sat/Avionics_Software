/**
 * @file board_configuration.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Hardware definitions for Avionics Board
 * @version 1.0.0
 * @date 2022-08-11
 * 
 * 
 */

#ifndef BOARD_CONFIGURATION_H
#define BOARD_CONFIGURATION_H

// #define WDTICK_PIN PIN_PB23
#define WDTICK_PIN 2  // for testing
#define WDRESET_PIN 3 // for testing
/**
 * @brief SAMD21 pin definitions
 *
 */

#define SERCOM_NON_CRIT sercom1
#define SDA_NON_CRIT 11
#define SCL_NON_CRIT 13
#define SERCOM_CRIT sercom3
#define SDA_CRIT SDA
#define SCL_CRIT SCL
#define WDTICK 2
#define RESET 3
#define MOSI MOSI
#define MISO MISO
#define SCK SCK
#define TXD2 TXD2
#define RXD2 RXD2
#define EN_EXT_I2C 8
#define EN_PAYLOAD_SERIAL 6
#define EN_RADIO_SERIAL 7
#define PAYLOAD_TXD TXD0
#define PAYLOAD_RXD RXD0
#define RADIO_TXD TXD1
#define RADION_RXD RXD1
#define PLD_ON_A 0
#define PLD_ON_B 1
#define PLD_ON_C 2
#define STATES_A_INT 3
#define STATES_B_INT 4
#define STATES_C_INT 5
#define SHUTDOWN_A 9
#define SHUTDOWN_B 10
#define SHUTDOWN_C 11
#define PAYLOAD_OC 12


/** 
 * I2C Addresses
 * 
 */

#define RTC_I2C_ADDRESS 0x68
#define IMU_I2C_ADDRESS 0x68
#define FRAM_I2C_ADDRESS 0x50

#endif