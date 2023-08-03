/*
 * mod8i8o.cpp
 *
 *  Created on: 19-Oct-2021
 *      Author: nataraj
 */

#include "mod8i8o.h"

MOD8I8O::MOD8I8O() {
	portState = false;
	ctx = NULL;
	slave = 0;
}

void MOD8I8O::mapModbus(bool mPortState, modbus_t *mCtx, int mSlave) {
	portState = mPortState;
	ctx = mCtx;
	slave = mSlave;
}

int MOD8I8O::getHardwareVer(uint16_t *retVal) {
	uint16_t dest[2];
	if(!portState)
		return 0;
	modbus_set_slave(ctx, slave);
	int num = modbus_read_registers(ctx, (int)MOD8I8O_VER_TYPE, 1, dest);
	*retVal = dest[0];
	return num;
}

int MOD8I8O::readInputPort(uint8_t *retVal) {
	uint16_t dest[2];
	if(!portState)
		return 0;
	modbus_set_slave(ctx, slave);
	int num = modbus_read_registers(ctx, (int)MOD8I8O_READ_INPUTS, 1, dest);
	*retVal = (uint8_t)(dest[0] & 0xFF);
	return num;
}

int MOD8I8O::readInputPin(int pin, PinValue *retVal) {
	uint8_t dest[2];
	if(!portState)
		return 0;
	modbus_set_slave(ctx, slave);
	int num = modbus_read_input_bits(ctx, (int)pin, 1, dest);
	*retVal = (dest[0]==0) ? PIN_CLR : PIN_SET;
	return num;
}

int MOD8I8O::setOutputPort(uint8_t value) {
	if(!portState)
		return 0;
	modbus_set_slave(ctx, slave);
	int num = modbus_write_register(ctx, (int)MOD8I8O_W_R_OUTPUT, value);
	return num;
}

int MOD8I8O::readOutputPort(uint8_t *retVal) {
	uint16_t dest[2];
	if(!portState)
		return 0;
	modbus_set_slave(ctx, slave);
	int num = modbus_read_input_registers(ctx, (int)MOD8I8O_W_R_OUTPUT, 1, dest);
	*retVal = (uint8_t)(dest[0] & 0xFF);
	return num;
}


int MOD8I8O::setOutputPin(int pin, PinValue value) {
	if(!portState)
		return 0;
	modbus_set_slave(ctx, slave);
	int num = modbus_write_bit(ctx, (int)pin, (int)value);
	return num;
}

int MOD8I8O::setOutputPins(int pinPairAdd, PinValue val1, PinValue val2){
	const uint8_t valBuff[3] = {(uint8_t)val1,(uint8_t)val2,0};
	if(!portState)
		return 0;
	modbus_set_slave(ctx, slave);
	int num = modbus_write_bits(ctx, (int)pinPairAdd, 2, valBuff);
	return num;
}

int MOD8I8O::readOutputPin(int pin, PinValue *retVal) {
	uint8_t dest[2];
	if(!portState)
		return 0;
	modbus_set_slave(ctx, slave);
	int num = modbus_read_bits(ctx, (int)pin, 1, dest);
	*retVal = (dest[0]==0) ? PIN_CLR:PIN_SET;
	return num;
}

MOD8I8O::~MOD8I8O() {
	// TODO Auto-generated destructor stub
}

