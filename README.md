
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

**Experimental**

This library is to use the BL0942 energy monitors.
This is a configurable current and voltage sensor.
This library only implements and supports the SPI interface.
Therfor the SEL (select) pin must be connected to HIGH (3.3V).

The device is a SPI slave only, which works in half duplex mode only,
at a maximum clock rate of 900 KHz.
It is not tested if it works well beyond that speed.





The library is not tested with hardware yet.

Feedback as always is welcome.


### Hardware 2 models

Read datasheet for details.

There are two different BL0942 modules, one with 10 pins, and one with
14 pins. The "upper" 10 pins are the same, the 14 pins device has 4 extra.


|    name   |  10 pin  |  14 pin  |  description             |
|:---------:|:--------:|:--------:|:-------------------------|
|    VDD    |     1    |     1    |  power supply  (3.3V)    |
|     IP    |     2    |     2    |  current channel         |
|     IN    |     3    |     3    |  current channel         |
|     VP    |     4    |     4    |  voltage channel         |
|    GND    |     5    |     5    |  ground                  |
|    CF1    |     6    |     6    |  output 1                |
|    SEL    |     7    |    11    |  LOW = UART  HIGH = SPI  |
|  CLK/BAUD |     8    |    12    |  SPI clock / BAUD select |
|   RX/SDI  |     9    |    13    |  serial data in          |
|   TX/SDO  |    10    |    14    |  serial data out         |
|           |          |          |                          |
|    A1     |          |     6    |  address pin (UART)      |
|  A2_NCS   |          |     7    |  address pin (UART)      |
|   CF2     |          |     8    |  output 2                |
|    ZX     |          |     9    |  zero crossing           |

Note: use pull ups on the serial data / clock lines.

Note from page 20, section 3.1
- three or four wire communication method. In three wire mode, A2_NCS is connected to GND. In four-wire mode, the A2_NCS must be driven low for the entire read or write operation.


### Calibration


TODO HOW TO

Sketch neeeded


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._


### Related

TODO

- https://github.com/RobTillaart/printHelpers exponential notation floats
- https://github.com/SanteriLindfors/BL0942  UART library.


### Tested

TODO


## Interface

```cpp
#include "BL0942_SPI.h"
```

### Constructor

- **BL0942_SPI(uint8_t select, __SPI_CLASS__ \* mySPI = &SPI)** hardware SPI.
- **BL0942_SPI(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)** software SPI.
- **bool begin()** initializes internals.


### Calibration





### Core

TODO elaborate, units + range

- **float getIWave()**
- **float getVWave()**
- **float getIRMS()**
- **float getVRMS()**
- **float getIRMSFast()**
- **float getWatt()**
- **uint32_t getCFPulseCount()**
- **float getFrequency()**
- **uint16_t getStatus()**

TODO status bits table


### Configuration

TODO elaborate, split in more sections?

- **float getCurrentRMSOffset()**
- **void setCurrentRMSOffset(float offset)**
- **float getPowerCreep()**
- **void setPowerCreep(float creep)**
- **float getFastRMSThreshold()**
- **void setFastRMSThreshold(float threshold)**
- **uint8_t getFastRMSCycles()**
- **void setFastRMSCycles(uint8_t cycles)** cycles = 0..7
- **uint8_t getFrequencyCycles()** cycles = 0..2
- **void setFrequencyCycles(uint8_t cycles)**
- **uint8_t getOutputConfigMask()**
- **void setOutputConfigMask(uint8_t mask)** mask = 0..63
- **uint16_t getUserMode()**
- **void setUserMode(uint16_t mode)**  mode = 0x0000 .. 0x03FF
- **uint8_t getCurrentGain()**
- **void setCurrentGain(uint8_t gain)**

### Miscelaneous

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


3.1.3 Fault Tolerant Mechanism of SPI Interface
If MCU send 6 bytes (0xFF), the BL0942 perform a reset function on the SPI communication interface.



### Error

- **uint8_t getLastError()** returns last error of low level communication.



## Future

#### Must

- improve documentation
- get hardware to test test and test
- investigate SELECT pin for SPI
  - multi device => AND gate with clock pin


#### Should

- add examples
- improve error handling
- investigate unit tests
- resetSPI function?  section 3.1.3

#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


