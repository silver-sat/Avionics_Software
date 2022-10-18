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
// todo: refactor as constexpr
#define SERCOM_SERIAL0 sercom0  /**< sercom for Serial0 @hideinitializer */
#define SERCOM_SERIAL1 sercom1  /**< sercom for Serial0 @hideinitializer */
#define SERCOM_NON_CRIT sercom2 /**< sercom for non-critical I2C @hideinitializer */
#define SERCOM_CRIT sercom3     /**< sercom for critical I2C @hideinitializer */
#define SERCOM_SPI sercom4      /**< sercom for Serial0 @hideinitializer */
#define SERCOM_SERIAL2 sercom5  /**< sercom for Serial0 @hideinitializer */

// #define SDA_NON_CRIT 4          /**< SDA for non-critical I2C @hideinitializer */
// #define SCL_NON_CRIT 3       /**< SCL for non-critical I2C @hideinitializer */
#define SDA_CRIT 26          /**< SDA for critical I2C @hideinitializer */
#define SCL_CRIT 27          /**< SCL for non-critical I2C @hideinitializer */
#define WDTICK 38            /**< trigger for Watchdog @hideinitializer */
#define MOSI MOSI            /**< MOSI @hideinitializer */
#define MISO MISO            /**< MISO @hideinitializer */
#define SCK SCK              /**< SCK @hideinitializer */
#define TXD2 7               /**< TXD @hideinitializer */
#define RXD2 6               /**< RXD @hideinitializer */
#define EN_EXT_I2C 11        /**< enable non-critical I2C @hideinitializer */
#define EN_PAYLOAD_SERIAL 39 /**< enable payload serial @hideinitializer */
#define EN_RADIO_SERIAL 10   /**< enable radio serial @hideinitializer */
#define PAYLOAD_TXD 1        /**< payload TXD @hideinitializer */
#define PAYLOAD_RXD 0        /**< payload RXD @hideinitializer */
#define RADIO_TXD 13         /**< radio TXD @hideinitializer */
#define RADIO_RXD 12         /**< radio TXD @hideinitializer */
#define PLD_ON_A 17          /**< payload on A @hideinitializer */
#define PLD_ON_B 18          /**< payload on B @hideinitializer */
#define PLD_ON_C 8           /**< payload on C @hideinitializer */
#define STATES_A_INT 9       /**< payload state A @hideinitializer */
#define STATES_B_INT 2       /**< payload state B @hideinitializer */
#define STATES_C_INT 5       /**< payload state C @hideinitializer */
#define SHUTDOWN_A 19        /**< payload shutdown A @hideinitializer */
#define SHUTDOWN_B 36        /**< payload shutdown B @hideinitializer */
#define SHUTDOWN_C 37        /**< payload shutdown C @hideinitializer */
#define PAYLOAD_OC 16        /**< payload over current @hideinitializer */

constexpr unsigned SDA_NON_CRIT{4u}; /**< SDA for non-critical I2C @hideinitializer */
constexpr unsigned SCL_NON_CRIT{3u}; /**< SCL for non-critical I2C @hideinitializer */
// #define SDA_CRIT 26             /**< SDA for critical I2C @hideinitializer */
// #define SCL_CRIT 27             /**< SCL for non-critical I2C @hideinitializer */
// #define WDTICK 38               /**< trigger for Watchdog @hideinitializer */
// #define MOSI MOSI               /**< MOSI @hideinitializer */
// #define MISO MISO               /**< MISO @hideinitializer */
// #define SCK SCK                 /**< SCK @hideinitializer */
// #define TXD2 7                  /**< TXD @hideinitializer */
// #define RXD2 6                  /**< RXD @hideinitializer */
// #define EN_EXT_I2C 11           /**< enable non-critical I2C @hideinitializer */
// #define EN_PAYLOAD_SERIAL 39    /**< enable payload serial @hideinitializer */
// #define EN_RADIO_SERIAL 10      /**< enable radio serial @hideinitializer */
// #define PAYLOAD_TXD 1           /**< payload TXD @hideinitializer */
// #define PAYLOAD_RXD 0           /**< payload RXD @hideinitializer */
// #define RADIO_TXD 13            /**< radio TXD @hideinitializer */
// #define RADIO_RXD 12            /**< radio TXD @hideinitializer */
// #define PLD_ON_A 17             /**< payload on A @hideinitializer */
// #define PLD_ON_B 18             /**< payload on B @hideinitializer */
// #define PLD_ON_C 8              /**< payload on C @hideinitializer */
// #define STATES_A_INT 9          /**< payload state A @hideinitializer */
// #define STATES_B_INT 2          /**< payload state B @hideinitializer */
// #define STATES_C_INT 5          /**< payload state C @hideinitializer */
// #define SHUTDOWN_A 19           /**< payload shutdown A @hideinitializer */
// #define SHUTDOWN_B 36           /**< payload shutdown B @hideinitializer */
// #define SHUTDOWN_C 37           /**< payload shutdown C @hideinitializer */
// #define PAYLOAD_OC 16           /**< payload over current @hideinitializer */
// todo: establish reset monitor pin for testing
#define RESET 0

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