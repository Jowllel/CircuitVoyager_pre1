#include "usermain_CM7.h"

uint8_t* msgOut = (uint8_t*)"1234567890";

void usermain_cm7(void)
{
    if(CSP_QUADSPI_Init() != HAL_OK)
    {
        Error_Handler();
    }

    if(CSP_QSPI_Erase_Chip() != HAL_OK)
    {
        Error_Handler();
    }

    if(CSP_QSPI_WriteMemory((uint8_t*)msgOut, 0, strlen((char*)msgOut)) != HAL_OK)
    {
        Error_Handler();
    }

    while(1)
    {
        HAL_GPIO_TogglePin(LED_O_GPIO_Port, LED_O_Pin);
        HAL_Delay(500);
    }
}
