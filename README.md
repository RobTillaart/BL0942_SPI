
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

This library is to use BL0942 sensor through its SPI interface.


page 20, section 3.1
- If SEL Pin is pulled up to VDD, the communication method is SPI
- slave mode
- Half duplex communication, the maximum SPI speed is 900khz
- 8-bits data transmission, data order with MSB-first shifting
- Fixed clock polarity and phase (CPOL = 0, CPHA = 1)
- three or four wire communication method. In three wire mode, A2_NCS is connected to GND. In four-wire mode, the A2_NCS must be driven low for the entire read or write operation.


Feedback as always is welcome.


### hardware 2 models

10 pin module
14 pin module - address pins voor UART (four devices possible

table pins
|  nr  |  name  |  10 pins  |  14 pins  |  description |
|:----:|:------:|:---------:|:---------:|:-------------|
| 1-14 |  TODO  |







### Datasheet warning

_Do not apply this product to safety protection devices or emergency stop equipment, 
and any other applications that may cause personal injury due to the product's failure._



### Related

TODO


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
- get hardware to test

#### Should

- improve error handling

#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


