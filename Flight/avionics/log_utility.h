/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief Logging Support Routines
 *
 * This file declares customized methods for the log facility
 *
 */

#pragma once

#include <ArduinoLog.h>
void printPrefix(Print *_logOutput, int logLevel);
void printTimestamp(Print *_logOutput);
void formatTimestamp(char *timestamp, const unsigned long msecs = millis());
void printLogLevel(Print *_logOutput, int logLevel);
void printSuffix(Print *_logOutput, int logLevel);
void updateLogDay();