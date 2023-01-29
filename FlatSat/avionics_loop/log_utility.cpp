/**
 * @file log_utility.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test logging support routines
 * @version 1.0.0
 * @date 2022-07-31
 *
 *
 */

#include "log_utility.h"

/**
 * @brief Print log prefix
 *
 * @param _logOutput output
 * @param logLevel log level
 */

void printPrefix(Print *_logOutput, int logLevel)
{
  printTimestamp(_logOutput);
  printLogLevel(_logOutput, logLevel);
}

/**
 * @brief Print log timestamp
 *
 * @param _logOutput output
 */

void printTimestamp(Print *_logOutput)
{
  char timestamp[20];
  formatTimestamp(timestamp);
  _logOutput->print(timestamp);
}

/**
 * @brief Format timestamp
 *
 * @param timestamp output
 * @param msecs optional, default is current value of millis()
 */

void formatTimestamp(char *timestamp, const unsigned long msecs)
{
  // Division constants
  const unsigned long MSECS_PER_SEC = 1000;
  const unsigned long SECS_PER_MIN = 60;
  const unsigned long SECS_PER_HOUR = 3600;
  const unsigned long SECS_PER_DAY = 86400;

  // Total time
  const unsigned long secs = msecs / MSECS_PER_SEC;

  // Time in components
  const unsigned long MilliSeconds = msecs % MSECS_PER_SEC;
  const unsigned long Seconds = secs % SECS_PER_MIN;
  const unsigned long Minutes = (secs / SECS_PER_MIN) % SECS_PER_MIN;
  const unsigned long Hours = (secs % SECS_PER_DAY) / SECS_PER_HOUR;

  sprintf(timestamp, "%02d:%02d:%02d.%03d ", Hours, Minutes, Seconds, MilliSeconds);
}

/**
 * @brief Print log description based on level
 *
 * @param _logOutput output
 * @param logLevel log level
 */

void printLogLevel(Print *_logOutput, int logLevel)
{
  switch (logLevel)
  {
  default:
  case 0:
    _logOutput->print("SILENT  ");
    break;
  case 1:
    _logOutput->print("FATAL   ");
    break;
  case 2:
    _logOutput->print("ERROR   ");
    break;
  case 3:
    _logOutput->print("WARNING ");
    break;
  case 4:
    _logOutput->print("INFO    ");
    break;
  case 5:
    _logOutput->print("TRACE   ");
    break;
  case 6:
    _logOutput->print("VERBOSE ");
    break;
  }
}

/**
 * @brief Print log suffix
 *
 * @param _logOutput output
 * @param logLevel log level
 */

void printSuffix(Print *_logOutput, int logLevel)
{
  _logOutput->print("");
}