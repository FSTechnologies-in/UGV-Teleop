/*
 * rs485_modbus_rtu.cpp
 *
 *  Created on: 15-Sep-2021
 *      Author: nataraj
 */

#include <rs485_modbus_rtu.h>

RS485_Modbus_RTU::RS485_Modbus_RTU(RS485_Param mDev) {
	//Create a new RTU context with proper serial parameters (in this example,
	ctx = modbus_new_rtu(mDev.port, mDev.baud, mDev.parity, mDev.dataBit, mDev.stopBit);

	if (!ctx) {
		std::cout << "Failed to create the context: " + std::string(modbus_strerror(-1)) + "\n";
		isPortOpen = false;
		return;
	}

	if (modbus_connect(ctx) == -1) {
		std::cout << "Unable to connect: " + std::string(modbus_strerror(-1)) + "\n";
		modbus_free(ctx);
		isPortOpen = false;
		return;
	}
	isPortOpen = true;
}



modbus_t *RS485_Modbus_RTU::getDev(){
	return this->ctx;
}

std::string getLibModbusVersion(){
	return "Compiled with \"libmodbus\" version" + std::string(LIBMODBUS_VERSION_STRING);
}

bool RS485_Modbus_RTU::isModbusOpen(){
	return this->isPortOpen;
}

RS485_Modbus_RTU::~RS485_Modbus_RTU() {
	modbus_close(ctx);
	modbus_free(ctx);
}



