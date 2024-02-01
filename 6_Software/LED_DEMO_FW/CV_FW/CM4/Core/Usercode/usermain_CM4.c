#include "usermain_CM4.h"

void usermain_cm4(void)
{
    //Turn on blue LED on DevBoard, to indicate that CM4 has booted.
    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, !1);

    while(1)
    {

    }
}
