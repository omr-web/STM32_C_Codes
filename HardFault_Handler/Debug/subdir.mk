################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/stm32g0-mainc/include/startup_stm32g031k8tx.s 

C_SRCS += \
../lab3_problem1.c \
C:/stm32g0-mainc/include/system_stm32g0xx.c 

OBJS += \
./lab3_problem1.o \
./startup_stm32g031k8tx.o \
./system_stm32g0xx.o 

S_DEPS += \
./startup_stm32g031k8tx.d 

C_DEPS += \
./lab3_problem1.d \
./system_stm32g0xx.d 


# Each subdirectory must supply rules for building sources it contributes
lab3_problem1.o: ../lab3_problem1.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g -DSTM32 -DSTM32G031xx -DSTM32G0 -DNUCLEO_G031K8 -DSTM32G031K8Tx -DDEBUG -c -I../../include -O0 -ffunction-sections -fdata-sections -Wall -Wextra -pedantic -Wmissing-include-dirs -Wconversion -fstack-usage -MMD -MP -MF"lab3_problem1.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
startup_stm32g031k8tx.o: C:/stm32g0-mainc/include/startup_stm32g031k8tx.s
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g -c -x assembler-with-cpp -MMD -MP -MF"startup_stm32g031k8tx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
system_stm32g0xx.o: C:/stm32g0-mainc/include/system_stm32g0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g -DSTM32 -DSTM32G031xx -DSTM32G0 -DNUCLEO_G031K8 -DSTM32G031K8Tx -DDEBUG -c -I../../include -O0 -ffunction-sections -fdata-sections -Wall -Wextra -pedantic -Wmissing-include-dirs -Wconversion -fstack-usage -MMD -MP -MF"system_stm32g0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

