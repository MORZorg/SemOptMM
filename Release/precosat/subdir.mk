################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../precosat/precobnr.cc \
../precosat/precomain.cc \
../precosat/precosat.cc 

OBJS += \
./precosat/precobnr.o \
./precosat/precomain.o \
./precosat/precosat.o 

CC_DEPS += \
./precosat/precobnr.d \
./precosat/precomain.d \
./precosat/precosat.d 


# Each subdirectory must supply rules for building sources it contributes
precosat/%.o: ../precosat/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


