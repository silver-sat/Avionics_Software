/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief Hardware definitions for Avionics Board
 *
 * This file contains the global constants used by the Avionics Board software.
 *
 */

#pragma once

#include <Arduino.h>

/**
 * @brief Global time constants
 *
 */

constexpr unsigned long seconds_to_milliseconds{1000}; /**< conversion factor for time in seconds @hideinitializer */
constexpr unsigned long minutes_to_seconds{60};        /**< conversion factor for time in minutes @hideinitializer */
constexpr unsigned long hours_to_minutes{60};          /**< conversion factor for time in hours @hideinitializer */
constexpr unsigned long days_to_hours{24};             /**< conversion factor for time in days @hideinitializer */
constexpr unsigned long weeks_to_days{7};              /**< conversion factor for time in weeks @hideinitializer */

/**
 * @brief SAMD21 pin definitions
 *
 */

constexpr unsigned SDA_NON_CRIT{4u};       /**< SDA for non-critical I2C @hideinitializer */
constexpr unsigned SCL_NON_CRIT{3u};       /**< SCL for non-critical I2C @hideinitializer */
constexpr unsigned SDA_CRIT{26u};          /**< SDA for critical I2C @hideinitializer */
constexpr unsigned SCL_CRIT{27u};          /**< SCL for non-critical I2C @hideinitializer */
constexpr unsigned WDTICK{38u};            /**< Watchdog service @hideinitializer */
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
constexpr unsigned GPIO_A{14U};            /**< GPIO pin on J1 */
constexpr unsigned RESET{0u};              /**< reset the processor @hideinitializer */

/**
 * @brief I2C delay constant
 *
 */

constexpr unsigned wait_for_i2c_device{20}; /**< wait for I2C device to become available */

/**
 * @brief Maximum size of command from Radio Board
 *
 */

constexpr size_t maximum_command_length{256}; /**< maximum characters in command */

/**
 * @brief KISS protocol constants
 *
 */

constexpr byte FEND{'\xC0'};  /**< frame end */
constexpr byte FESC{'\xDB'};  /**< frame escape */
constexpr byte TFEND{'\xDC'}; /**< transposed frame end */
constexpr byte TFESC{'\xDD'}; /**< transposed frame escape */

/**
 * @brief Local message content
 *
 */

const String ACK{"ACK"};   /**< acknowledge */
const String NACK{"NACK"}; /**< negative acknowledge */
const String RES{"RES"};   /**< response */

/**
 * @brief SilverSat defined KISS local command types
 *
 */

constexpr byte LOCAL_FRAME{'\x00'};       /**< local data frame */
constexpr byte REMOTE_FRAME{'\xAA'};      /**< remote data frame */
constexpr byte BEACON{'\x07'};            /**< beacon */
constexpr byte DIGITALIO_RELEASE{'\x08'}; /**< deploy antenna in recovery mode */
constexpr byte GET_RADIO_STATUS{'\x09'};  /**< request radio status */
constexpr byte HALT{'\x0A'};              /**< stop transmission */
constexpr byte MODIFY_FREQUENCY{'\x0B'};  /**< change radio frequency */
constexpr byte MODIFY_MODE{'\x0C'};       /**< change radio mode */
constexpr byte TOGGLE_RADIO_5V{'\x0F'};   /**< Toggle radio 5v */
constexpr byte BACKGROUND_RSSI{'\x18'};   /**< Report average background RSSI */
constexpr byte CURRENT_RSSI{'\x19'};      /**< Report current RSSI */

/**
 * @brief Radio command parameter lengths
 *
 */

constexpr size_t mode_length{1};            /**< mode */
constexpr size_t background_rssi_length{2}; /**< background RSSI */

/**
 * @brief Error code for frequency change
 *
 */

constexpr byte BELL{'\x07'}; /**< bell character */
