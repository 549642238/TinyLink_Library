#ifndef U_BLOX_GPS_ARDUINO_UNO_H
#define U_BLOX_GPS_ARDUINO_UNO_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "TL_Config.h"

SoftwareSerial GPS(2,3);

class UBLOX
{
  
private:
  typedef struct{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
  } date_time;
  double lng, lat;
  date_time dt;
  
public:
  UBLOX();
  void read();
  date_time timeData();
  double lngData();
  double latData();
};

extern UBLOX TL_GPS;

#endif
