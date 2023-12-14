#include "usermain_CM7.h"

void usermain_cm7(void)
{
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, !1);

    uint8_t uartBuf[20] = "";
    float voltage = 9;
    float current = .05;

    while(1)
    {
        sprintf((char *)uartBuf, "%03.1fV\t%04.2fA\t%05.2fW", voltage, current, voltage*current);

        HAL_UART_Transmit(&huart1, uartBuf, strlen((char *)uartBuf), HAL_MAX_DELAY);

        HAL_Delay(500);
    }
}
