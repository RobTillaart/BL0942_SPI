//
//    FILE: BL0942_SPI_demo_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/BL0942_SPI_demo


#include "BL0942_SPI.h"


BL0942_SPI mySensor(4, 5, 6, 7);


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

  Serial.println("get all registers in float\n");

  Serial.print("BL0942_REG_I_WAVE:\t");
  Serial.println(mySensor.getIWave());
  Serial.print("BL0942_REG_V_WAVE:\t");
  Serial.println(mySensor.getVWave());
  Serial.print("BL0942_REG_I_RMS:\t");
  Serial.println(mySensor.getIRMS());
  Serial.print("BL0942_REG_V_RMS:\t");
  Serial.println(mySensor.getVRMS());
  /*
    Serial.print("BL0942_REG_I_FAST_RMS:\t");
    Serial.println(mySensor.readRegister(0x05), HEX);
    Serial.print("BL0942_REG_WATT:\t");
    Serial.println(mySensor.readRegister(0x06), HEX);
    Serial.print("BL0942_REG_CF_CNT:\t");
    Serial.println(mySensor.readRegister(0x07), HEX);
    Serial.print("BL0942_REG_FREQ:\t");
    Serial.println(mySensor.readRegister(0x08), HEX);
    Serial.print("BL0942_REG_STATUS:\t");
    Serial.println(mySensor.readRegister(0x09), HEX);
    Serial.print("BL0942_REG_I_RMSOS:\t");
    Serial.println(mySensor.readRegister(0x12), HEX);
    Serial.print("BL0942_REG_WA_CREEP:\t");
    Serial.println(mySensor.readRegister(0x14), HEX);
    Serial.print("BL0942_REG_I_FAST_RMS_TH:\t");
    Serial.println(mySensor.readRegister(0x15), HEX);
    Serial.print("BL0942_REG_I_FAST_RMS_CYC:\t");
    Serial.println(mySensor.readRegister(0x16), HEX);
    Serial.print("BL0942_REG_FREQ_CYC:\t");
    Serial.println(mySensor.readRegister(0x17), HEX);
    Serial.print("BL0942_REG_OT_FUNX:\t");
    Serial.println(mySensor.readRegister(0x18), HEX);
    Serial.print("BL0942_REG_MODE:\t");
    Serial.println(mySensor.readRegister(0x19), HEX);
    Serial.print("BL0942_REG_GAIN_CR:\t");
    Serial.println(mySensor.readRegister(0x1A), HEX);
    Serial.print("BL0942_REG_SOFT_RESET:\t");
    Serial.println(mySensor.readRegister(0x1C), HEX);
    Serial.print("BL0942_REG_USR_WRPROT:\t");
    Serial.println(mySensor.readRegister(0x1D), HEX);
  */
}


void loop()
{

  delay(2000);
}


//  -- END OF FILE --
