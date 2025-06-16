/*
 * FRAM.c
 *
 *  Created on: Jun 15, 2025
 *      Author: simon
 */

#include "main.h"
#include "FRAM.h"
#include "stdio.h"

extern SPI_HandleTypeDef hspi1;

#define FRAM_CS_LOW()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define FRAM_CS_HIGH()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

static uint16_t nextEntry = 0;

void FRAM_WriteEnable(void) {
    uint8_t cmd = 0x06; // WREN
    FRAM_CS_LOW();
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    FRAM_CS_HIGH();
}

void FRAM_WriteBytes(uint16_t addr, uint8_t* data, uint16_t len) {
    FRAM_WriteEnable();
    uint8_t cmd[3] = {0x02, addr >> 8, addr & 0xFF};
    FRAM_CS_LOW();
    HAL_SPI_Transmit(&hspi1, cmd, 3, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, data, len, HAL_MAX_DELAY);
    FRAM_CS_HIGH();
}

void FRAM_ReadBytes(uint16_t addr, uint8_t* buffer, uint16_t length) {
    uint8_t cmd[3] = {0x03, addr >> 8, addr & 0xFF};
    FRAM_CS_LOW();
    HAL_SPI_Transmit(&hspi1, cmd, 3, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi1, buffer, length, HAL_MAX_DELAY);
    FRAM_CS_HIGH();
}

void FRAM_LogEntry(uint32_t timestamp, float value) {
    if (nextEntry >= FRAM_MAX_ENTRIES)
        return; // optional: Ringpuffer oder stoppen

    uint8_t buffer[LOG_ENTRY_SIZE];
    buffer[0] = (timestamp >> 24) & 0xFF;
    buffer[1] = (timestamp >> 16) & 0xFF;
    buffer[2] = (timestamp >> 8) & 0xFF;
    buffer[3] = timestamp & 0xFF;

    uint8_t* val = (uint8_t*)&value;
    buffer[4] = val[0];
    buffer[5] = val[1];
    buffer[6] = val[2];
    buffer[7] = val[3];

    uint16_t addr = FRAM_START_ADDRESS + nextEntry * LOG_ENTRY_SIZE;
    FRAM_WriteBytes(addr, buffer, LOG_ENTRY_SIZE);
    nextEntry++;
}

uint8_t FRAM_ReadEntry(uint16_t index, uint32_t* timestamp, float* value) {
    if (index >= nextEntry)
        return 0;

    uint8_t buffer[LOG_ENTRY_SIZE];
    uint16_t addr = FRAM_START_ADDRESS + index * LOG_ENTRY_SIZE;
    FRAM_ReadBytes(addr, buffer, LOG_ENTRY_SIZE);

    *timestamp = (buffer[0] << 24) | (buffer[1] << 16) |
                 (buffer[2] << 8) | buffer[3];

    uint8_t* val = (uint8_t*)value;
    val[0] = buffer[4];
    val[1] = buffer[5];
    val[2] = buffer[6];
    val[3] = buffer[7];

    // Ausgabe
    printf("Eintrag %u: Zeitstempel: %lu, Lichtstärke: %.2f Lux\r\n", index, *timestamp, *value);

    return 1;
}

void FRAM_Clear(void) {
    nextEntry = 0;
}


