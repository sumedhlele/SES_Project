################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Project_App/Src/Project_Application.c 

OBJS += \
./Core/Project_App/Src/Project_Application.o 

C_DEPS += \
./Core/Project_App/Src/Project_Application.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Project_App/Src/%.o Core/Project_App/Src/%.su Core/Project_App/Src/%.cyclo: ../Core/Project_App/Src/%.c Core/Project_App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/sumedh/Documents/MTech_EmbeddedSystems/Software_for_Embedded_Systems/Mini_Project/SES_Project/STM32_MiniProject/Core/Project_App/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Project_App-2f-Src

clean-Core-2f-Project_App-2f-Src:
	-$(RM) ./Core/Project_App/Src/Project_Application.cyclo ./Core/Project_App/Src/Project_Application.d ./Core/Project_App/Src/Project_Application.o ./Core/Project_App/Src/Project_Application.su

.PHONY: clean-Core-2f-Project_App-2f-Src

