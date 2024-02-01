#include "usermain_CM7.h"

void usermain_cm7(void)
{
     //Turn on green LED on DevBoard, to indicate that CM7 has booted.
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, !1);


    //main loop (generated using MS Copilot)
    while(1)
    {
        for(int i = 0; i < 5; i++)
        {
            int red = (i * 51 + HAL_GetTick() / 10) % 256;
            int blue = 255 - red;
            CV_LED_BUF[i] = (red << 16) | (0 << 8) | blue;
        }

        //Update LEDs
        CV_LED_SendBuf();

        //wait 250ms (aprox. 4Hz cycle frequency)
        HAL_Delay(250);
    }
}
