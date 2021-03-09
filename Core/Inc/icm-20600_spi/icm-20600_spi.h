#ifndef __ICM_20600_SPI_H__
#define __ICM_20600_SPI_H__

#include "stm32f4xx_hal.h"

struct ICM20600{
  SPI_HandleTypeDef *hspi;
  
  // Hardware pin
  GPIO_TypeDef *cs_port;
  uint16_t cs_pin;
};

extern struct ICM20600 imu;

extern void ICM20600_Init(SPI_HandleTypeDef* spi, GPIO_TypeDef* cs_port, uint16_t cs_pin);
extern void ICM20600_writeByte(uint8_t addr, uint8_t data);
extern uint8_t ICM20600_readByte(uint8_t addr);
#endif