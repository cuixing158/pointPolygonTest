/**
 * @file           : rtGetInf.c
 * @target         : Generic->MATLAB Host Computer
 * @details        : computional geometry algorithms
 * @author         : cuixingxing
 * @email          : cuixingxing150@gmail.com
 * @date           : 30-Oct-2022 10:57:27
 * @version        : V1.0.0
 * @copyright      : Copyright (C) 2022 cuixingxing.All rights reserved.
 */

/*
 * Abstract:
 *       MATLAB for code generation function to initialize non-finite, Inf and
 * MinusInf
 */
/** @include file    : Include Files */
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/*
 * Function: rtGetInf
 * ================================================================== Abstract:
 *  Initialize rtInf needed by the generated code.
 */
real_T rtGetInf(void)
{
  return rtInf;
}

/*
 * Function: rtGetInfF
 * ================================================================= Abstract:
 *  Initialize rtInfF needed by the generated code.
 */
real32_T rtGetInfF(void)
{
  return rtInfF;
}

/*
 * Function: rtGetMinusInf
 * ============================================================= Abstract:
 *  Initialize rtMinusInf needed by the generated code.
 */
real_T rtGetMinusInf(void)
{
  return rtMinusInf;
}

/*
 * Function: rtGetMinusInfF
 * ============================================================ Abstract:
 *  Initialize rtMinusInfF needed by the generated code.
 */
real32_T rtGetMinusInfF(void)
{
  return rtMinusInfF;
}

/**
 * File trailer for rtGetInf.c
 *
 * [EOF]
 */
