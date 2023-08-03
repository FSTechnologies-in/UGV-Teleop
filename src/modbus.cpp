
#include <stdio.h>
#include <iostream>
#include "rs485_modbus_rtu.h"
#include "mod8i8o.h"
#include "rs485_modbus_rtu.cpp"
#include "mod8i8o.cpp"
#include <unistd.h>
/*
   device_id -> Identify the Modbus based on salve id
   pin -> Relay pin number
   value->set, clear
   mode -> input/output_iterator
*/
   
int modbus(int device_id,int pin, PinValue value, int mode) {
	uint16_t result16;
	uint8_t result8;
	PinValue retVal;
	int errorNum;
	//Creating Modbus port
	RS485_Modbus_RTU test1(inputDevparam);
	modbus_t *ctx = test1.getDev();
	MOD8I8O ioDev1;
	ioDev1.mapModbus(test1.isModbusOpen(), ctx, 1);

	errorNum = ioDev1.setOutputPin(pin, value);// Modbus Relay SET/CLEAR Based on Actual parameter in Joystick node
	if (errorNum > 0) {
		printf("setOutputPin set success\n");
		return 1;
		} else {
		printf("setOutputPin Failure\n");
		return 0;
	}

	//printf("Pin Number:%d, Value:%d, Mode:%d",pin,value,mode);
}


