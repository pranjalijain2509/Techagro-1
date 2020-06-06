//TechAgro

#include <MD_TCS230.h> //Color Sensor Library
#include <FreqCount.h> // FreqCount measures the frequency of a signal by counting the number of pulses during a fixed time
#include <Adafruit_ST7735.h> //Arduino 1.8 inch tft display library
#include <Adafruit_GFX.h> //Adafruit GFX graphics core library

#define cs   10  
#define dc   9   
#define rst  8   

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF
#define GREY            0xC618
#define LIGHT GREY      0xBDF7
#define DARK GREY       0x7BEF
#define ORANGE          0xFBE0
#define BROWN           0x79E0  
#define PINK            0xF81F
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */

// Pin definitions
#define  S2_OUT  2
#define  S3_OUT  3
#define  OE_OUT   4    // LOW = ENABLED 

int R = 0;
int G = 0;
int B = 0;

MD_TCS230 CS(S2_OUT, S3_OUT, OE_OUT);
  
int state = 0;

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

void setup() {

 Serial.begin(57600);
  
 tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab


 drawBlackScreen();//Now Printing Opening Screen
  
 tft.setCursor(20,30);
  tft.setTextColor(RED);
 tft.setTextSize(2);
    tft.print("Code Mania");// Name of event

 tft.setCursor(20,60);
    tft.setTextColor(GREEN);
 tft.setTextSize(2);
  tft.print("TechAgro"); // Project Name

    tft.setCursor(20,90);
 tft.setTextColor(BLUE);
  tft.setTextSize(1);
 tft.print("By- Prakhar"); // Creator's Name

  delay(3000);
  
  drawBlackScreen();

 
  
 tft.setCursor(20,20);
  tft.setTextColor(RED);
 tft.setTextSize(2);
    tft.print("Step 1- Caliberate the senor using black & white colors");// Instructions for device operation

  delay(3000);
drawBlackScreen();

 tft.setCursor(20,20);
  tft.setTextColor(RED);
 tft.setTextSize(2);
    tft.print("Step 2- Place the sensor module on the chromatographic strip");

  delay(3000);
drawBlackScreen();

 tft.setCursor(20,20);
  tft.setTextColor(RED);
 tft.setTextSize(2);
    tft.print("Step 3- Wait for the Results!!!");

  delay(3000);
drawBlackScreen();

   tft.setCursor(10,30);
   tft.setTextColor(WHITE);
   tft.setTextSize(2);
   tft.print("SET BLACK");
   delay(5000);
   
   CS.begin();
   CS.read();
}

void loop() {

if(state ==0)
{
  if (CS.available()) {
   sensorData  sd;
   CS.getRaw(&sd); 
   CS.setDarkCal(&sd); 
   Serial.println("Black Calibration Set"); // calibrating black color
   state++;
   drawBlackScreen();

   tft.setCursor(10,30);
   tft.setTextColor(WHITE);
   tft.setTextSize(2);
   tft.print("SET WHITE");

   delay(5000);
   CS.read();
  }
}
else if(state == 1)
{
 if (CS.available()) {
   sensorData  sd;
   CS.getRaw(&sd); 
   CS.setWhiteCal(&sd); 
   Serial.println("White Calibration Set"); // Calibrating white color
   drawBlackScreen();

  tft.setCursor(35,64);
  tft.setTextColor(WHITE);
    tft.setTextSize(2);
   tft.print("COLOR");
  tft.drawRect(31,10,90,25,WHITE);
   state++;
  }

}else
{
  readSensor(); //to read values from the sensor
}
 

}

void drawBlackScreen()
{
  tft.fillScreen(BLACK);
  //Draw white frame
  tft.drawRect(0,0,127,159,WHITE); // Frame dimensions
  tft.drawRect(1,1,127,159,WHITE);
}

uint16_t convertRGB24toRGB565(uint8_t r, uint8_t g, uint8_t b) 
{
  return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

void readSensor()
{
  static  bool  waiting = false;
  
  if (!waiting)
  {
    CS.read();
    waiting = true;
  }
  else
  {
    if (CS.available()) 
    {
      colorData  rgb;
      
      CS.getRGB(&rgb);
      Serial.print("RGB [");
      Serial.print(rgb.value[TCS230_RGB_R]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_G]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_B]);
      Serial.println("]");
      
      R = rgb.value[TCS230_RGB_R];
      G = rgb.value[TCS230_RGB_G];
      B = rgb.value[TCS230_RGB_B];
 
      int color = convertRGB24toRGB565(R,G,B); //Convertion to 16bit color for the display
      
      delay(100);
      
      tft.fillRect(31,10,90,25,color);  //Defining Size of the rectangle, with 'color' as a heading.

      waiting = false;
    }
  }
} 
