# stm32f746-sdram
Using SDRAM on a [WaveShare STM32F746IGT6](https://www.waveshare.com/wiki/Core746I) board

## Notes
Using SDRAM is as easy as using a built-in RAM, however the trick is to initialize it properly. This is an example that exposes 8 Mbytes as a USB mass storage. Most of the code is generated, the interesting part is in `BSP_SDRAM_Init`.

