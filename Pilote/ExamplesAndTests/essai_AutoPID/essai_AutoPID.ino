/***************************************************************************
  This is a library example for the HMC5883 magnentometer/compass

  Designed specifically to work with the Adafruit HMC5883 Breakout
  http://www.adafruit.com/products/1746
 
  *** You will also need to install the Adafruit_Sensor library! ***

  These displays use I2C to communicate, 2 pins are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Kevin Townsend for Adafruit Industries with some heading example from
  Love Electronics (loveelectronics.co.uk)
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the version 3 GNU General Public License as
 published by the Free Software Foundation.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/
/* THIS IS A TEST PROGRAM !!! */
/*
 * Brochage : 
 * SCL : pin A5 (analogic)
 * SDA : pin A4 (analogic)
 * INT : NC
 * VCC : 5V (arduino)
 * GND : GND (arduino).
 * NB si alim autre que arduino, les GND du chip et de l'arduino doivent être reliés
 */
#define MAX 30
int nb = 0;
#include <AutoPID.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

#define HEADING_READ_DELAY 800 //can only read heading every ~750ms

//pid settings and gains
#define OUTPUT_MIN 10
#define OUTPUT_MAX 10
#define KP .12
#define KI .0003
#define KD 0

// pid values
double headingCurrent, headingWanted, headingCorrection;
unsigned long lastHeadingUpdate; //tracks clock time of last heading update

//input/output variables passed by reference, so they are updated automatically
AutoPID myPID(&headingCurrent, &headingWanted, &headingCorrection, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

/* the update delay will be (first) controled by delay() in loop()
bool updateHeading() {
  if ((millis() - lastHeadingUpdate) > HEADING_READ_DELAY) {
    headingCurrent = temperatureSensors.getTempFByIndex(0); //get temp reading
    lastTempUpdate = millis();
    temperatureSensors.requestTemperatures(); //request reading for next time
    return true;
  }
  return false;
}
*/

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  /* Display some basic information on this sensor */
  displaySensorDetails();
  /* PID setup and start */
  myPID.setBangBang(4);
  //set PID update interval to 4000ms
  myPID.setTimeStep(4000);
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
  if (nb < MAX) {
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  /*
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
  */
  }
  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  // float declinationAngle = 0.22;
  // heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  Serial.print("Heading rad: "); Serial.println(heading);
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
  Serial.println("------------------------------------------------");
  nb += 1;
  delay(500);
}
