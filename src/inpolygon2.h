/**
 * @file           : inpolygon2.h
 * @target         : Generic->MATLAB Host Computer
 * @details        : computional geometry algorithms
 * @author         : cuixingxing
 * @email          : cuixingxing150@gmail.com
 * @date           : 30-Oct-2022 10:57:27
 * @version        : V1.0.0
 * @copyright      : Copyright (C) 2022 cuixingxing.All rights reserved.
 */

#ifndef INPOLYGON2_H
#define INPOLYGON2_H

/** @include file    : Include Files */
#include "inpolygon2_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Function Declarations */
extern void inpolygon2(emxArray_real_T *contour, const emxArray_real_T *points,
                       boolean_T meatureDist, emxArray_real_T *dists);

extern void inpolygon2_initialize(void);

extern void inpolygon2_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/**
 * File trailer for inpolygon2.h
 *
 * [EOF]
 */
