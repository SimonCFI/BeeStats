/*
 * FRAM.h
 *
 *  Created on: Jun 15, 2025
 *      Author: simon
 */

#ifndef FRAM_H_
#define FRAM_H_

#include "main.h" // für SPI_HandleTypeDef, HAL etc.
//#include "stm32f4xx_hal.h"

#define LOG_ENTRY_SIZE     8
#define FRAM_START_ADDRESS 0x0000
#define FRAM_MAX_ENTRIES   (8192 / LOG_ENTRY_SIZE) // 8KB FRAM

//Struct Definition for Sensor Data:
	#pragma pack(push, 1)
	typedef struct{
		uint8_t year;		// 1 Byte
		uint8_t month;		// 1 Byte
		uint8_t day;		// 1 Byte
		uint8_t hour;		// 1 Byte
		uint8_t minute;		// 1 Byte
		uint8_t second;		// 1 Byte
		uint16_t weight;	// 2 Byte  (5-stellig bis 65535, 10-stellig wäre uint32_t (4Byte))
}SensorData;
#pragma pack(pop)

void FRAM_WriteEnable(void);
void FRAM_WriteStruct(uint16_t address, SensorData *data);
void FRAM_ReadStruct(uint16_t address, SensorData *data);
void FRAM_WriteEntry(uint16_t index, SensorData *data);
void FRAM_ReadEntry(uint16_t index, SensorData *data);

//void FRAM_WriteByte(uint16_t addr, uint8_t data);
//uint8_t FRAM_ReadByte(uint16_t addr);
//void FRAM_LogEntry(uint32_t timestamp, float value);
//uint8_t FRAM_ReadEntry(uint16_t index, uint32_t* timestamp, float* value);
//void FRAM_Clear(void);

#endif /* FRAM_H_ */
