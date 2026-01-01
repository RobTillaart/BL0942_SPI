
[![Arduino CI](https://github.com/RobTillaart/BL0942_SPI/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/BL0942_SPI/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/BL0942_SPI/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/BL0942_SPI/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/BL0942_SPI/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/BL0942_SPI.svg)](https://github.com/RobTillaart/BL0942_SPI/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/BL0942_SPI/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/BL0942_SPI.svg?maxAge=3600)](https://github.com/RobTillaart/BL0942_SPI/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/BL0942_SPI.svg)](https://registry.platformio.org/libraries/robtillaart/BL0942_SPI)


# BL0942_SPI

Arduino library for BL0942 energy monitor, SPI interface.


## Description

**Experimental - Work in progress**

Note: this is work in progress, not functional complete yet.

This library is to use the BL0942 energy monitor.
The BL0942 is a configurable current and voltage sensor.
This library only implements and supports the SPI interface.
Therfor the SEL (protocol select) pin must be connected to HIGH (3.3V).

The device is a SPI slave, which works in half duplex mode,
at a maximum clock rate of 900 kHz.
It is not tested if it works well beyond that speed.

The library is not tested with hardware yet, so use with care.

Feedback as always is welcome.


### Hardware 2 models

Read datasheet for details.

There are two different BL0942 modules, one with 10 pins, and one with
14 pins. The "upper" 10 pins are the same, the 14 pins device has 4 extra.


|    name   |  10 pin  |  14 pin  |  description  |
|:---------:|:--------:|:--------:|:--------------|
|    VDD    |     1    |     1    |  power supply  (3.3V)
|     IP    |     2    |     2    |  current channel
|     IN    |     3    |     3    |  current channel
|     VP    |     4    |     4    |  voltage channel
|    GND    |     5    |     5    |  ground
|    CF1    |     6    |     6    |  output 1
|    SEL    |     7    |    11    |  LOW = UART  HIGH = SPI
|  CLK/BAUD |     8    |    12    |  SPI clock / BAUD select
|   RX/SDI  |     9    |    13    |  serial data in
|   TX/SDO  |    10    |    14    |  serial data out
|           |          |          |
|    A1     |          |     6    |  address pin, GND in SPI
|  A2_NCS   |          |     7    |  address pin, SELECT in SPI
|   CF2     |          |     8    |  output 2
|    ZX     |          |     9    |  zero crossing

Note: use pull ups on the serial data / clock lines.


From datasheet section 3.1:

In three wire mode (miso, mosi, clock), A1 and A2_NCS must be connected to GND. 
There can only be a single device on the SPI bus which is always selected.

In four-wire mode (select, miso, mosi, clock), the A1 pin is connected to GND,
and the A2_NCS must be driven LOW for the read or write operation.

If the A2 is held HIGH, the A2 bit in the COMMAND byte (write / read) is set HIGH,
and the device won't recognize the 10101000 (=write) or 01011000 (=read) command.
By pulling the A2_NCS LOW, that device will recognize the command and will 
response on the request, either read or write.

In hardware the **select-pin** given in the constructor **MUST** be connected to 
the **A2_NCS** pin of the devices to implement a proper select.
Note this will ONLY work with the 14 pins BL0942.



### Calibration

Call **calibrate(shunt, reductionFactor)** with shunt (typical = 0.001) and 
the reduction factor of the voltage divider (e.g. 4000).

The other calibration functions are to manually set the settings, optional adjust 
the values derived from **calibrate()** call.


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._


### BL0940

The BL0940 is not compatible, although its internal working is partial similar.
At least it needs other magic numbers, and has some other registers.
Support for the BL0940 is not planned.


### Related

- https://www.belling.com.cn/product_info.html?id=753  latest datasheet
- https://github.com/RobTillaart/printHelpers exponential notation floats
- https://github.com/SanteriLindfors/BL0942  UART library.


Application notes
- https://www.belling.com.cn/media/file_object/bel_product/BL0942/guide/BL0942%20APP%20Note_V1.04_cn.pdf


### Tested

not


## Interface

```cpp
#include "BL0942_SPI.h"
```

### Constructor

- **BL0942_SPI(uint8_t select, __SPI_CLASS__ \* mySPI = &SPI)** hardware SPI.
- **BL0942_SPI(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)** software SPI.
- **bool begin()** initializes internals.

The select pin should be connected to the A2_NCS pin.
When pulled LOW this device is selected.


### Calibration 1

- **void calibrate(float shunt, float reductionFactor = 1.0f)**
calibration of the current measurement based upon the shunt and the
calibration of the voltage based upon the reduction factor (ration)
of an optional voltage divider.

Typical values for shunt are in the range 0.001 - 1 Ohm.

Reduction factor of an ```VDD - R1 - R2 - GND``` ladder:
```
RF = (R1 + R2) / R2;  // e.g. R1=20K R2=100 => RF=20100/100=201.
```

Note the max current is 30A although one should keep the current under 15A.
The power dissipated by the shunt can be calculated:
```
P = 25 * 35 * shunt;
```

### Calibration 2

The following functions set the values per LSB directly for the core measurements registers.
The getter functions allow (run time) adjustments and help to manually calibrate
the device more precise.

- **float getVoltageLSB()**
- **void setVoltageLSB(float voltageLSB)**
- **float getCurrentLSB()**
- **void setCurrentLSB(float currentLSB)**
- **float getPowerLSB()**
- **void setPowerLSB(float powerLSB)**
- **float getEnergyLSB()**
- **void setEnergyLSB(float energyLSB)**


### Core

- **float getIWave()** return current in Amperes.
- **float getVWave()** return voltage in Volts.
- **float getIRMS()** return RMS current in Amperes.
- **float getVRMS()** return RMS voltage in Volts.
- **float getIRMSFast()** returns RMS current (faster less exact) in Amperes.
- **float getWatt()** returns power Watt
- **uint32_t getCFPulseCount()** returns counter (base for energy)
- **float getEnergy()** returns energy in kWh.
- **float getFrequency()** returns frequency ~ 50 or 60 Hz.
- **uint16_t getStatus()** returns status byte mask.

|  name                  |  value   |
|:-----------------------|:--------:|
|  BL0942_STAT_CF_REVP   |  0x0001  |
|  BL0942_STAT_CREEP     |  0x0002  |
|  BL0942_STAT_I_ZX_LTH  |  0x0100  |
|  BL0942_STAT_V_ZX_LTH  |  0x0200  |


### Configuration

Read datasheet for details.

TODO
- not tested
- find their meaning / how these workor affect measurements.
- elaborate API + code details

#### RMS offset

- **float getCurrentRMSOffset()**
- **void setCurrentRMSOffset(float offset)**

#### Power creep

- **float getPowerCreep()**
- **void setPowerCreep(float creep)**

#### Other

- **float getFastRMSThreshold()**
- **void setFastRMSThreshold(float threshold)**
- **uint8_t getFastRMSCycles()**
- **void setFastRMSCycles(uint8_t cycles)** cycles = 0..7
- **uint8_t getFrequencyCycles()**
- **void setFrequencyCycles(uint8_t cycles)** cycles = 0..2

#### OutputConfig

- **uint8_t getOutputConfigMask()**
- **void setOutputConfigMask(uint8_t mask)** mask = 0..63

TODO config register table

#### UserMode

- **uint16_t getUserMode()**
- **void setUserMode(uint16_t mode)**  mode = 0x0000 .. 0x03FF

TODO mode register table

#### Gain

- **uint8_t getCurrentGain()**
- **void setCurrentGain(uint8_t gain)**

|  name            |  value  |  gain  |
|:-----------------|:-------:|:-------|
|  BL0942_GAIN_1   |   0x00  |    1   |
|  BL0942_GAIN_4   |   0x01  |    4   |
|  BL0942_GAIN_16  |   0x02  |   16   |
|  BL0942_GAIN_24  |   0x03  |   24   |


### Miscelaneous

Read datasheet for details.

TODO elaborate

- **void softReset()**
- **uint8_t getWriteProtect()**
- **void setWriteProtect()**


### SPI

To be used only if one needs a specific speed for hardware SPI.
Has no effect on software SPI.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true / false depending on constructor.

_3.1.3 Fault Tolerant Mechanism of SPI Interface
If MCU send 6 bytes (0xFF), the BL0942 perform a reset function on the SPI communication interface. => **resetSPI()**_


### Error

- **uint8_t getLastError()** returns last error of low level communication.

|  value  |  error                 |  notes  |
|:-------:|:-----------------------|:--------|
|     0   |  BL0942_OK             |
|    -1   |  BL0942_ERR_WRITE      |  not used
|    -2   |  BL0942_ERR_READ       |  not used
|    -3   |  BL0942_ERR_CHECKSUM   |


### Channel selector

TODO elaborate

```cpp
typedef void (*channelSelector)(bool active);
```

- **void setChannelSelector(channelSelector selector)**
- **void ensure_channel_selected(bool active)**

See example.


## Future

#### Must

- get API functional complete
- verify proper working of all functions (configuration ones)
- improve documentation
- get hardware to test test and test


#### Should

- investigate multi device
  - SELECT pin for SPI
  - multi device => AND gate with clock pin
  - multiplexer?
- add examples
- improve error handling
- investigate unit tests
- **resetSPI()** function?  section 3.1.3
-

#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


