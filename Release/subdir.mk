################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AF.cpp \
../Argument.cpp \
../Labelling.cpp \
../OrClause.cpp \
../Preferred.cpp \
../SATFormulae.cpp \
../SetArguments.cpp \
../main.cpp \
../misc.cpp 

OBJS += \
./AF.o \
./Argument.o \
./Labelling.o \
./OrClause.o \
./Preferred.o \
./SATFormulae.o \
./SetArguments.o \
./main.o \
./misc.o 

CPP_DEPS += \
./AF.d \
./Argument.d \
./Labelling.d \
./OrClause.d \
./Preferred.d \
./SATFormulae.d \
./SetArguments.d \
./main.d \
./misc.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


