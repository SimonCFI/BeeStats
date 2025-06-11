/*
 * BH1750.c
 *
 *  Created on: Jun 9, 2025
 *      Author: simon
 */


#include "main.h"
#include "stdio.h"

extern I2C_HandleTypeDef hi2c1;
#include "BH1750.h"

uint8_t cmd = 0x10;
int16_t rawLux[2];
int16_t lux;

int16_t getBH1750_Lux (void){

	HAL_I2C_Master_Transmit(&hi2c1, DEV_ADR<<1, &cmd, 1, HAL_MAX_DELAY);
	HAL_Delay(150);
	HAL_I2C_Master_Receive(&hi2c1, 0x23<<1, rawLux, 2, HAL_MAX_DELAY);

	lux=(rawLux[0] << 8) | rawLux[1];

	return lux;
}
