######################################
# includes
######################################
INCLUDES-$(CONFIG_STM32F4xx) += -I./vk.hardware/HAL/ST/STM32F4xx/inc


######################################
# sources
######################################
# ASM sources
ASM_SOURCES-y += 

# C sources
C_SOURCES-y += 

# Cpp sources
CPP_SOURCES-$(CONFIG_HAL_SYSTEM) += ./vk.hardware/HAL/ST/STM32F4xx/src/System.cpp
CPP_SOURCES-$(CONFIG_HAL_GPIO) += ./vk.hardware/HAL/ST/STM32F4xx/src/Gpio.cpp
CPP_SOURCES-$(CONFIG_HAL_GPI) += ./vk.hardware/HAL/ST/STM32F4xx/src/Gpi.cpp
CPP_SOURCES-$(CONFIG_HAL_GPO) += ./vk.hardware/HAL/ST/STM32F4xx/src/Gpo.cpp
CPP_SOURCES-$(CONFIG_HAL_NVIC) += ./vk.hardware/HAL/ST/STM32F4xx/src/Nvic.cpp
CPP_SOURCES-$(CONFIG_HAL_USART) += ./vk.hardware/HAL/ST/STM32F4xx/src/Usart.cpp
CPP_SOURCES-$(CONFIG_HAL_SPI) += ./vk.hardware/HAL/ST/STM32F4xx/src/Spi.cpp
CPP_SOURCES-$(CONFIG_HAL_I2C) += ./vk.hardware/HAL/ST/STM32F4xx/src/I2c.cpp
CPP_SOURCES-$(CONFIG_HAL_DMA) += ./vk.hardware/HAL/ST/STM32F4xx/src/Dma.cpp
CPP_SOURCES-$(CONFIG_HAL_FSMC) += ./vk.hardware/HAL/ST/STM32F4xx/src/Fsmc.cpp

