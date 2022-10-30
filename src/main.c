/**
 * @file           : main.c
 * @target         : Generic->MATLAB Host Computer
 * @details        : computional geometry algorithms
 * @author         : cuixingxing
 * @email          : cuixingxing150@gmail.com
 * @date           : 30-Oct-2022 10:57:27
 * @version        : V1.0.0
 * @copyright      : Copyright (C) 2022 cuixingxing.All rights reserved.
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/** @include file    : Include Files */
#include "main.h"
#include "inpolygon2.h"
#include "inpolygon2_emxAPI.h"
#include "inpolygon2_types.h"
#include "rt_nonfinite.h"

/** Function Declarations */
static emxArray_real_T *argInit_Unboundedx2_real_T(void);

static boolean_T argInit_boolean_T(void);

static double argInit_real_T(void);

/** Function Definitions */
/**
 * @fn             : argInit_Unboundedx2_real_T
 * @brief          :
 * @param          : void
 * @return         : emxArray_real_T *
 */
static emxArray_real_T *argInit_Unboundedx2_real_T(void)
{
  emxArray_real_T *result;
  double *result_data;
  int idx0;
  int idx1;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreate_real_T(2, 2);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < 2; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result_data[idx0 + result->size[0] * idx1] = argInit_real_T();
    }
  }
  return result;
}

/**
 * @fn             : argInit_boolean_T
 * @brief          :
 * @param          : void
 * @return         : boolean_T
 */
static boolean_T argInit_boolean_T(void)
{
  return false;
}

/**
 * @fn             : argInit_real_T
 * @brief          :
 * @param          : void
 * @return         : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/**
 * @fn             : main
 * @brief          :
 * @param          : int argc
 *                   char **argv
 * @return         : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_inpolygon2();
  /* Terminate the application.
You do not need to do this more than one time. */
  inpolygon2_terminate();
  return 0;
}

/**
 * @fn             : main_inpolygon2
 * @brief          :
 * @param          : void
 * @return         : void
 */
void main_inpolygon2(void)
{
  emxArray_real_T *contour;
  emxArray_real_T *dists;
  emxArray_real_T *points;
  /* Initialize function 'inpolygon2' input arguments. */
  /* Initialize function input argument 'contour'. */
  contour = argInit_Unboundedx2_real_T();
  /* Initialize function input argument 'points'. */
  points = argInit_Unboundedx2_real_T();
  /* Call the entry-point 'inpolygon2'. */
  emxInitArray_real_T(&dists, 1);
  inpolygon2(contour, points, argInit_boolean_T(), dists);
  emxDestroyArray_real_T(points);
  emxDestroyArray_real_T(contour);
  emxDestroyArray_real_T(dists);
}

/**
 * File trailer for main.c
 *
 * [EOF]
 */
