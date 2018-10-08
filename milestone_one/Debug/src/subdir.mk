################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/GPIO_driver.c \
../src/TIM8_BRK_TIM12_IRQHandler.c \
../src/channel_monitor.c \
../src/main.c \
../src/timer_12.c 

OBJS += \
./src/GPIO_driver.o \
./src/TIM8_BRK_TIM12_IRQHandler.o \
./src/channel_monitor.o \
./src/main.o \
./src/timer_12.o 

C_DEPS += \
./src/GPIO_driver.d \
./src/TIM8_BRK_TIM12_IRQHandler.d \
./src/channel_monitor.d \
./src/main.d \
./src/timer_12.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -I"C:/Users/doughertymj/Documents/CE 4951/Milestone1/raderschoolofbusiness/milestone_one/inc" -include"C:/Users/doughertymj/Documents/CE 4951/Milestone1/raderschoolofbusiness/milestone_one/inc/channel_monitor.h" -include"C:/Users/doughertymj/Documents/CE 4951/Milestone1/raderschoolofbusiness/milestone_one/inc/timer_12.h" -include"C:/Users/doughertymj/Documents/CE 4951/Milestone1/raderschoolofbusiness/milestone_one/inc/GPIO_driver.h" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


