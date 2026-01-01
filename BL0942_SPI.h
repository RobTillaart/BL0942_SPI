#pragma once
//
//    FILE: BL0942_SPI.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-12-29
// VERSION: 0.1.0
// PURPOSE: Arduino library for BL0942 energy monitor, SPI interface.
//     URL: https://github.com/RobTillaart/BL0942_SPI
//
//  uses MODE1, CPOL = 0, CPHA = 1
//
//  explain connections for SPI
//  UART/SPI mode selection (0: UART 1: SPI), internal pull-down resistance,
//  connected to GND is 0 level (UART),
//  connected directly to VDD is high level (SPI)


#include "Arduino.h"
#include "SPI.h"


#define BL0942_SPI_LIB_VERSION         (F("0.1.0"))

#ifndef __SPI_CLASS__
  //  MBED must be tested before RP2040
  #if defined(ARDUINO_ARCH_MBED)
  #define __SPI_CLASS__   SPIClass
  #elif defined(ARDUINO_ARCH_RP2040)
  #define __SPI_CLASS__   SPIClassRP2040
  #else
  #define __SPI_CLASS__   SPIClass
  #endif
#endif


//
//  ERROR CONSTANTS
//
const int BL0942_OK = 0;
const int BL0942_ERR_WRITE = -1;
const int BL0942_ERR_READ = -2;
const int BL0942_ERR_CHECKSUM = -3;


//
//  MODE REGISTER (0x19) BIT MASKS
//  read datasheet page 10 for details
//
const int BL0942_MODE_CF_ENABLE  = 0x004;
const int BL0942_MODE_RMS_UPDATE = 0x008;  //  0 = 400ms, 1 = 800 ms;
const int BL0942_MODE_RMS_FAST   = 0x010;  //  0 = full wave, 1 = AC Wave
const int BL0942_MODE_AC_FREQ    = 0x020;  //  0 = 50 Hz, 1 = 60 Hz
const int BL0942_MODE_CF_CNT_CLR = 0x040;
const int BL0942_MODE_CF_CNT_ADD = 0x080;
const int BL0942_MODE_UART_4800  = 0x000;
const int BL0942_MODE_UART_9600  = 0x100;
const int BL0942_MODE_UART_19200 = 0x200;
const int BL0942_MODE_UART_38400 = 0x300;


//
//  OUTPUT CONFIG REGISTER (0x18) BIT MASKS
//  read datasheet page 11 for details
//
const int BL0942_CF1_ACTIVE_ENERGY = 0x00;  //  default
const int BL0942_CF1_OVER_CURRENT  = 0x01;
const int BL0942_CF1_ZERO_CROSS_V  = 0x02;
const int BL0942_CF1_ZERO_CROSS_I  = 0x03;

const int BL0942_CF2_ACTIVE_ENERGY = 0x00;
const int BL0942_CF2_OVER_CURRENT  = 0x04;  //  default
const int BL0942_CF2_ZERO_CROSS_V  = 0x08;
const int BL0942_CF2_ZERO_CROSS_I  = 0x0C;

const int BL0942_ZX_ACTIVE_ENERGY  = 0x00;
const int BL0942_ZX_OVER_CURRENT   = 0x10;
const int BL0942_ZX_ZERO_CROSS_V   = 0x20;  //  default
const int BL0942_ZX_ZERO_CROSS_I   = 0x30;


//
//  STATUS REGISTER (0x09) BIT MASKS
//  read datasheet page 11 for details
//
const int BL0942_STAT_CF_REVP  = 0x0001;
const int BL0942_STAT_CREEP    = 0x0002;
const int BL0942_STAT_I_ZX_LTH = 0x0100;
const int BL0942_STAT_V_ZX_LTH = 0x0200;


//
//  GAIN REGISTER (0x1A) BIT MASKS
//  read datasheet page 11 for details
//
const int BL0942_GAIN_1  = 0x00;
const int BL0942_GAIN_4  = 0x01;
const int BL0942_GAIN_16 = 0x02;  //  default
const int BL0942_GAIN_24 = 0x03;




class BL0942_SPI
{
public:
  //  HARDWARE SPI
  BL0942_SPI(uint8_t select, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI  (dataIn == "MISO", dataOut == "MOSI")
  BL0942_SPI(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  bool     begin();

  //  CALIBRATION
  void     calibrate(float shunt, float reductionFactor = 1.0f);
  //  direct calibration of the least significant bits per measurement.
  float    getVoltageLSB();
  void     setVoltageLSB(float voltageLSB);
  float    getCurrentLSB();
  void     setCurrentLSB(float currentLSB);
  float    getPowerLSB();
  void     setPowerLSB(float powerLSB);
  float    getEnergyLSB();
  void     setEnergyLSB(float energyLSB);

  //  READ ONLY registers
  float    getIWave();
  float    getVWave();
  float    getIRMS();
  float    getVRMS();
  float    getIRMSFast();
  float    getWatt();
  uint32_t getCFPulseCount();
  float    getEnergy();       //  kWh
  float    getFrequency();

  //  status bit masks see above
  uint16_t getStatus();


  //  READ WRITE registers
  //  offset = ??
  float    getCurrentRMSOffset();
  void     setCurrentRMSOffset(float offset);

  //  creep = ??
  float    getPowerCreep();
  void     setPowerCreep(float creep);

  //  threshold = ??
  float    getFastRMSThreshold();
  void     setFastRMSThreshold(float threshold);

  //  cycles = 0..7
  uint8_t  getFastRMSCycles();
  void     setFastRMSCycles(uint8_t cycles);

  //  cycles = 0..2
  uint8_t  getFrequencyCycles();
  void     setFrequencyCycles(uint8_t cycles);

  //  bit masks see above
  //  mask = 0..63
  uint8_t  getOutputConfigMask();
  void     setOutputConfigMask(uint8_t mask);

  //  bit masks see above
  //  mode = 0x0000 .. 0x03FF
  uint16_t getUserMode();
  void     setUserMode(uint16_t mode);

  //  bit masks see above
  //  gain = 0..3
  uint8_t  getCurrentGain();
  void     setCurrentGain(uint8_t gain);

  void     softReset();
  uint8_t  getWriteProtect();
  void     setWriteProtect(bool wp);


  //       SPI
  //       900 KHz max
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();

  //       ERROR
  int      getLastError();


  //  should be protected
  //  for now available for testing
  int      writeRegister(uint8_t regAddr, uint32_t value);
  uint32_t readRegister(uint8_t regAddr);


  //
  //  CHANNEL-SELECTOR
  //  in .h file for now.
  //
  //
  typedef void (*channelSelector)(bool active);

  void setChannelSelector(channelSelector selector)
  {
     _selector = selector;
  }

  void ensure_channel_selected(bool active)
  {
    if (_selector) _selector(active);
    else digitalWrite(_select, active ? LOW : HIGH);
  }

  channelSelector _selector = nullptr;


protected:
  uint8_t  _dataOut;
  uint8_t  _dataIn;
  uint8_t  _select;
  uint8_t  _clock;
  int      _error;

  //  TODO
  //  (semi) constants to set in begin() TODO.
  float    _internVolts  = 1.218;
  float    _dividerRatio = 1.0;
  //  how to determine magic numbers
  float    _powerLSB   = 1.0;
  float    _voltageLSB = 1.0;
  float    _currentLSB = 1.0;
  float    _energyLSB  = 1.0;


  bool     _hwSPI;
  uint32_t _SPIspeed = 16000000;
  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;

  // int      writeRegister(uint8_t regAddr, uint32_t value);
  // uint32_t readRegister(uint8_t regAddr);
  uint8_t  swSPI_transfer(uint8_t val);

};


//  -- END OF FILE --





