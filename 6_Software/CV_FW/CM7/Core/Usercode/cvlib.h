#ifndef USERCODE_CVLIB_H_
#define USERCODE_CVLIB_H_

#include "main.h"



typedef enum
{
	CV_VRange_1__4_9V = 1,
	CV_VRange_2__10_35V = 2
} CV_VRange_TypeDef;

typedef enum
{
	CV_ARange_1__0_330A = 1,
	CV_ARange_2__1_32A = 2
} CV_ARange_TypeDef;



HAL_StatusTypeDef CV_VRange_Set(CV_VRange_TypeDef range);
HAL_StatusTypeDef CV_ARange_Set(CV_ARange_TypeDef range);



#endif /* USERCODE_CVLIB_H_ */
