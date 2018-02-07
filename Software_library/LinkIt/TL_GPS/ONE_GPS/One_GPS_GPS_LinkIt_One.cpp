#include "One_GPS_GPS_LinkIt_One.h"

Built_In_GPS::Built_In_GPS()
{
  lng = lat = 0;
  // dt.year = dt.month = dt.day = dt.hour = dt.minute = dt.second = 0;
  LGPS.powerOn();
}

unsigned char Built_In_GPS::getComma(unsigned char num,const char *str)
{
  unsigned char i,j = 0;
  int len=strlen(str);
  for(i = 0;i < len;i ++)
  {
     if(str[i] == ',')
      j++;
     if(j == num)
      return i + 1; 
  }
  return 0; 
}

double Built_In_GPS::getDoubleNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;
  
  i=getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev=atof(buf);
  return rev; 
}

double Built_In_GPS::getIntNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;
  
  i=getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev=atoi(buf);
  return rev; 
}

void Built_In_GPS::parseGPGGA(const char* GPGGAstr)
{
  /* Refer to http://www.gpsinformation.org/dale/nmea.htm#GGA
   * Sample data: $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
   * Where:
   *  GGA          Global Positioning System Fix Data
   *  123519       Fix taken at 12:35:19 UTC
   *  4807.038,N   Latitude 48 deg 07.038' N
   *  01131.000,E  Longitude 11 deg 31.000' E
   *  1            Fix quality: 0 = invalid
   *                            1 = GPS fix (SPS)
   *                            2 = DGPS fix
   *                            3 = PPS fix
   *                            4 = Real Time Kinematic
   *                            5 = Float RTK
   *                            6 = estimated (dead reckoning) (2.3 feature)
   *                            7 = Manual input mode
   *                            8 = Simulation mode
   *  08           Number of satellites being tracked
   *  0.9          Horizontal dilution of position
   *  545.4,M      Altitude, Meters, above mean sea level
   *  46.9,M       Height of geoid (mean sea level) above WGS84
   *                   ellipsoid
   *  (empty field) time in seconds since last DGPS update
   *  (empty field) DGPS station ID number
   *  *47          the checksum data, always begins with *
   */
  double latitude;
  double longitude;
  int tmp, hour, minute, second, num ;
  if(GPGGAstr[0] == '$')
  {
    tmp = getComma(1, GPGGAstr);
    hour     = (GPGGAstr[tmp + 0] - '0') * 10 + (GPGGAstr[tmp + 1] - '0');
    minute   = (GPGGAstr[tmp + 2] - '0') * 10 + (GPGGAstr[tmp + 3] - '0');
    second    = (GPGGAstr[tmp + 4] - '0') * 10 + (GPGGAstr[tmp + 5] - '0');
    // dt.hour = hour;
    // dt.minute = minute;
    // dt.second = second;
    // sprintf(buff, "UTC timer %2d-%2d-%2d", hour, minute, second);
    // Serial.println(buff);
    
    tmp = getComma(2, GPGGAstr);
    latitude = getDoubleNumber(&GPGGAstr[tmp]);
    lat = latitude;
    tmp = getComma(4, GPGGAstr);
    longitude = getDoubleNumber(&GPGGAstr[tmp]);
    lng = longitude;
    // sprintf(buff, "latitude = %10.4f, longitude = %10.4f", latitude, longitude);
    // Serial.println(buff); 
    
    // tmp = getComma(7, GPGGAstr);
    // num = getIntNumber(&GPGGAstr[tmp]);    
    // sprintf(buff, "satellites number = %d", num);
    // Serial.println(buff); 
  }
  else
  {
    Serial.println("Not get data"); 
  }
}


void Built_In_GPS::read()
{
  LGPS.getData(&info);
  parseGPGGA((const char*)info.GPGGA);
}

// date_time Built_In_GPS::timeData()
// {
  // return dt;
// }

double Built_In_GPS::latData()
{
  return lat;
}

double Built_In_GPS::lngData()
{
  return lng;
}

Built_In_GPS TL_GPS;
