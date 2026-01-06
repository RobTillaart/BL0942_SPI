//
//    FILE: OKNX_BL0942_SPI_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test dependency injection for OKNX
//     URL: https://github.com/RobTillaart/BL0942_SPI


//  simulate SwitchActuatorChannel.h

#define OPENKNX_SWA_BL0942_SPI

class SwitchActuatorChannel
{
  public:
    SwitchActuatorChannel() {};
    // ...
    static void bl0942ChannelSelector(bool active)
    {
      Serial.print(active ? "TRUE " : "FALSE ");
      Serial.println();
    };
    // ...
};

SwitchActuatorChannel sac;


#include "BL0942_SPI.h"

OKNX_BL0942_SPI mySensor(4, 5, 6, 7);


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

  //  register SwitchActuatorChannel
  mySensor.setChannelSelector(&sac);


  //  numbers from the BL0942 APP NOTE
  float RF = (390000.0 * 5 + 510.0) / 510.0;
  float SHUNT = 0.001;
  mySensor.calibrate(SHUNT, RF);  //  shunt in ohm, reduction factor voltage.


  Serial.println("get a notification twice\n");

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
}


//  -- END OF FILE --
