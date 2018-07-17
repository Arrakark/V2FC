#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//figure out how to include timer library
//#include <libopencm3/stm32/gpio.h>
//#include <libopencm3/stm32/timer.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
#define SSD1306_LCDHEIGHT 64
#define rEncoderA PA2
#define rEncoderB PA3

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int leftCount = 0;
int rightCount = 0;

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // text display tests
   display.setTextSize(2);
   display.setTextColor(WHITE);
   display.setCursor(0,0);


  display.clearDisplay();


  pinMode(rEncoderA, INPUT);
  pinMode(rEncoderB, INPUT);
  digitalWrite(rEncoderA, HIGH); // already pulled high but try anyway
  digitalWrite(rEncoderB, HIGH);

  //display.setCursor(0,0);
 // display.print("LEFT");
  //display.setCursor(0,64);
  //display.println("RIGHT");

  //display.println("Hello, world!");
  // display.setTextColor(BLACK, WHITE); // 'inverted' text
  // display.println(3.141592);
  // display.setTextSize(2);
  // display.setTextColor(WHITE);
  // display.print("0x"); display.println(0xDEADBEEF, HEX);
  //display.display();
  //delay(2000);
  // display.clearDisplay();
}


void loop() {
 
  //---- display encoder info ----//
  // display.clearDisplay();
  display.setCursor(0,0);
  display.println("LEFT RIGHT");
  display.drawFastHLine(0,15,120,WHITE);
  display.setCursor(5,25);
  display.print(leftCount);
  display.setCursor(60,25);
  display.print(rightCount);
  display.display();

  
  //read rotary encoder 




  //display.clearDisplay();
  //delay(2000);
}
