# Techagro
"Everything can wait but not Agriculture"

I, Prakhar Saxena, a first year student of B-Tech Computer Science at Lovely Professional University, here by propose an idea which could be a boom for INDIAN AGRICULTURE SECTOR and would not only provide employment to alot of rural people but would also increase their economic status of farmers and would make them self independent.  

*TECHAGRO - "Everything can wait, but not Agriculture."*    

Currently the techniques followed in agriculture are obsolete and of no use. We follow the same techniques that were followed by our ancestors 20-25 years ago. But the climate and weather conditions have changed drastically, pollution has increased on on uncountable scale that's why the net average production per hectare of India is also decreasing day by day.
Their are proven reports for example taking case of Ethiopia, where when appropriate amount of NPK was used and proper soil testing was done to grow maize , their net average production reached around 6-7 tons per hectare that is somewhere equal to the European average.
But in India it's not that easy or feasible to approach a small farmer to tell him to get his soil tested. As in India small farmers don't have 500-600 bucks, to buy seeds then why will he listen to us to get his soil tested. So making sure that it's within his reach will ensure that he would in fact listen to us but would also take the advice.

*Solution-*
Providing accessible, affordable and instant way of soil testing through RGB analysis and chromatography. The soil testing can be done in just few minutes at the rate of ₹13 per test.

*Advantages over existing technology-*
Conventional soil testing laboratories take around ₹50-₹600 to get the soil tested whereas through this device it would be done in just ₹13.

For conventional soil testing in laboratories it takes around 2weeks to even 2 months to get the soil tested as the sample is first sent to the laboratories which are mostly situated in the major cities and then after the test the farmer gets back the result. Whereas through this device it can be done instantly.

This device provides easy to understand reports which even the farmers can interpret without any difficulties making them self reliable. Whereas conventional soil testing provides detailed report which an illiterate (in terms of formal education) can't understand.

This device provides localized reports depending upon weather conditions and topographical data making the report more accurate. For Ex- The soil of UNNAO, a district in UP is quite rich in sulphur which is quite unnatural so it would cause errors in the conventional way of soil testing.

The device also provides weather precautions which could be of great help for farmers. If the farmers of Maharashtra would have got timely precautions about the pre mature rainfall then they would not have suffered such a big loss of onion crop and its price would have not hiked in India.

The device not only predicts the soil content but can also predict the most suitable crop along with type and amount of fertilizer required. It would also suggest precautions about weather conditions if any. The farmers have soil testing card which has details regarding the pincode and the area of their farm, so these data along with the NPK values helps in these predictions.

This project would not only affect the farmers but would also help in improving the economic status of India.
It mainly focuses on increasing the net average production of crop per hectare.

*Working -*
The farmers would just have to dip the given strip in the aqueous solution of their soil, stick it on the soil health card and scan it through the device. The soil health card would contain a barcode which would be unique for each farmer, having details like location, size and previous record
of tests (if any). All these details along with the stored dataset would help in predicting the most suitable crop, soil NPK content, along with type and amount of fertilizers required depending upon all of the aforesaid factors.
All the details would be printed on the soil health card in the local language.
This scanning device which cost around ₹400  could be installed in post offices of every village and in future it would be replaced by a smartphone application. Through the smartphone application, farmers could do the soil testing and prediction through just a click of their smartphones.


*CODE*
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

Regards,
Prakhar Saxena,
Student,
Lovely Professional University, India.
+91 8765186212,
prakhar.11911235@lpu.in
https://www.linkedin.com/in/prakhar9saxena
