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


//  ERROR CONSTANTS
const int BL0942_OK = 0;
const int BL0492_ERR_WRITE = -1;
const int BL0492_ERR_READ = -2;
const int BL0492_ERR_CHECKSUM = -3;



class BL0942_SPI
{
public:
  BL0942_SPI(uint8_t select, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  BL0942_SPI(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  bool     begin();

  //  read only registers
  float    getIWave();
  float    getVWave();
  float    getIRMS();
  float    getVRMS();
  float    getIRMSFast();
  float    getWatt();
  uint32_t getCFPulseCount();
  float    getFrequency();
  uint16_t getStatus();

  //  read write registers




  //  TODO more registers.









  //       SPI
  void     setSPIspeed(uint32_t speed);  //  900 KHz max
  uint32_t getSPIspeed();
  bool     usesHWSPI();

  //       ERROR
  int      getLastError();


  //  should be protected
  //  for now available for testing
  int      writeRegister(uint8_t regAddr, uint32_t value);
  uint32_t readRegister(uint8_t regAddr);
  uint8_t  swSPI_transfer(uint8_t val);

protected:
  uint8_t  _dataOut;
  uint8_t  _dataIn;
  uint8_t  _select;
  uint8_t  _clock;
  bool     _hwSPI;
  uint32_t _SPIspeed = 16000000;

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;

  int     _error;
};


//  -- END OF FILE --





