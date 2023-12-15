#include "cvlib.h"


HAL_StatusTypeDef CV_VRange_Set(CV_VRange_TypeDef range)
{
    switch(range)
    {
    case CV_VRange_1__4_9V:
        HAL_GPIO_WritePin(V_R2_EN_GPIO_Port, V_R2_EN_Pin, 0);
        HAL_GPIO_WritePin(V_R1_EN_GPIO_Port, V_R1_EN_Pin, 1);
        return HAL_OK;
    case CV_VRange_2__10_35V:
        HAL_GPIO_WritePin(V_R1_EN_GPIO_Port, V_R1_EN_Pin, 0);
        HAL_GPIO_WritePin(V_R2_EN_GPIO_Port, V_R2_EN_Pin, 1);
        return HAL_OK;
    default:
        return HAL_ERROR;
    }
}


HAL_StatusTypeDef CV_ARange_Set(CV_ARange_TypeDef range)
{
    switch(range)
    {
    case CV_ARange_1__0_330A:
        HAL_GPIO_WritePin(A_RSEL_GPIO_Port, A_RSEL_Pin, 0);
        return HAL_OK;
    case CV_ARange_2__1_32A:
        HAL_GPIO_WritePin(A_RSEL_GPIO_Port, A_RSEL_Pin, 1);
        return HAL_OK;
    default:
        return HAL_ERROR;
    }
}

void CV_Buz_BeepBlocking(uint32_t millis)
{
    HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, 1);
    HAL_Delay(millis);
    HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, 0);
}


