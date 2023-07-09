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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#include <ArduinoLog.h>
#pragma GCC diagnostic pop

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