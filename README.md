[![Version: 1.0 Release](https://img.shields.io/badge/Version-1.0%20Release-green.svg)](https://github.com/0x007e/drivers-crypto-rng90) ![Build](https://github.com/0x007e/drivers-crypto-rng90/actions/workflows/release.yml/badge.svg) [![License GPLv3](https://img.shields.io/badge/License-GPLv3-lightgrey)](https://www.gnu.org/licenses/gpl-3.0.html)

# `RNG90 Crypto Driver`

This hardware abstracted driver can be used to interact with an [RNG90](#additional-information) over `TWI`/`I2C`. The hardware layer is fully abstract an can be switched between different plattforms. The `TWI`/`I2C` library has to impelement the [twi.h](https://0x007e.github.io/drivers-crypto-rng90/twi_8h.html)-header used in this repository.

## File Structure

![File Structure](https://0x007e.github.io/drivers-crypto-rng90/rng90_8c__incl.png)

```
drivers/
└── crypto/
    └── rng90/
        ├── rng90.c
        └── rng90.h

hal/
├── common/
|   ├── defines/
|   |   └── TWI_defines.h
|   └── enums/
|       └── TWI_enums.h
└── avr0/
    └── twi/
        ├── twi.c
        └── twi.h

utils/
├── macros/
|   └── stringify.h
├── crc/
|   ├── crc16.c
|   └── crc16.h
└── systick/
    ├── systick.c
    └── systick.h
```

> The plattform `avr0` can completely be exchanged with any other hardware abstraction library.

## Downloads

The library can be downloaded (`zip` or `tar`), cloned or used as submodule in a project.

| Type      | File               | Description              |
|:---------:|:------------------:|:-------------------------|
| Library   | [zip](https://github.com/0x007E/drivers-crypto-rng90/releases/latest/download/library.zip) / [tar](https://github.com/0x007E/drivers-crypto-rng90/releases/latest/download/library.tar.gz) | RNG90 crypto library including all required libraries (including `hal-avr0-twi`). |

### Using with `git clone`

``` bash
mkdir -p ./drivers/crypto/
git clone https://github.com/0x007E/drivers-crypto-rng90.git ./drivers/crypto/
mv ./drivers/crypto/drivers-crypto-rng90 ./drivers/crypto/rng90

mkdir -p ./hal/
git clone https://github.com/0x007E/hal-common.git ./hal
mv ./hal/hal-common ./hal/common

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# Hardware abstraction layer of TWI (Must fit the used plattform)
mkdir -p ./hal/avr0/
git clone https://github.com/0x007E/hal-avr0-twi.git ./hal/avr0
mv ./hal/avr0/hal-avr0-twi ./hal/avr0/twi
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

mkdir -p ./utils/
git clone https://github.com/0x007E/utils-macros.git   ./utils
git clone https://github.com/0x007E/utils-crc.git      ./utils
git clone https://github.com/0x007E/utils-systick.git  ./utils
mv ./utils/utils-macros  ./utils/macros
mv ./utils/utils-crc     ./utils/crc
mv ./utils/utils-systick ./utils/systick
```

### Using as `git submodule`

``` bash
git submodule add https://github.com/0x007E/drivers-crypto-rng90.git  drivers/crypto/rng90
git submodule add https://github.com/0x007E/hal-common.git            hal/common

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# Hardware abstraction layer of TWI (Must fit the used plattform)
git submodule add https://github.com/0x007E/hal-avr0-twi.git          hal/avr0/twi
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

git submodule add https://github.com/0x007E/utils-macros.git          utils/macros
git submodule add https://github.com/0x007E/utils-crc.git             utils/crc
git submodule add https://github.com/0x007E/utils-systick.git         utils/systick
```

## Programming

``` c
#include "../hal/PLATFORM/twi/twi.h"

#include "../lib/drivers/crypto/rng90/rng90.h"
#include "../lib/utils/systick/systick.h"

// Called every ~ milli-/microsecond!
ISR(...)
{
	systick_tick();
}

void systick_timer_wait_ms(unsigned int ms)
{
	systick_timer_wait(ms);
}

int main(void)
{
	systick_init();
	twi_init();

    RNG90_Status status = rng90_init();

    // Serial Number:
    unsigned char serial[RNG90_OPERATION_READ_SERIAL_SIZE];

    if(rng90_serial(serial) == RNG90_Status_Success)
	{
        // Output -> serial
	}

    // Device Info:
    RNG90_Info info;

    if(rng90_info(&info) == RNG90_Status_Success)
	{
	    // Output:
        // -> info.DeviceID
        // -> info.Revision
        // -> info.RFU
        // -> info.SiliconID
	}

    // Read random numbers into buffer
    status = rng90_random(rng_numbers);
			
    for (unsigned char i=0; i < RNG90_OPERATION_RANDOM_RNG_SIZE; i++)
    {
        // Output -> rng_numbers[i]
    }
}
```

# Additional Information

| Type       | Link               | Description              |
|:----------:|:------------------:|:-------------------------|
| RNG90 | [pdf](https://ww1.microchip.com/downloads/aemDocuments/documents/SCBU/ProductDocuments/DataSheets/RNG90-CryptoAuthentication-Data-Sheet-DS40002499.pdf) | RNG90 CryptoAuthentication |

---

R. GAECHTER