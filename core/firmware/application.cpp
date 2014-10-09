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

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B

//I don't need WIFI right now
//SYSTEM_MODE(MANUAL);

int setSalvationCount(String count);


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8,8,5,1, PIXEL_PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  PIXEL_TYPE);

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(30);
  matrix.setTextColor(matrix.Color(80,255,0));
  matrix.fillScreen(0);
  matrix.setCursor(0,0);

  int addr = 1;
  int value = EEPROM.read(addr);
  if(value){
    matrix.print(F(value));
    matrix.show();
  }else{
    matrix.print(F("999999"));
    matrix.show();
  }

  Spark.function("celebrate", setSalvationCount);
}

void loop() {

}

int setSalvationCount(String count){
  matrix.fillScreen(0);
  matrix.setCursor(0,0);
  matrix.print(F(count));
  matrix.show();
  return 1;
}

