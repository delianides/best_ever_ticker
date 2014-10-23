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
#include "neomatrix.h"
#include "flashee-eeprom.h"
using namespace Flashee;

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2

//I don't need WIFI right now
SYSTEM_MODE(SEMI_AUTOMATIC);

//RESTful function for receiving data
int setSalvations(String count);

//Print Salvations
void showSalvations(int salvations, int oldSalvations);

//Helper function to count the number of digits so the cursor moves.
int countDigits(int digits);

// Turn LED on for no wifi...
void missingWifi();

// Turn LED on for low battery...
void lowBattery();

//Define Matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8,8,5,1, PIXEL_PIN,
  NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_PROGRESSIVE +
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE
);

void setup() {
  //Initalize the reader
  FlashDevice* device = Devices::createWearLevelErase();
  FlashReader reader(device);

  Serial.begin(9600);
  Serial.println("Starting setup....");

  //Wifi will be disabled at this point
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(30);
  matrix.setTextColor(matrix.Color(80,255,0));
  matrix.fillScreen(0);

  //We're not connected to WIFI just yet but we need a number to show
  int salvations = reader.readInt();

  //Show salvations unless something isn't stored in memory.
  if(salvations >= 0){
    showSalvations(salvations, 0);
  }else{
    matrix.print(F("******"));
    matrix.show();
  }

  //Now that everything is done and being shown, lets quietly connect to wifi.
  if ( Spark.connected() == false){
    Spark.connect();
  }
}

void loop() {
  if ( Spark.connected() == true){
    //let the web know we are alive!
    Spark.publish("ticker-connected");
    //Make sure the function is registered
    Spark.function("celebrate", setSalvations);
  }else{
    //No wifi?
    missingWifi();
  }

  //Read analog input for battery life.
}

int setSalvations(String count){
  //Convert count string to integer.
  int salvations = atoi(count.c_str());

  //Initalize the flash device for saving the new number
  FlashDevice* device = Devices::createWearLevelErase();

  //Get the old number.
  FlashReader reader(device);
  int oldSalvations = reader.readInt();

  //Write the new number.
  FlashWriter writer(device);
  writer.writeInt(salvations);

  //Output Serial for debug.
  Serial.print("Salvations: ");
  Serial.println(salvations);

  //Fun Print function
  showSalvations(salvations, oldSalvations);

  //Restful function returns count
  return salvations;
}

void showSalvations(int salvations, int oldSalvations){
  //Initalize Digits
  int digits = 1;
  //Loop through a counter until it reaches salvations. This loop happens very fast.
  for(int c = oldSalvations; c <= salvations; c = c + (rand() % 30 + 200)){
    //Fill Screen with black
    matrix.fillScreen(0);
    //Count digits
    digits = countDigits(c);
    //Place cursor
    matrix.setCursor(41-(digits*6),0);
    //set the data within the matrix
    matrix.print(F(c));
    //Show
    matrix.show();
    //delay the next interation for 35ms
    delay(35);
  }

  //The following happens at the very end but because the ticker is moving so fast you wouldn't see it happen.
  //This is just to ensure the final number displayed is the correct total.
  matrix.fillScreen(0);
  digits = countDigits(salvations);
  matrix.setCursor(41-(digits*6),0);
  matrix.print(F(salvations));
  matrix.show();

  return;
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

//Show YELLOW LED if no WIFI.
void missingWifi(){
  matrix.drawPixel(1,8,matrix.Color(255,255,35));
  matrix.show();
}

//Show RED LED if low battery.
void lowBattery(){
  matrix.drawPixel(0,8,matrix.Color(255,70,0));
  matrix.show();
}

