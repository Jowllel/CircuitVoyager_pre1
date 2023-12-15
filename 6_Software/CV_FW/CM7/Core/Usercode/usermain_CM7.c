#include "usermain_CM7.h"

void usermain_cm7(void)
{
    //init local variables
    uint8_t uartBuf[50] = "";

    double voltage = (double)0;
    double current = (double)0;

    CV_VRange_Enum VRange = CV_VRange_1__4_9V;
    CV_ARange_Enum ARange = CV_ARange_1__0_330A;


    //Turn on green LED on DevBoard, to indicate that CM7 has booted.
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, !1);

    //Beep for 250ms at startup
    CV_Buz_BeepBlocking(250);

    //Start in voltage range 1 (O.L. at 4.9V)
    CV_VRange_Set(VRange);

    //Start in current range 1 (O.L. at 330mA)
    CV_ARange_Set(ARange);


    //main loop
    while(1)
    {
        //get voltage reading from adc1 (V_MEAS pin)
        voltage = CV_VMeas_RawBlocking() * CV_VRange_Factor[VRange];

        if((VRange == CV_VRange_1__4_9V) && (voltage > CV_VThreshold_R12))
        {
            VRange = CV_VRange_2__10_35V;
            CV_VRange_Set(VRange);
            voltage = CV_VMeas_RawBlocking() * CV_VRange_Factor[VRange];
        }
        else if((VRange == CV_VRange_2__10_35V) && (voltage < CV_VThreshold_R21))
        {
            VRange = CV_VRange_1__4_9V;
            CV_VRange_Set(VRange);
            voltage = CV_VMeas_RawBlocking() * CV_VRange_Factor[VRange];
        }


        //get current reading from adc3 (A_MEAS pin)
        current = CV_AMeas_RawBlocking() * CV_ARange_Factor[ARange];

        if((ARange == CV_ARange_1__0_330A) && (current > CV_AThreshold_R12))
        {
            ARange = CV_ARange_2__1_32A;
            CV_ARange_Set(ARange);
            current = CV_AMeas_RawBlocking() * CV_ARange_Factor[ARange];
        }
        else if((ARange == CV_ARange_2__1_32A) && (current < CV_AThreshold_R21))
        {
            ARange = CV_ARange_1__0_330A;
            CV_ARange_Set(ARange);
            current = CV_AMeas_RawBlocking() * CV_ARange_Factor[ARange];
        }


        //format output buffer with voltage, current and power reading.
        sprintf((char *)uartBuf, "%03.1fV\t%04.2fA\t%05.2fW\tVR:%d\tAR:%d", voltage, current, voltage * current, VRange, ARange);

        //Output buffer over UART 1. (ST-Link UART)
        HAL_UART_Transmit(&huart1, uartBuf, strlen((char *)uartBuf), HAL_MAX_DELAY);


        //wait 250ms (aprox. 4Hz cycle frequency)
        HAL_Delay(250);
    }
}
