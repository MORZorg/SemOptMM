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
../SCCSSEQ.cpp \
../SetArguments.cpp \
../boundcond.cpp \
../grounded.cpp \
../main.cpp \
../misc.cpp \
../pref.cpp 

OBJS += \
./AF.o \
./Argument.o \
./Labelling.o \
./OrClause.o \
./Preferred.o \
./SATFormulae.o \
./SCCSSEQ.o \
./SetArguments.o \
./boundcond.o \
./grounded.o \
./main.o \
./misc.o \
./pref.o 

CPP_DEPS += \
./AF.d \
./Argument.d \
./Labelling.d \
./OrClause.d \
./Preferred.d \
./SATFormulae.d \
./SCCSSEQ.d \
./SetArguments.d \
./boundcond.d \
./grounded.d \
./main.d \
./misc.d \
./pref.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


