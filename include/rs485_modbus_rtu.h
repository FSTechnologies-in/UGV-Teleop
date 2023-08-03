/*
 * rs485_modbus_rtu.h
 *
 *  Created on: 15-Sep-2021
 *      Author: nataraj
 */

#ifndef RS485_MODBUS_RTU_H_
#define RS485_MODBUS_RTU_H_

#include <stdio.h>
#include <modbus.h>
#include <iostream>
#include <string>


//0x01 (read coil status) - modbus_read_bits(modbus_t *ctx, int addr, int nb, uint8_t *dest);
//0x02 (read input status) - modbus_read_input_bits(modbus_t *ctx, int addr, int nb, uint8_t *dest);
//0x03 (read holding registers)- modbus_read_registers(modbus_t *ctx, int addr, int nb, uint16_t *dest);
//0x04 (read input registers) - modbus_read_input_registers(modbus_t *ctx, int addr, int nb, uint16_t *dest);
//0x05 (force single coil) - modbus_write_bit(modbus_t *ctx, int coil_addr, int status);
//0x06 (preset single register) - modbus_write_register(modbus_t *ctx, int reg_addr, int value);
//0x0F (force multiple coils) - modbus_write_bits(modbus_t *ctx, int addr, int nb, const uint8_t *data);
//0x10 (preset multiple registers) - modbus_write_registers(modbus_t *ctx, int addr, int nb, const uint16_t *data);
//0x17 (write/read registers) - modbus_write_and_read_registers(modbus_t *ctx, int write_addr, int write_nb, const uint16_t *src, int read_addr, int read_nb, uint16_t *dest);


typedef struct{
	unsigned char addr;
	char *port;
	int baud;
	char parity;
	int dataBit;
	int stopBit;
}RS485_Param;


#define TEST_DEV_ADDR 		0x01
const RS485_Param testDevParam = { TEST_DEV_ADDR, (char*)"/dev/ttyUSB0",9600,'N',8,1 };
const RS485_Param inputDevparam = { TEST_DEV_ADDR, (char*)"/dev/ttyUSB0",9600,'N',8,1 };

class RS485_Modbus_RTU {
private:
	modbus_t *ctx;
	std::string exceptions="";
	bool isPortOpen = false;

public:
	RS485_Modbus_RTU(RS485_Param mDev);
	~RS485_Modbus_RTU();

	std::string getLibModbusVersion();
	modbus_t *getDev();
	bool isModbusOpen();
};

#endif /* RS485_MODBUS_RTU_H_ */
