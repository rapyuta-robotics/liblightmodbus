#ifndef LIGHTMODBUS_BASE_H
#define LIGHTMODBUS_BASE_H

/* This is main header file that is ought to be included as library */

//Include proper header files
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

//Error codes
#define MODBUS_ERROR_OK 0 //Everything went ok
#define MODBUS_ERROR_PARSE 1 //Slave did not parse frame (eg. bad function code)
#define MODBUS_ERROR_EXCEPTION 2 //Slave thrown an exception and it's stored in status->exception
#define MODBUS_ERROR_CRC 4 //Invalid crc error
#define MODBUS_ERROR_ALLOC 8 //Memory allocation problems (eg. system ran out of RAM)
#define MODBUS_ERROR_OTHER 16 //Other reason function was exited (eg. bad function parameter)
#define MODBUS_ERROR_FRAME 32 //Frame contained incorrect data, and exception could not be thrown (eg. bytes count != reg count * 2 in slave's response)

#define MODBUS_MASTER_MAX_REQUEST_SIZE 64
#define MODBUS_MASTER_MAX_RESPONSE_SIZE 64
#define MODBUS_MASTER_MAX_DATA_COUNT 8

//Types
typedef struct
{
	uint8_t length; //Length of frame, if it's equal to 0, frame is not ready
	uint8_t *frame; //Frame content
} ModbusFrame; //Type containing information about generated frame

//Function prototypes
extern uint8_t modbusMaskRead( uint8_t *mask, uint16_t maskLength, uint16_t bit );
extern uint8_t modbusMaskWrite( uint8_t *mask, uint16_t maskLength, uint16_t bit, uint8_t value );
extern uint16_t modbusSwapEndian( uint16_t data );
extern uint16_t modbusCRC( uint8_t *data, uint16_t length );

#endif
