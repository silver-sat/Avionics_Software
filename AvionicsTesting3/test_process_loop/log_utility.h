/**
 * @file log_utility.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test logging support routines
 * @version 1.0.0
 * @date 2022-07-31
 *
 *
 */

#ifndef LOG_UTILITY_H
#define LOG_UTILITY_H

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

#endif // LOG_UTILITY_H
