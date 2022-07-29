/**
 * @file AvionicsBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Avionics Board for SilverSat
 * @version 1.0.0
 * @date 2022-07-29
 *
 *
 */

#include "AvionicsBoard.h"

AvionicsBoard::AvionicsBoard()
{
    RTC_PCF8523 rtc;
    _external_rtc = rtc;
};

bool AvionicsBoard::begin()
{
    return true;
};

bool AvionicsBoard::initialize_external_rtc()
{
    return _external_rtc.begin();
};

bool AvionicsBoard::set_external_rtc(DateTime date_time)
{
    _external_rtc.adjust(date_time);
    _external_rtc.start();
    _external_rtc_is_set = true;
    return true;
};

bool AvionicsBoard::get_external_rtc_is_set()
{
    return _external_rtc_is_set;
};

int AvionicsBoard::get_year()
{
    return _external_rtc.now().year();
};

int AvionicsBoard::get_month()
{
    return _external_rtc.now().month();
};

int AvionicsBoard::get_day()
{
    return _external_rtc.now().day();
};

int AvionicsBoard::get_hour()
{
    return _external_rtc.now().hour();
};

int AvionicsBoard::get_minute()
{
    return _external_rtc.now().minute();
};

int AvionicsBoard::get_second()
{
    return _external_rtc.now().second();
};
