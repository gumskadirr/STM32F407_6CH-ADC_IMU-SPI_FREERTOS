#include "lis3dsh.h"

LIS3DSHInitStatus LIS3DSH_Init(SPI_HandleTypeDef *hspi)
{
    uint8_t ctrlReg4Value;

    ctrlReg4Value =
            (LIS3DSH_1600HZ        << 4) |
            (LIS3DSH_BDU_MSB_LSB  << 3) |
            (LIS3DSH_ZEN_EN       << 2) |
            (LIS3DSH_YEN_EN       << 1) |
            (LIS3DSH_XEN_EN       << 0);

    if (LIS3DSH_WriteRegister(
            hspi,
            LIS3DSH_CTRL_REG4,
            ctrlReg4Value) != HAL_OK)
    {
        return INIT_FAIL;
    }

    return INIT_SUCCESS;
}


HAL_StatusTypeDef LIS3DSH_ReadRegister(SPI_HandleTypeDef *hspi, uint8_t regAddress, uint8_t *data, uint16_t size)
{
    regAddress |= LIS3DSH_READ;

    LIS3DSH_CS_LOW;

    HAL_StatusTypeDef status = HAL_SPI_Transmit(hspi, &regAddress, 1, HAL_MAX_DELAY);

    if (status == HAL_OK)
    {
        status = HAL_SPI_Receive(hspi, data, size, HAL_MAX_DELAY);
    }

    LIS3DSH_CS_HIGH;

    return status;
}

HAL_StatusTypeDef LIS3DSH_WriteRegister(SPI_HandleTypeDef *hspi, uint8_t regAddress, uint8_t data)
{
    regAddress |= LIS3DSH_WRITE;

    LIS3DSH_CS_LOW;

    HAL_StatusTypeDef status = HAL_SPI_Transmit(hspi, &regAddress, 1, HAL_MAX_DELAY);

    if (status == HAL_OK)
    {
        status = HAL_SPI_Transmit(hspi, &data, 1, HAL_MAX_DELAY);
    }

    LIS3DSH_CS_HIGH;

    return status;
}




uint8_t LIS3DSH_ReadWhoAmI(SPI_HandleTypeDef *hspi)
{
    uint8_t whoAmI = 0;

    LIS3DSH_ReadRegister(hspi, LIS3DSH_WHO_AM_I, &whoAmI, 1);

    return whoAmI;
}



LIS3DSH_AccelData_t LIS3DSH_ReadAccel(SPI_HandleTypeDef *hspi)
{
    uint8_t rawData[6] = {0};
    LIS3DSH_AccelData_t accelData = {0};

    LIS3DSH_ReadRegister(hspi, LIS3DSH_OUT_X_L, rawData, 6);

    accelData.x = ((int16_t)(((uint16_t)rawData[1] << 8) | rawData[0]))*LIS3DSH_SENSITIVITY;
    accelData.y = ((int16_t)(((uint16_t)rawData[3] << 8) | rawData[2]))*LIS3DSH_SENSITIVITY;
    accelData.z = ((int16_t)(((uint16_t)rawData[5] << 8) | rawData[4]))*LIS3DSH_SENSITIVITY;

    return accelData;
}

/*
int16_t LIS3DSH_ReadAccel(SPI_HandleTypeDef *hspi)
{
    uint8_t rawData[10] = {0};
    uint8_t regAddressX = LIS3DSH_OUT_X_L | LIS3DSH_READ;
    uint8_t regAddressY = LIS3DSH_OUT_Y_L | LIS3DSH_READ;
    uint8_t regAddressZ = LIS3DSH_OUT_Z_L | LIS3DSH_READ;

    LIS3DSH_CS_LOW;

    HAL_SPI_Transmit(hspi,&regAddressX,1,HAL_MAX_DELAY);
    HAL_SPI_Receive(hspi,rawData,2,HAL_MAX_DELAY);

    HAL_SPI_Transmit(hspi,&regAddressY,1,HAL_MAX_DELAY);
    HAL_SPI_Receive(hspi,rawData,2,HAL_MAX_DELAY);

    HAL_SPI_Transmit(hspi,&regAddressZ,1,HAL_MAX_DELAY);
    HAL_SPI_Receive(hspi,rawData,2,HAL_MAX_DELAY);

    LIS3DSH_CS_HIGH;

    int16_t accelX = (int16_t)( ( (uint16_t)rawData[1] << 8) | (uint16_t)rawData[0] );

    return accelX;
}*/

/*
int16_t LIS3DSH_ReadAccel(SPI_HandleTypeDef *hspi){

	uint8_t tempReg = 0;
	uint8_t regAdress = LIS3DSH_OUT_X_L | LIS3DSH_READ ;

	LIS3DSH_CS_LOW;
	HAL_SPI_Transmit(hspi, &regAdress, 1, HAL_MAX_DELAY);
	HAL_SPI_Receive(hspi, accelData, 2, HAL_MAX_DELAY);
	LIS3DSH_CS_HIGH;
}*/
