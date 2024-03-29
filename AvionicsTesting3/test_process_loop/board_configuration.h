/**
 * @file board_configuration.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Hardware definitions for Avionics Board
 * @version 1.0.1
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

constexpr unsigned SDA_NON_CRIT{4u};       /**< SDA for non-critical I2C @hideinitializer */
constexpr unsigned SCL_NON_CRIT{3u};       /**< SCL for non-critical I2C @hideinitializer */
constexpr unsigned SDA_CRIT{26u};          /**< SDA for critical I2C @hideinitializer */
constexpr unsigned SCL_CRIT{27u};          /**< SCL for non-critical I2C @hideinitializer */
constexpr unsigned WDTICK{38u};            /**< trigger for Watchdog @hideinitializer */
constexpr unsigned uC_MOSI{29u};           /**< MOSI @hideinitializer */
constexpr unsigned uC_MISO{28u};           /**< MISO @hideinitializer */
constexpr unsigned uC_SCK{30u};            /**< SCK @hideinitializer */
constexpr unsigned TXD2{7u};               /**< TXD @hideinitializer */
constexpr unsigned RXD2{6u};               /**< RXD @hideinitializer */
constexpr unsigned EN_EXT_I2C{11u};        /**< enable non-critical I2C @hideinitializer */
constexpr unsigned EN_PAYLOAD_SERIAL{39u}; /**< enable payload serial @hideinitializer */
constexpr unsigned EN_RADIO_SERIAL{10u};   /**< enable radio serial @hideinitializer */
constexpr unsigned PAYLOAD_TXD{1u};        /**< payload TXD @hideinitializer */
constexpr unsigned PAYLOAD_RXD{0u};        /**< payload RXD @hideinitializer */
constexpr unsigned RADIO_TXD{13u};         /**< radio TXD @hideinitializer */
constexpr unsigned RADIO_RXD{12u};         /**< radio TXD @hideinitializer */
constexpr unsigned PLD_ON_A_INT{17u};      /**< payload on A @hideinitializer */
constexpr unsigned PLD_ON_B_INT{18u};      /**< payload on B @hideinitializer */
constexpr unsigned PLD_ON_C_INT{8u};       /**< payload on C @hideinitializer */
constexpr unsigned STATES_A_INT{9u};       /**< payload state A @hideinitializer */
constexpr unsigned STATES_B_INT{2u};       /**< payload state B @hideinitializer */
constexpr unsigned STATES_C_INT{5u};       /**< payload state C @hideinitializer */
constexpr unsigned SHUTDOWN_A{19u};        /**< payload shutdown A @hideinitializer */
constexpr unsigned SHUTDOWN_B{36u};        /**< payload shutdown B @hideinitializer */
constexpr unsigned SHUTDOWN_C{37u};        /**< payload shutdown C @hideinitializer */
constexpr unsigned PAYLOAD_OC{16u};        /**< payload over current @hideinitializer */
constexpr unsigned RESET{0u};              /**< reset the processor @hideinitializer */

/**
 * @brief I2C Addresses
 *
 * RTC and IMU have the same addresses but are located on different buses
 */

constexpr unsigned RTC_I2C_ADDRESS{0x68};   /**< realtime clock I2C address @hideinitializer */
constexpr unsigned IMU_I2C_ADDRESS{0x68};   /**< inertial measurement unit I2C address @hideinitializer */
constexpr unsigned FRAM_I2C_ADDRESS{0x50};  /**< FRAM I2C address @hideinitializer */
constexpr unsigned wait_for_i2c_device{10}; /**< wait for I2C device to become available */

/**
 * @brief Global constants
 *
 */

constexpr unsigned long seconds_to_milliseconds{1000}; /**< conversion factor for time in seconds @hideinitializer */
constexpr unsigned long minutes_to_seconds{60};        /**< conversion factor for time in minutes @hideinitializer */

#endif // BOARD_CONFIGURATION_H