################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BH1750/BH1750.c 

OBJS += \
./BH1750/BH1750.o 

C_DEPS += \
./BH1750/BH1750.d 


# Each subdirectory must supply rules for building sources it contributes
BH1750/%.o BH1750/%.su BH1750/%.cyclo: ../BH1750/%.c BH1750/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/simon/Documents/CubeIDE/Projects/BeeStats/BH1750" -I"C:/Users/simon/Documents/CubeIDE/Projects/BeeStats/FRAM" -I"C:/Users/simon/Documents/CubeIDE/Projects/BeeStats/Core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BH1750

clean-BH1750:
	-$(RM) ./BH1750/BH1750.cyclo ./BH1750/BH1750.d ./BH1750/BH1750.o ./BH1750/BH1750.su

.PHONY: clean-BH1750

