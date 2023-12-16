#ifndef USERCODE_CVLIB_H_
#define USERCODE_CVLIB_H_

#include "main.h"


typedef enum
{
    CV_VRange_1__4_9V = 1,
    CV_VRange_2__10_35V = 2
} CV_VRange_Enum;

typedef enum
{
    CV_ARange_1__0_330A = 1,
    CV_ARange_2__1_32A = 2
} CV_ARange_Enum;


const double CV_VRange_Factor[3]; //index: CV_VRange_Enum
const double CV_ARange_Factor[3]; //index: CV_ARange_Enum

#define CV_VThreshold_R12 3.6
#define CV_VThreshold_R21 3.4
#define CV_AThreshold_R12 0.24
#define CV_AThreshold_R21 0.26

#define CV_V_OL 8
#define CV_A_OL 1

int dummy;

#define ADD_DELAY dummy++
#define CV_LED_SEND_0 LED_D_GPIO_Port->ODR|=LED_D_Pin; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; LED_D_GPIO_Port->ODR&=(~LED_D_Pin); ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY
#define CV_LED_SEND_1 LED_D_GPIO_Port->ODR|=LED_D_Pin; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; LED_D_GPIO_Port->ODR&=(~LED_D_Pin); ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY; ADD_DELAY

HAL_StatusTypeDef CV_VRange_Set(CV_VRange_Enum range);
HAL_StatusTypeDef CV_ARange_Set(CV_ARange_Enum range);

void CV_Buz_BeepBlocking(uint32_t millis);

double CV_VMeas_RawBlocking();
double CV_AMeas_RawBlocking();

void CV_LED_SendByte(uint8_t byte);

void CV_LED_SendRGB(uint32_t color);

void CV_LED_SendBuf();

uint32_t CV_LED_BUF[5];

#define CV_COLOR_RED   0x100000
#define CV_COLOR_GREEN 0x000A00
#define CV_COLOR_BLACK 0x000000

#endif /* USERCODE_CVLIB_H_ */
