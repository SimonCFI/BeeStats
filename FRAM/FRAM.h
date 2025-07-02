/*
 * FRAM.h
 *
 *  Created on: Jun 15, 2025
 *      Author: simon
 */

#ifndef FRAM_H_
#define FRAM_H_

#include "main.h" // für SPI_HandleTypeDef, HAL etc.
extern uint16_t FRAMindex;
#define FRAM_TOTAL_SIZE		8192  //8KB FRAM, später anpassen
#define INDEX_ADDR		(FRAM_TOTAL_SIZE - sizeof(uint16_t))
#define FRAM_START_ADDR 	0x0000
#define RECORD_SIZE         sizeof(SensorData)
#define MAX_RECORDS         ((INDEX_ADDR - FRAM_START_ADDR) / RECORD_SIZE)

#define FRAM_CS_LOW()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)  //Pin anpassen
#define FRAM_CS_HIGH()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

#define FRAM_WRITE_ENABLE  0x06
#define FRAM_WRITE         0x02
#define FRAM_READ          0x03


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
void FRAM_WriteEntry(uint16_t FRAMindex, SensorData *data);
void FRAM_ReadEntry(uint16_t FRAMindex, SensorData *data);
void FRAM_WriteIndex(uint16_t index);
uint16_t FRAM_ReadIndex(void);

//void FRAM_WriteByte(uint16_t addr, uint8_t data);
//uint8_t FRAM_ReadByte(uint16_t addr);
//void FRAM_LogEntry(uint32_t timestamp, float value);
//uint8_t FRAM_ReadEntry(uint16_t index, uint32_t* timestamp, float* value);
//void FRAM_Clear(void);

#endif /* FRAM_H_ */
