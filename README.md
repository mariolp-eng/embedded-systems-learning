# embedded-systems-learning
Documented process of learning embedded systems.

## Structure

- `01-gpio-basics/` — GPIO basics
- `02-i2c-mpu6050/` — I2C communication with MPU6050
- `03-sd-logging/` — SD card data logging

## Cloning

ARM (CMSIS) and ST (STM32F4 device headers and HAL) libraries are included as Git submodules under `Drivers/`. To fetch them along with the repository:

```bash
git clone --recurse-submodules https://github.com/marioLP-eng/embedded-systems-learning.git
```

If you already cloned it without submodules and `Drivers/` is empty:

```bash
git submodule update --init
```
