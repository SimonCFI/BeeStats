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

void FRAM_WriteEnable(void);
void FRAM_WriteByte(uint16_t addr, uint8_t data);
uint8_t FRAM_ReadByte(uint16_t addr);
void FRAM_LogEntry(uint32_t timestamp, float value);
uint8_t FRAM_ReadEntry(uint16_t index, uint32_t* timestamp, float* value);
void FRAM_Clear(void);

#endif /* FRAM_H_ */
