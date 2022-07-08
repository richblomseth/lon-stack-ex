################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FtxlApi/FtxlApi.cpp \
../FtxlApi/FtxlDefNvdFlashFs.cpp \
../FtxlApi/FtxlStack.cpp \
../FtxlApi/FtxlVectorHandlers.cpp 

OBJS += \
./FtxlApi/FtxlApi.o \
./FtxlApi/FtxlDefNvdFlashFs.o \
./FtxlApi/FtxlStack.o \
./FtxlApi/FtxlVectorHandlers.o 

CPP_DEPS += \
./FtxlApi/FtxlApi.d \
./FtxlApi/FtxlDefNvdFlashFs.d \
./FtxlApi/FtxlStack.d \
./FtxlApi/FtxlVectorHandlers.d 


# Each subdirectory must supply rules for building sources it contributes
FtxlApi/%.o: ../FtxlApi/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -DIZOT_PLATFORM -D_DEBUG -I../LonLinkIzoT/include -I../Lre/include -I../Shared/include -I../ShareIp/include -I../Stack/include -I../VxLayer/include -I../Target/include -I../Target/Drivers/Linux/SMIP/include -I../../Templates -I../FtxlApi/include -I../XMLParser -I../Pa/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


