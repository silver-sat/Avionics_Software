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
 * @param _logOutput output
 * @param logLevel log level
 */

void printPrefix(Print *_logOutput, int logLevel);

/**
 * @brief Print log timestamp
 *
 * @param _logOutput output
 */

void printTimestamp(Print *_logOutput);

/**
 * @brief Print log description based on level
 *
 * @param _logOutput output
 * @param logLevel log level
 */

void printLogLevel(Print *_logOutput, int logLevel);

/**
 * @brief Print log suffix
 *
 * @param _logOutput output
 * @param logLevel log level
 */

void printSuffix(Print *_logOutput, int logLevel);

#endif // LOG_UTILITY_H
