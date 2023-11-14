#include "usermain_CM4.h"

void usermain_cm4(void)
{

    while(1)
    {
        HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
        HAL_Delay(500);
    }
}
