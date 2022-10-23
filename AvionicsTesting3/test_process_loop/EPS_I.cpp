/**
 * @file EPS_I.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat driver for Endurosat EPS I
 * @version 1.0.0
 * @date 2022-10-23
 * 
 * 
 */

#include "EPS_I.h"

#include <avr/pgmspace.h>
#include <limits.h>
#include "pins_arduino.h"
#include "wiring_private.h"

EPS_I::EPS_I(int32_t sensorID) {
  _sensorID = sensorID;
}

bool EPS_I::getEvent(sensors_event_t *event) {
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = SENSOR_TYPE_PRESSURE;
  event->timestamp = 0;
  event->pressure = 123.0F;
  return true;
}

void EPS_I::getSensor(sensor_t *sensor) {
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, "EPS_I", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _sensorID;
  sensor->type        = SENSOR_TYPE_PRESSURE;
  sensor->min_delay   = 0;
  sensor->max_value   = 300.0F;               // 300..1100 hPa
  sensor->min_value   = 1100.0F;
  sensor->resolution  = 0.01F;                // 0.01 hPa resolution

  /* Clear the reserved section */
  // memset(sensor->reserved, 0, sizeof(sensor->reserved));
}