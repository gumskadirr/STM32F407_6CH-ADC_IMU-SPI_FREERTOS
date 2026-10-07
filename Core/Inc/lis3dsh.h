#ifndef INC_LIS3DSH_H_
#define INC_LIS3DSH_H_

#include "main.h"

#define LIS3DSH_WHO_AM_I         0X0F
#define LIS3DSH_CTRL_REG1        0X21
#define LIS3DSH_CTRL_REG2        0X22
#define LIS3DSH_CTRL_REG3        0X23
#define LIS3DSH_CTRL_REG4        0X20
#define LIS3DSH_STATUS_REG       0X27
#define LIS3DSH_OUT_X_L          0X28
#define LIS3DSH_OUT_X_H          0X29
#define LIS3DSH_OUT_Y_L          0X2A
#define LIS3DSH_OUT_Y_H          0X2B
#define LIS3DSH_OUT_Z_L          0X2C
#define LIS3DSH_OUT_Z_H          0X2D
#define LIS3DSH_READ             0X80
#define LIS3DSH_WRITE            0X00
#define LIS3DSH_CS_HIGH          HAL_GPIO_WritePin(GPIOE, CS_Pin, GPIO_PIN_SET);
#define LIS3DSH_CS_LOW           HAL_GPIO_WritePin(GPIOE, CS_Pin, GPIO_PIN_RESET);

#define LIS3DSH_POWERDOWN				0X00
#define LIS3DSH_3HZ						0X01
#define LIS3DSH_6HZ						0X02
#define LIS3DSH_12HZ					0X03
#define LIS3DSH_25HZ					0X04
#define LIS3DSH_50HZ					0X05
#define LIS3DSH_100HZ					0X06
#define LIS3DSH_400HZ					0X07
#define LIS3DSH_800HZ					0X08
#define LIS3DSH_1600HZ					0X09
#define LIS3DSH_BDU_CONT_UPDATE			0X00
#define LIS3DSH_BDU_MSB_LSB				0X01
#define LIS3DSH_ZEN_EN					0X01
#define LIS3DSH_ZEN_DS					0X00
#define LIS3DSH_YEN_EN					0X01
#define LIS3DSH_YEN_DS					0X00
#define LIS3DSH_XEN_EN					0X01
#define LIS3DSH_XEN_DS					0X00
#define LIS3DSH_SENSITIVITY 			0.001

typedef enum{
	INIT_FAIL = 0,
	INIT_SUCCESS = 1,
}LIS3DSHInitStatus;


LIS3DSHInitStatus LIS3DSH_Init(SPI_HandleTypeDef *hspi);

uint8_t LIS3DSH_ReadWhoAmI(SPI_HandleTypeDef *hspi);

typedef struct{
    int16_t x;
    int16_t y;
    int16_t z;
}LIS3DSH_AccelData_t;

LIS3DSH_AccelData_t LIS3DSH_ReadAccel(SPI_HandleTypeDef *hspi);



HAL_StatusTypeDef LIS3DSH_ReadRegister(SPI_HandleTypeDef *hspi, uint8_t regAddress, uint8_t *data, uint16_t size);
HAL_StatusTypeDef LIS3DSH_WriteRegister(SPI_HandleTypeDef *hspi, uint8_t regAddress, uint8_t data);




typedef struct
{
    uint8_t whoAmI;
    uint8_t ctrlReg3;
    uint8_t ctrlReg4;
    uint32_t drdyCount;
    uint32_t dmaCompleteCount;
    uint32_t sampleCount;
    uint32_t dmaStartErrors;
    uint32_t dmaTransferErrors;
    uint32_t flagErrors;
    uint32_t rtosErrors;
    uint32_t dmaTimeouts;
    /* Izleme gorevi yaklasik saniyede bir gunceller. */
    float drdyRateHz;
    float dmaRateHz;
    float sampleRateHz;
    uint32_t rateWindowMs;
} SensorDebug_t;

typedef struct
{
    uint32_t tickMs;
    uint32_t drdy;
    uint32_t dma;
    uint32_t samples;
} SensorCounterSnapshot_t;

#define LIS3DSH_DMA_FRAME_SIZE  7U
#define SENSOR_FLAG_DRDY       (1UL << 0)
#define SENSOR_FLAG_DMA_DONE   (1UL << 1)
#define SENSOR_FLAG_DMA_ERROR  (1UL << 2)
#define SENSOR_FLAGS_DMA       (SENSOR_FLAG_DMA_DONE | SENSOR_FLAG_DMA_ERROR)




#endif /* INC_LIS3DSH_H_ */
