#include "icm-20600_spi.h"

struct ICM20600 imu;

void ICM20600_Init(SPI_HandleTypeDef* spi, GPIO_TypeDef* cs_port, uint16_t cs_pin){
  imu.hspi = spi;
  imu.cs_port = cs_port;
  imu.cs_pin = cs_pin;
}

void ICM20600_writeByte(uint8_t addr, uint8_t data){
  uint8_t txData[2];
  txData[0] = addr;
  txData[1] = data;
//  txData[2] = 0;
//  txData[3] = 0;
//  txData[4] = data;
  
  
//  HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_RESET);  
  HAL_SPI_Transmit(imu.hspi, txData, 1, 1000);
  HAL_SPI_Transmit(imu.hspi, txData + 1, 1, 1000);
//  HAL_SPI_Transmit(imu.hspi, txData + 2, 1, 1000);
//  HAL_SPI_Transmit(imu.hspi, txData + 3, 1, 1000);
//  HAL_SPI_Transmit(imu.hspi, txData + 4, 1, 1000);
//  HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_SET);  
}

uint8_t ICM20600_readByte(uint8_t addr){
  uint8_t txData[2];
  uint8_t rxData[2];
  
  txData[0] = addr | 0x80;
  txData[1] = 0x00;
  
  //HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(imu.hspi, txData, rxData, 2, 1000);
  //HAL_GPIO_WritePin(imu.cs_port, imu.cs_pin, GPIO_PIN_RESET);  

  return rxData[1];
}