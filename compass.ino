#include <U8glib.h>
#include <COMPASS64X13.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

U8GLIB_SSD1306_64X48 u8g(14, 11, 10, 8, 9);   //MicroView OLED
 
/* Assign a unique ID to mag sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

int headingInt;
 
void setup(void) 
{
  Serial.begin(9600);
  
  /* Initialise the sensor */
  if(!mag.begin());
} 

void draw(void){
  u8g.setFont(u8g_font_6x13);     //draw compass heading
  if (headingInt <= 9 ){          //center number on screen
    u8g.setPrintPos( 30, 24);
    u8g.print(headingInt);
    u8g.setPrintPos( 36, 24);
    u8g.print((char)176);       //Degree symbol
   }
     else if (headingInt >= 10 && headingInt <= 99){ //center
       u8g.setPrintPos( 27, 24);
       u8g.print(headingInt);
       u8g.print((char)176);
     }
       else if (headingInt >= 100){              //center
         u8g.setPrintPos( 23, 24);
         u8g.print(headingInt);
         u8g.print((char)176);
       }
}
 
void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
  
  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
  
  // Normalize to 0-360
  if (heading < 1)
  {
    heading = 360 + heading;
  }
   headingInt = heading; 
  
  Serial.print("Compass Heading: ");
  Serial.println(heading);
  Serial.println(headingInt);
  
    // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  
  delay(300);
}
