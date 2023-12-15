#include "cvlib.h"


const double CV_VRange_Factor[3] = {0, 1.47, 3.13636}; //index: CV_VRange_Enum
const double CV_ARange_Factor[3] = {0, 0.1, 0.4};    //index: CV_ARange_Enum


HAL_StatusTypeDef CV_VRange_Set(CV_VRange_Enum range)
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


HAL_StatusTypeDef CV_ARange_Set(CV_ARange_Enum range)
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


double CV_VMeas_RawBlocking()
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(&hadc1) * 3.3 / 65535;
}


double CV_AMeas_RawBlocking()
{
    HAL_ADC_Start(&hadc3);
    HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(&hadc3) * 3.3 / 65535;
}


