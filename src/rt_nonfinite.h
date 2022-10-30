/**
 * @file           : rt_nonfinite.h
 * @target         : Generic->MATLAB Host Computer
 * @details        : computional geometry algorithms
 * @author         : cuixingxing
 * @email          : cuixingxing150@gmail.com
 * @date           : 30-Oct-2022 10:57:27
 * @version        : V1.0.0
 * @copyright      : Copyright (C) 2022 cuixingxing.All rights reserved.
 */

#ifndef RT_NONFINITE_H
#define RT_NONFINITE_H

/** @include file    : Include Files */
#include "rtwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;

extern boolean_T rtIsInf(real_T value);
extern boolean_T rtIsInfF(real32_T value);
extern boolean_T rtIsNaN(real_T value);
extern boolean_T rtIsNaNF(real32_T value);

#ifdef __cplusplus
}
#endif
#endif
/**
 * File trailer for rt_nonfinite.h
 *
 * [EOF]
 */
