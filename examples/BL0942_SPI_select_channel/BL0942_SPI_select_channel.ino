//
//    FILE: BL0942_SPI_select_channel.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/BL0942_SPI


#include "BL0942_SPI.h"


BL0942_SPI mySensor(4, 5, 6, 7);


void dummyChannelSelector(bool active)
{
  Serial.println(active ? "TRUE" : "FALSE");
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("BL0942_SPI_LIB_VERSION: ");
  Serial.println(BL0942_SPI_LIB_VERSION);
  Serial.println();

  SPI.begin();

  mySensor.begin();
  mySensor.setChannelSelector(dummyChannelSelector);

  //  numbers from the BL0942 APP NOTE 
  float RF = (390000.0 * 5 + 510.0) / 510.0;
  float SHUNT = 0.001;
  
  mySensor.calibrate(SHUNT, RF);  //  shunt in ohm, reduction factor voltage.


  Serial.println("get all registers");
  Serial.println("READ ONLY\n");

  mySensor.ensure_channel_selected(true);
  
  Serial.print("BL0942_REG_I_WAVE:\t");
  Serial.println(mySensor.getIWave());
  Serial.print("BL0942_REG_V_WAVE:\t");
  Serial.println(mySensor.getVWave());
  Serial.print("BL0942_REG_I_RMS:\t");
  Serial.println(mySensor.getIRMS());
  Serial.print("BL0942_REG_V_RMS:\t");
  Serial.println(mySensor.getVRMS());
  
  mySensor.ensure_channel_selected(false);


}


void loop()
{
  delay(2000);
}


//  -- END OF FILE --
