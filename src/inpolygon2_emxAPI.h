/**
 * @file           : inpolygon2_emxAPI.h
 * @target         : Generic->MATLAB Host Computer
 * @details        : computional geometry algorithms
 * @author         : cuixingxing
 * @email          : cuixingxing150@gmail.com
 * @date           : 30-Oct-2022 10:57:27
 * @version        : V1.0.0
 * @copyright      : Copyright (C) 2022 cuixingxing.All rights reserved.
 */

#ifndef INPOLYGON2_EMXAPI_H
#define INPOLYGON2_EMXAPI_H

/** @include file    : Include Files */
#include "inpolygon2_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Function Declarations */
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, const int *size);

extern emxArray_real_T *
emxCreateWrapperND_real_T(double *data, int numDimensions, const int *size);

extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows,
                                                int cols);

extern emxArray_real_T *emxCreate_real_T(int rows, int cols);

extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);

extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#ifdef __cplusplus
}
#endif

#endif
/**
 * File trailer for inpolygon2_emxAPI.h
 *
 * [EOF]
 */
