#include "usermain_CM7.h"

void usermain_cm7(void)
{


    //Turn on green LED on DevBoard, to indicate that CM7 has booted.
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, !1);

    //Beep for 250ms at startup
    HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, 1);
    HAL_Delay(250);
    HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, 0);

    //Start in voltage range 1 (O.L. at 4.9V)
    CV_VRange_Set(CV_VRange_1__4_9V);

    //Start in current range 1 (O.L. at 330mA)
    CV_ARange_Set(CV_ARange_1__0_330A);




    //init local variables
    uint8_t uartBuf[20] = "";
    float voltage = (float)0;
    float current = (float)0;


    //main loop
    while(1)
    {
        //get voltage reading from adc1 (V_MEAS pin)
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        voltage = HAL_ADC_GetValue(&hadc1) * 3.3 * 1.47 / 65536;

        //get current reading from adc3 (A_MEAS pin)
        HAL_ADC_Start(&hadc3);
        HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY);
        current = HAL_ADC_GetValue(&hadc3) * 3.3 / 10 / 65536;

        //format output buffer with voltage, current and power reading.
        sprintf((char *)uartBuf, "%03.1fV\t%04.2fA\t%05.2fW", voltage, current, voltage * current);

        //Output buffer over UART 1. (ST-Link UART)
        HAL_UART_Transmit(&huart1, uartBuf, strlen((char *)uartBuf), HAL_MAX_DELAY);


        //wait 500ms (aprox. 2Hz cycle frequency)
        HAL_Delay(500);
    }
}
