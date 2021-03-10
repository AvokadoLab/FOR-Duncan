#include "esp8266_spi.h"

struct ESP8266 imu;

void ESP8266_Init(SPI_HandleTypeDef* spi, GPIO_TypeDef* cs_port, uint16_t cs_pin){
  imu.hspi = spi;
  imu.cs_port = cs_port;
  imu.cs_pin = cs_pin;
}
// https://github.com/esp8266/Arduino/blob/master/libraries/SPISlave/examples/SPISlave_Master/SPISlave_Master.ino
// https://github.com/esp8266/Arduino/blob/master/libraries/SPISlave/examples/SPISlave_SafeMaster/SPISlave_SafeMaster.ino

uint32_t ESP8266_ReadStatus(){
  uint8_t command = 0x04;
  uint8_t rxData[4];
  
  HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(imu.hspi, &command, 1, 100);
  HAL_SPI_Receive(imu.hspi, rxData, 4, 100);
  HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_SET);  
  return (uint32_t)rxData[0] | (uint32_t)(rxData[1] << 8) | (uint32_t)(rxData[2] << 16) | (uint32_t)(rxData[3] << 24);
}

void ESP8266_WriteStatus(uint32_t status){
  uint8_t command = 0x01;
  uint8_t txData[4];
  txData[0] = status & 0xFF;
  txData[1] = (status >> 8) & 0xFF;
  txData[2] = (status >> 16) & 0xFF;
  txData[3] = (status >> 24) & 0xFF;
  
  HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_RESET);  
  HAL_SPI_Transmit(imu.hspi, &command, 1, 100);
  HAL_SPI_Transmit(imu.hspi, txData, 4, 100);
  HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_SET);  
}

void ESP8266_ReadData(uint8_t *pRxData){
  uint8_t command = 0x03;
  uint8_t addr = 0x00;
  
  HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(imu.hspi, &command, 1, 100); 
  HAL_SPI_Transmit(imu.hspi, &addr, 1, 100);
  HAL_SPI_Receive(imu.hspi, pRxData, 32, 100);
  HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_SET);  
}

void ESP8266_WriteData(uint8_t *pTxData, uint32_t len){
  uint8_t command = 0x02;
  uint8_t addr = 0x00;
  uint8_t zero = 0;
  uint8_t i = 0;
  
  HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(imu.hspi, &command, 1, 100); 
  HAL_SPI_Transmit(imu.hspi, &addr, 1, 100);
  while (len-- && i < 32) {
    HAL_SPI_Transmit(imu.hspi, pTxData + (i++), 1, 100);
  }
  while (i++ < 32) {
    HAL_SPI_Transmit(imu.hspi, &zero, 1, 100);
  }
  HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_SET);  
}