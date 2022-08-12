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

void printPrefix(Print* _logOutput, int logLevel);
void printTimestamp(Print* _logOutput);
void printLogLevel(Print* _logOutput, int logLevel);
void printSuffix(Print* _logOutput, int logLevel);

#endif // LOG_UTILITY_H