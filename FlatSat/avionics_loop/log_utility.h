/**
 * @file log_utility.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Logging Support Routines
 * @version 1.0.0
 * @date 2022-07-31
 *
 * This file declares customized methods for the log facility
 *
 */

#pragma once

#include <ArduinoLog.h>

/**
 * @brief Print log prefix
 *
 */

void printPrefix(Print *_logOutput, int logLevel);

/**
 * @brief Print log timestamp
 *
 */

void printTimestamp(Print *_logOutput);

/**
 * @brief Format timestamp
 *
 */

void formatTimestamp(char *timestamp, const unsigned long msecs = millis());

/**
 * @brief Print log description based on level
 *
 */

void printLogLevel(Print *_logOutput, int logLevel);

/**
 * @brief Print log suffix
 *
 */

void printSuffix(Print *_logOutput, int logLevel);