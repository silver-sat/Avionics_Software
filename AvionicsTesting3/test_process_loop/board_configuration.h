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

/**
 * @brief SAMD21 pin definitions
 *
 */

#define SERCOM_NON_CRIT sercom1 /**< sercom for non-critical I2C @hideinitializer */
#define SDA_NON_CRIT 11         /**< SDA for non-critical I2C @hideinitializer */
#define SCL_NON_CRIT 13         /**< SCL for non-critical I2C @hideinitializer */
#define SERCOM_CRIT sercom3     /**< sercom for critical I2C @hideinitializer */
#define SDA_CRIT SDA            /**< SDA for critical I2C @hideinitializer */
#define SCL_CRIT SCL            /**< SCL for non-critical I2C @hideinitializer */
#define WDTICK 2                /**< trigger for Watchdog @hideinitializer */
#define RESET 3                 /**< Watchdog reset @hideinitializer */
#define MOSI MOSI               /**< MOSI @hideinitializer */
#define MISO MISO               /**< MISO @hideinitializer */
#define SCK SCK                 /**< SCK @hideinitializer */
#define TXD2 TXD2               /**< TXD @hideinitializer */
#define RXD2 RXD2               /**< RXD @hideinitializer */
#define EN_EXT_I2C 8            /**< enable non-critical I2C @hideinitializer */
#define EN_PAYLOAD_SERIAL 6     /**< enable payload serial @hideinitializer */
#define EN_RADIO_SERIAL 7       /**< enable radio serial @hideinitializer */
#define PAYLOAD_TXD TXD0        /**< payload TXD @hideinitializer */
#define PAYLOAD_RXD RXD0        /**< payload RXD @hideinitializer */
#define RADIO_TXD TXD1          /**< radio TXD @hideinitializer */
#define RADION_RXD RXD1         /**< radio TXD @hideinitializer */
#define PLD_ON_A 0              /**< payload on A @hideinitializer */
#define PLD_ON_B 1              /**< payload on B @hideinitializer */
#define PLD_ON_C 2              /**< payload on C @hideinitializer */
#define STATES_A_INT 3          /**< payload state A @hideinitializer */
#define STATES_B_INT 4          /**< payload state B @hideinitializer */
#define STATES_C_INT 5          /**< payload state C @hideinitializer */
#define SHUTDOWN_A 9            /**< payload shutdown A @hideinitializer */
#define SHUTDOWN_B 10           /**< payload shutdown B @hideinitializer */
#define SHUTDOWN_C 11           /**< payload shutdown C @hideinitializer */
#define PAYLOAD_OC 12           /**< payload over current @hideinitializer */

/**
 * @brief I2C Addresses
 *
 */
// todo: refactor as constexpr
#define RTC_I2C_ADDRESS 0x68  /**< realtime clock I2C address @hideinitializer */
#define IMU_I2C_ADDRESS 0x68  /**< inertial measurement unit I2C address @hideinitializer */
#define FRAM_I2C_ADDRESS 0x50 /**< FRAM I2C address @hideinitializer */

/**
 * @brief Global constants
 *
 */

constexpr unsigned long seconds_to_milliseconds{1000}; /**< conversion factor for time in seconds @hideinitializer */

#endif // BOARD_CONFIGURATION_H