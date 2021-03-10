#ifndef __ESP8266_SPI_H__
#define __ESP8266_SPI_H__

#include "stm32f4xx_hal.h"

struct ESP8266{
  SPI_HandleTypeDef *hspi;
  
  // Hardware pin
  GPIO_TypeDef *cs_port;
  uint16_t cs_pin;
};

extern struct ESP8266 imu;

extern void ESP8266_Init(SPI_HandleTypeDef* spi, GPIO_TypeDef* cs_port, uint16_t cs_pin);
extern uint32_t ESP8266_ReadStatus();
extern void ESP8266_WriteStatus(uint32_t status);
extern void ESP8266_ReadData(uint8_t *pRxData);
extern void ESP8266_WriteData(uint8_t *pTxData, uint32_t len);
#endif