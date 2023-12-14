#include "usermain_CM4.h"

void usermain_cm4(void)
{
    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, !1);

    while(1)
    {

    }
}
