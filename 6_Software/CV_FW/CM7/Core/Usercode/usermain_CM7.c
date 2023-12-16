#include "usermain_CM7.h"

void usermain_cm7(void)
{
    //init local variables
    uint8_t uartBuf[50] = "";
    uint8_t uartInBuf[1] = "";

    uint8_t VMsg[7] = "";
    uint8_t AMsg[7] = "";
    uint8_t WMsg[8] = "";

    double voltage = (double)0;
    double current = (double)0;

    uint8_t noMsgCnt = 5;
    uint8_t connected = 0;

    uint32_t colorConnectionState = CV_COLOR_BLACK;

    CV_VRange_Enum VRange = CV_VRange_1__4_9V;
    CV_ARange_Enum ARange = CV_ARange_1__0_330A;

    //Set LED Ring to red
    for(int i = 0; i < 5; i++)
    {
        CV_LED_BUF[i] = colorConnectionState;
    }
    CV_LED_SendBuf();

    //Turn on green LED on DevBoard, to indicate that CM7 has booted.
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, !1);

    //Start in voltage range 1 (O.L. at 4.9V)
    CV_VRange_Set(VRange);

    //Start in current range 1 (O.L. at 330mA)
    CV_ARange_Set(ARange);


    //main loop
    while(1)
    {
        if((HAL_UART_Receive(&huart1, uartInBuf, 1, 100) == HAL_OK) && (uartInBuf[0] == '1')) noMsgCnt = 0;
        else if(noMsgCnt < 10)                                                                noMsgCnt++;

        if(noMsgCnt >= 2)
        {
            colorConnectionState = CV_COLOR_BLACK;
            if(connected == 1) CV_Buz_BeepBlocking(150);
            connected = 0;
        }
        else
        {
            colorConnectionState = CV_COLOR_GREEN;
            if(connected == 0)
            {
                CV_Buz_BeepBlocking(125);
                HAL_Delay(50);
                CV_Buz_BeepBlocking(125);
            }
            connected = 1;
        }



        //get voltage reading from adc1 (V_MEAS pin)
        voltage = CV_VMeas_RawBlocking() * CV_VRange_Factor[VRange];

        if((VRange == CV_VRange_1__4_9V) && (voltage > CV_VThreshold_R12))
        {
            CV_Buz_BeepBlocking(5);
            VRange = CV_VRange_2__10_35V;
            CV_VRange_Set(VRange);
            HAL_Delay(1);
            voltage = CV_VMeas_RawBlocking() * CV_VRange_Factor[VRange];
        }
        else if((VRange == CV_VRange_2__10_35V) && (voltage < CV_VThreshold_R21))
        {
            CV_Buz_BeepBlocking(5);
            VRange = CV_VRange_1__4_9V;
            CV_VRange_Set(VRange);
            HAL_Delay(1);
            voltage = CV_VMeas_RawBlocking() * CV_VRange_Factor[VRange];
        }


        //get current reading from adc3 (A_MEAS pin)
        current = CV_AMeas_RawBlocking() * CV_ARange_Factor[ARange];

        if((ARange == CV_ARange_1__0_330A) && (current > CV_AThreshold_R12))
        {
            CV_Buz_BeepBlocking(5);
            ARange = CV_ARange_2__1_32A;
            CV_ARange_Set(ARange);
            HAL_Delay(1);
            current = CV_AMeas_RawBlocking() * CV_ARange_Factor[ARange];
        }
        else if((ARange == CV_ARange_2__1_32A) && (current < CV_AThreshold_R21))
        {
            CV_Buz_BeepBlocking(5);
            ARange = CV_ARange_1__0_330A;
            CV_ARange_Set(ARange);
            HAL_Delay(1);
            current = CV_AMeas_RawBlocking() * CV_ARange_Factor[ARange];
        }


        //format output buffer with voltage, current and power reading.
        if(voltage < CV_V_OL) sprintf((char *)VMsg, "%04.2fV\t", voltage);
        else                  sprintf((char *)VMsg, "O.L.\t");

        if(current < CV_A_OL) sprintf((char *)AMsg, "%04.2fA\t", current);
        else                  sprintf((char *)AMsg, "O.L.\t");

        if((voltage < CV_V_OL) && (current < CV_A_OL))
        {
            sprintf((char *)WMsg, "%04.2fW\t", voltage * current);
            for(int i = 0; i < 5; i++)
            {
                CV_LED_BUF[i] = colorConnectionState;
            }
        }
        else
        {
            sprintf((char *)WMsg, " O.L. \t");
            for(int i = 0; i < 5; i++)
            {
                CV_LED_BUF[i] = CV_COLOR_RED;
            }
        }

        sprintf((char *)uartBuf, "%s%s%sVR:%d\tAR:%d\n", VMsg, AMsg, WMsg, VRange, ARange);

        //Output buffer over UART 1. (ST-Link UART)
        HAL_UART_Transmit(&huart1, uartBuf, strlen((char *)uartBuf), HAL_MAX_DELAY);

        //Update LEDs
        CV_LED_SendBuf();

        //wait 250ms (aprox. 4Hz cycle frequency)
        HAL_Delay(250);
    }
}
