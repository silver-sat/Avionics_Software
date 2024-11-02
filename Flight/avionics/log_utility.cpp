/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Logging Support Routines
 *
 * This file implements customized methods for the log facility
 *
 */

#include "log_utility.h"
static unsigned long daysSinceStart{0};
static unsigned long timer{millis()};
// Division constants
const unsigned long MSECS_PER_SEC = 1000;
const unsigned long SECS_PER_MIN = 60;
const unsigned long SECS_PER_HOUR = 3600;
const unsigned long SECS_PER_DAY = 86400;

/**
 * @brief Print log prefix
 *
 * @param _logOutput output
 * @param logLevel log level
 *
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
 *
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
 *
 */

void formatTimestamp(char *timestamp, const unsigned long msecs)
{

  // Total time
  unsigned long secs = msecs / MSECS_PER_SEC;

  // Time in components
  int MilliSeconds = msecs % MSECS_PER_SEC;
  int Seconds = secs % SECS_PER_MIN;
  int Minutes = (secs / SECS_PER_MIN) % SECS_PER_MIN;
  int Hours = (secs % SECS_PER_DAY) / SECS_PER_HOUR;
  int Days = daysSinceStart;

  sprintf(timestamp, "%03d:%02d:%02d:%02d.%03d ", Days, Hours, Minutes, Seconds, MilliSeconds);
}

/**
 * @brief Print log description based on level
 *
 * @param _logOutput output
 * @param logLevel log level
 *
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
    _logOutput->print("\033[1;31mFATAL\033[0m   ");
    break;
  case 2:
    _logOutput->print("\033[1;31mERROR\033[0m   ");
    break;
  case 3:
    _logOutput->print("\033[1;31mWARNING\033[0m ");
    break;
  case 4:
    _logOutput->print("\033[1;32mINFO\033[0m    ");
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
 *
 */

void printSuffix(Print *_logOutput, int logLevel)
{
  _logOutput->print("");
}
void updateLogDay()
{
if(millis()-timer>=SECS_PER_DAY*MSECS_PER_SEC ){
  
    ++daysSinceStart;
    timer=millis();
  }
}