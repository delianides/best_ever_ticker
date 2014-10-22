/*-------------------------------------------------------------------------
  Spark Core library to control WS2811/WS2812 based RGB
  LED devices such as Adafruit NeoPixel strips.
  Currently handles 800 KHz and 400kHz bitstream on Spark Core,
  WS2812, WS2812B and WS2811.

  Also supports Radio Shack Tri-Color Strip with TM1803 controller
  400kHz bitstream.

  PLEASE NOTE that the NeoPixels require 5V level inputs
  and the Spark Core only has 3.3V level outputs. Level shifting is
  necessary, but will require a fast device such as one of the following:

  [SN74HCT125N]
  http://www.digikey.com/product-detail/en/SN74HCT125N/296-8386-5-ND/376860

  [SN74HCT245N]
  http://www.digikey.com/product-detail/en/SN74HCT245N/296-1612-5-ND/277258

  [TXB0108PWR]
  http://www.digikey.com/product-search/en?pv7=2&k=TXB0108PWR

  If you have a Spark Shield Shield, the TXB0108PWR 3.3V to 5V level
  shifter is built in.

  Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
  Modified to work with Spark Core by Technobly.
  Contributions by PJRC and other members of the open source community.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!
  --------------------------------------------------------------------*/

/* ======================= includes ================================= */

#include "application.h"
//#include "spark_disable_wlan.h" (for faster local debugging only)
#include "neomatrix.h"

#include "flashee-eeprom.h"
using namespace Flashee;

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B

//I don't need WIFI right now
SYSTEM_MODE(SEMI_AUTOMATIC);

//Definition for extra functions
int setSalvationCount(String count);
int countDigits(int digits);

//Define Matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8,8,5,1, PIXEL_PIN,
 NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_PROGRESSIVE +
 NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE
);

void setup() {
  //Initalize the reader
  FlashDevice* device = Devices::createWearLevelErase();
  FlashReader reader(device);

  Serial.begin(9600);  // open serial over TX and RX pins

  Serial.println("Starting setup....");
  //Wifi will be disabled at this point
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(30);
  matrix.setTextColor(matrix.Color(80,255,0));
  matrix.fillScreen(0);

  int value = reader.readInt();

  if(value){
    int digits = countDigits(value);
    matrix.setCursor(41-(digits*6),0);
    matrix.print(F(value));
    matrix.show();
  }else{
    matrix.print(F("******"));
    matrix.show();
  }

  //After everything has been setup, connect to wifi....
  Spark.connect();

  //Enable Wifi
  Spark.function("celebrate", setSalvationCount);
}

void loop() {

}

int setSalvationCount(String count){
  //Convert count string to integer.
  int salvations = atoi(count.c_str());

  //Initalize the flash device for saving the new number
  FlashDevice* device = Devices::createWearLevelErase();
  FlashWriter writer(device);
  writer.writeInt(salvations);

  //Output Serial for debug
  Serial.print("Salvations: ");
  Serial.println(salvations);

  //Initalize Digits
  int digits = 1;
  //Random number to increment by so it doesn't seem so neat.
  int flux = rand() % 30 + 50;

  //Loop through a counter until it reaches salvations
  for(int c = 0; c <= salvations; c = c + flux){
    Serial.print("Count: ");
    Serial.println(c);
    matrix.fillScreen(0);
    digits = countDigits(c);
    matrix.setCursor(41-(digits*6),0);
    matrix.print(F(c));
    matrix.show();
    flux = rand() % 30 + 200;
    delay(35);
  }

  //This is to make sure that the ticker ends up on the right number
  //Everything is happening really fast no one would be able to see this
  matrix.fillScreen(0);
  digits = countDigits(salvations);
  matrix.setCursor(41-(digits*6),0);
  matrix.print(F(salvations));
  matrix.show();

  //Restful function returns count
  return salvations;
}

//Helper function to count the number of digits in an int
int countDigits(int number){
  int digits = 0;
  while (number){
    number /= 10;
    digits++;
  }
  return digits;
}

void missingWifi(){
  //light pixel for no wifi
}

void lowBattery(){
  //light pixel for low battery

}

