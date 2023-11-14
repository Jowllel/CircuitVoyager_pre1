#include "usermain_CM7.h"

void usermain_cm7(void)
{

    while(1)
    {
        HAL_GPIO_TogglePin(LED_O_GPIO_Port, LED_O_Pin);
        HAL_Delay(500);
    }
}
