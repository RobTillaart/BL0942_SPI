//
//    FILE: BL0942_SPI_select_channel.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test program basic behaviour channel selector
//     URL: https://github.com/RobTillaart/BL0942_SPI


#include "BL0942_SPI.h"

BL0942_SPI mySensor(4, 5, 6, 7);

class YAC
{
public:
  YAC() {};
  void channelSelect(bool active)
  {
    Serial.print(active ? "TRUE " : "FALSE ");
    Serial.println(x++);
    Serial.println();
  };
private:
  int x = 0;
};

YAC yy;

//  helper function
void f(bool active)
{
  yy.channelSelect(active);
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

  mySensor.setChannelSelector(f);
  // mySensor.setChannelSelector( reinterpret_cast<void (*)(bool)> (&yy)->channelSelect );
  // mySensor.setChannelSelector( reinterpret_cast<void (*)(bool)> (pyy->channelSelect) );
  // mySensor.setChannelSelector( yy::channelSelect );

  //  numbers from the BL0942 APP NOTE 
  float RF = (390000.0 * 5 + 510.0) / 510.0;
  float SHUNT = 0.001;
  
  mySensor.calibrate(SHUNT, RF);  //  shunt in ohm, reduction factor voltage.


  Serial.println("get a register twice\n");

  mySensor.ensure_channel_selected(true);
  
  Serial.print("BL0942_REG_I_WAVE:\t");
  Serial.println(mySensor.getIWave());
  
  mySensor.ensure_channel_selected(false);


  mySensor.ensure_channel_selected(true);
  
  Serial.print("BL0942_REG_I_WAVE:\t");
  Serial.println(mySensor.getIWave());
  
  mySensor.ensure_channel_selected(false);
}


void loop()
{
  delay(2000);
}


//  -- END OF FILE --
