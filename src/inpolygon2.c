/**
 * @file           : inpolygon2.c
 * @target         : Generic->MATLAB Host Computer
 * @details        : computional geometry algorithms
 * @author         : cuixingxing
 * @email          : cuixingxing150@gmail.com
 * @date           : 30-Oct-2022 10:57:27
 * @version        : V1.0.0
 * @copyright      : Copyright (C) 2022 cuixingxing.All rights reserved.
 */

/** @include file    : Include Files */
#include "inpolygon2.h"
#include "inpolygon2_emxutil.h"
#include "inpolygon2_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/** Function Declarations */
static void all(const emxArray_boolean_T *x, emxArray_boolean_T *y);

static boolean_T any(const boolean_T x[2]);

static void b_all(const emxArray_boolean_T *x, emxArray_boolean_T *y);

static void b_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3);

static void b_or(emxArray_boolean_T *in1, const emxArray_boolean_T *in2);

static void b_sign(emxArray_real_T *x);

static void binary_expand_op(emxArray_boolean_T *in1,
                             const emxArray_real_T *in2,
                             const emxArray_real_T *in3,
                             const emxArray_real_T *in4);

static void c_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_real_T *in2);

static void d_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_boolean_T *in2,
                               const emxArray_real_T *in3);

static void e_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_real_T *in2,
                               const emxArray_real_T *in3,
                               const emxArray_real_T *in4);

static double eps(double x);

static void expand_min(const emxArray_real_T *a, const emxArray_real_T *b,
                       emxArray_real_T *c);

static void f_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_boolean_T *in2,
                               const emxArray_boolean_T *in3);

static double maximum(const emxArray_real_T *x);

static double minimum(const emxArray_real_T *x);

static void minimum2(const emxArray_real_T *x, const emxArray_real_T *y,
                     emxArray_real_T *ex);

static void repmat(const double a[2], double varargin_1, emxArray_real_T *b);

/** Function Definitions */
/**
 * @fn             : all
 * @brief          :
 * @param          : const emxArray_boolean_T *x
 *                   emxArray_boolean_T *y
 * @return         : void
 */
static void all(const emxArray_boolean_T *x, emxArray_boolean_T *y)
{
  int i1;
  int i2;
  int j;
  int vstride;
  const boolean_T *x_data;
  boolean_T *y_data;
  x_data = x->data;
  i2 = y->size[0];
  y->size[0] = x->size[0];
  emxEnsureCapacity_boolean_T(y, i2);
  y_data = y->data;
  vstride = x->size[0];
  for (i2 = 0; i2 < vstride; i2++) {
    y_data[i2] = true;
  }
  vstride = x->size[0];
  i2 = x->size[0];
  i1 = 0;
  for (j = 0; j < vstride; j++) {
    int ix;
    boolean_T exitg1;
    i1++;
    i2++;
    ix = i1;
    exitg1 = false;
    while ((!exitg1) && ((vstride > 0) && (ix <= i2))) {
      if (!x_data[ix - 1]) {
        y_data[j] = false;
        exitg1 = true;
      } else {
        ix += vstride;
      }
    }
  }
}

/**
 * @fn             : any
 * @brief          :
 * @param          : const boolean_T x[2]
 * @return         : boolean_T
 */
static boolean_T any(const boolean_T x[2])
{
  int k;
  boolean_T exitg1;
  boolean_T y;
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (x[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  return y;
}

/**
 * @fn             : b_all
 * @brief          :
 * @param          : const emxArray_boolean_T *x
 *                   emxArray_boolean_T *y
 * @return         : void
 */
static void b_all(const emxArray_boolean_T *x, emxArray_boolean_T *y)
{
  int i1;
  int i2;
  int j;
  int vstride;
  const boolean_T *x_data;
  boolean_T *y_data;
  x_data = x->data;
  i1 = y->size[0];
  y->size[0] = x->size[0];
  emxEnsureCapacity_boolean_T(y, i1);
  y_data = y->data;
  vstride = x->size[0];
  for (i1 = 0; i1 < vstride; i1++) {
    y_data[i1] = true;
  }
  vstride = x->size[0];
  i1 = 0;
  i2 = 0;
  for (j = 0; j < vstride; j++) {
    int ix;
    boolean_T exitg1;
    i1++;
    i2++;
    ix = i1;
    exitg1 = false;
    while ((!exitg1) && ((vstride > 0) && (ix <= i2))) {
      if (!x_data[ix - 1]) {
        y_data[j] = false;
        exitg1 = true;
      } else {
        ix += vstride;
      }
    }
  }
}

/**
 * @fn             : b_binary_expand_op
 * @brief          :
 * @param          : emxArray_real_T *in1
 *                   const emxArray_real_T *in2
 *                   const emxArray_real_T *in3
 * @return         : void
 */
static void b_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3)
{
  const double *in2_data;
  const double *in3_data;
  double *in1_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  int stride_3_0;
  in3_data = in3->data;
  in2_data = in2->data;
  i = in1->size[0];
  if (in2->size[0] == 1) {
    stride_0_0 = in3->size[0];
  } else {
    stride_0_0 = in2->size[0];
  }
  if (stride_0_0 == 1) {
    if (in3->size[0] == 1) {
      in1->size[0] = in2->size[0];
    } else {
      in1->size[0] = in3->size[0];
    }
  } else if (in2->size[0] == 1) {
    in1->size[0] = in3->size[0];
  } else {
    in1->size[0] = in2->size[0];
  }
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_2_0 = (in3->size[0] != 1);
  stride_3_0 = (in2->size[0] != 1);
  if (in2->size[0] == 1) {
    i = in3->size[0];
  } else {
    i = in2->size[0];
  }
  if (i == 1) {
    if (in3->size[0] == 1) {
      loop_ub = in2->size[0];
    } else {
      loop_ub = in3->size[0];
    }
  } else if (in2->size[0] == 1) {
    loop_ub = in3->size[0];
  } else {
    loop_ub = in2->size[0];
  }
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] =
        in2_data[i * stride_0_0] * in3_data[i * stride_1_0 + in3->size[0]] -
        in3_data[i * stride_2_0] * in2_data[i * stride_3_0 + in2->size[0]];
  }
}

/**
 * @fn             : b_or
 * @brief          :
 * @param          : emxArray_boolean_T *in1
 *                   const emxArray_boolean_T *in2
 * @return         : void
 */
static void b_or(emxArray_boolean_T *in1, const emxArray_boolean_T *in2)
{
  emxArray_boolean_T *b_in1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  const boolean_T *in2_data;
  boolean_T *b_in1_data;
  boolean_T *in1_data;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_boolean_T(&b_in1, 1);
  i = b_in1->size[0];
  if (in2->size[0] == 1) {
    b_in1->size[0] = in1->size[0];
  } else {
    b_in1->size[0] = in2->size[0];
  }
  emxEnsureCapacity_boolean_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_1_0 = (in2->size[0] != 1);
  if (in2->size[0] == 1) {
    loop_ub = in1->size[0];
  } else {
    loop_ub = in2->size[0];
  }
  for (i = 0; i < loop_ub; i++) {
    b_in1_data[i] = (in1_data[i * stride_0_0] || in2_data[i * stride_1_0]);
  }
  i = in1->size[0];
  in1->size[0] = b_in1->size[0];
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in1->size[0];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = b_in1_data[i];
  }
  emxFree_boolean_T(&b_in1);
}

/**
 * @fn             : b_sign
 * @brief          :
 * @param          : emxArray_real_T *x
 * @return         : void
 */
static void b_sign(emxArray_real_T *x)
{
  double *x_data;
  int k;
  int nx;
  x_data = x->data;
  nx = x->size[0];
  for (k = 0; k < nx; k++) {
    double d;
    d = x_data[k];
    if (rtIsNaN(d)) {
      d = rtNaN;
    } else if (d < 0.0) {
      d = -1.0;
    } else {
      d = (d > 0.0);
    }
    x_data[k] = d;
  }
}

/**
 * @fn             : binary_expand_op
 * @brief          :
 * @param          : emxArray_boolean_T *in1
 *                   const emxArray_real_T *in2
 *                   const emxArray_real_T *in3
 *                   const emxArray_real_T *in4
 * @return         : void
 */
static void binary_expand_op(emxArray_boolean_T *in1,
                             const emxArray_real_T *in2,
                             const emxArray_real_T *in3,
                             const emxArray_real_T *in4)
{
  const double *in2_data;
  const double *in3_data;
  const double *in4_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  int stride_3_0;
  int stride_4_0;
  boolean_T *in1_data;
  in4_data = in4->data;
  in3_data = in3->data;
  in2_data = in2->data;
  i = in1->size[0];
  if (in2->size[0] == 1) {
    if (in4->size[0] == 1) {
      stride_0_0 = in3->size[0];
    } else {
      stride_0_0 = in4->size[0];
    }
    if (stride_0_0 == 1) {
      if (in3->size[0] == 1) {
        in1->size[0] = in2->size[0];
      } else {
        in1->size[0] = in3->size[0];
      }
    } else if (in4->size[0] == 1) {
      in1->size[0] = in3->size[0];
    } else {
      in1->size[0] = in4->size[0];
    }
  } else {
    in1->size[0] = in2->size[0];
  }
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_2_0 = (in3->size[0] != 1);
  stride_3_0 = (in4->size[0] != 1);
  stride_4_0 = (in2->size[0] != 1);
  if (in2->size[0] == 1) {
    if (in4->size[0] == 1) {
      i = in3->size[0];
    } else {
      i = in4->size[0];
    }
    if (i == 1) {
      if (in3->size[0] == 1) {
        loop_ub = in2->size[0];
      } else {
        loop_ub = in3->size[0];
      }
    } else if (in4->size[0] == 1) {
      loop_ub = in3->size[0];
    } else {
      loop_ub = in4->size[0];
    }
  } else {
    loop_ub = in2->size[0];
  }
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] =
        ((in2_data[i * stride_0_0] - in3_data[i * stride_1_0] == 0.0) &&
         (in3_data[i * stride_2_0] - in4_data[i * stride_3_0] == 0.0) &&
         (in2_data[i * stride_4_0] != 0.0));
  }
}

/**
 * @fn             : c_binary_expand_op
 * @brief          :
 * @param          : emxArray_boolean_T *in1
 *                   const emxArray_real_T *in2
 * @return         : void
 */
static void c_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_real_T *in2)
{
  emxArray_boolean_T *b_in1;
  const double *in2_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  boolean_T *b_in1_data;
  boolean_T *in1_data;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_boolean_T(&b_in1, 1);
  i = b_in1->size[0];
  if (in2->size[0] == 1) {
    b_in1->size[0] = in1->size[0];
  } else {
    b_in1->size[0] = in2->size[0];
  }
  emxEnsureCapacity_boolean_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_1_0 = (in2->size[0] != 1);
  if (in2->size[0] == 1) {
    loop_ub = in1->size[0];
  } else {
    loop_ub = in2->size[0];
  }
  for (i = 0; i < loop_ub; i++) {
    b_in1_data[i] =
        (in1_data[i * stride_0_0] && (in2_data[i * stride_1_0] != 0.0));
  }
  i = in1->size[0];
  in1->size[0] = b_in1->size[0];
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in1->size[0];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = b_in1_data[i];
  }
  emxFree_boolean_T(&b_in1);
}

/**
 * @fn             : d_binary_expand_op
 * @brief          :
 * @param          : emxArray_boolean_T *in1
 *                   const emxArray_boolean_T *in2
 *                   const emxArray_real_T *in3
 * @return         : void
 */
static void d_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_boolean_T *in2,
                               const emxArray_real_T *in3)
{
  const double *in3_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  const boolean_T *in2_data;
  boolean_T *in1_data;
  in3_data = in3->data;
  in2_data = in2->data;
  i = in1->size[0];
  if (in3->size[0] == 1) {
    in1->size[0] = in2->size[0];
  } else {
    in1->size[0] = in3->size[0];
  }
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  if (in3->size[0] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = in3->size[0];
  }
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] =
        (in2_data[i * stride_0_0] && (in3_data[i * stride_1_0] == 0.0));
  }
}

/**
 * @fn             : e_binary_expand_op
 * @brief          :
 * @param          : emxArray_boolean_T *in1
 *                   const emxArray_real_T *in2
 *                   const emxArray_real_T *in3
 *                   const emxArray_real_T *in4
 * @return         : void
 */
static void e_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_real_T *in2,
                               const emxArray_real_T *in3,
                               const emxArray_real_T *in4)
{
  const double *in2_data;
  const double *in3_data;
  const double *in4_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  int stride_3_0;
  boolean_T *in1_data;
  in4_data = in4->data;
  in3_data = in3->data;
  in2_data = in2->data;
  i = in1->size[0];
  if (in4->size[0] == 1) {
    stride_0_0 = in3->size[0];
  } else {
    stride_0_0 = in4->size[0];
  }
  if (stride_0_0 == 1) {
    if (in3->size[0] == 1) {
      in1->size[0] = in2->size[0];
    } else {
      in1->size[0] = in3->size[0];
    }
  } else if (in4->size[0] == 1) {
    in1->size[0] = in3->size[0];
  } else {
    in1->size[0] = in4->size[0];
  }
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_2_0 = (in3->size[0] != 1);
  stride_3_0 = (in4->size[0] != 1);
  if (in4->size[0] == 1) {
    i = in3->size[0];
  } else {
    i = in4->size[0];
  }
  if (i == 1) {
    if (in3->size[0] == 1) {
      loop_ub = in2->size[0];
    } else {
      loop_ub = in3->size[0];
    }
  } else if (in4->size[0] == 1) {
    loop_ub = in3->size[0];
  } else {
    loop_ub = in4->size[0];
  }
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] =
        ((in2_data[i * stride_0_0] - in3_data[i * stride_1_0] == 0.0) &&
         (in3_data[i * stride_2_0] - in4_data[i * stride_3_0] == 0.0));
  }
}

/**
 * @fn             : eps
 * @brief          :
 * @param          : double x
 * @return         : double
 */
static double eps(double x)
{
  double absx;
  double r;
  int exponent;
  absx = fabs(x);
  if (rtIsInf(absx) || rtIsNaN(absx)) {
    r = rtNaN;
  } else if (absx < 4.4501477170144028E-308) {
    r = 4.94065645841247E-324;
  } else {
    frexp(absx, &exponent);
    r = ldexp(1.0, exponent - 53);
  }
  return r;
}

/**
 * @fn             : expand_min
 * @brief          :
 * @param          : const emxArray_real_T *a
 *                   const emxArray_real_T *b
 *                   emxArray_real_T *c
 * @return         : void
 */
static void expand_min(const emxArray_real_T *a, const emxArray_real_T *b,
                       emxArray_real_T *c)
{
  const double *a_data;
  const double *b_data;
  double *c_data;
  int csz_idx_0;
  int i;
  int u0;
  int u1;
  b_data = b->data;
  a_data = a->data;
  u0 = a->size[0];
  u1 = b->size[0];
  if (u0 <= u1) {
    u1 = u0;
  }
  if (b->size[0] == 1) {
    csz_idx_0 = a->size[0];
  } else if (a->size[0] == 1) {
    csz_idx_0 = b->size[0];
  } else {
    csz_idx_0 = u1;
  }
  i = c->size[0];
  u0 = a->size[0];
  u1 = b->size[0];
  if (u0 <= u1) {
    u1 = u0;
  }
  if (b->size[0] == 1) {
    c->size[0] = a->size[0];
  } else if (a->size[0] == 1) {
    c->size[0] = b->size[0];
  } else {
    c->size[0] = u1;
  }
  emxEnsureCapacity_real_T(c, i);
  c_data = c->data;
  if (csz_idx_0 != 0) {
    boolean_T b1;
    boolean_T b_b;
    b_b = (a->size[0] != 1);
    b1 = (b->size[0] != 1);
    i = csz_idx_0 - 1;
    for (u0 = 0; u0 <= i; u0++) {
      c_data[u0] = fmin(a_data[b_b * u0], b_data[b1 * u0]);
    }
  }
}

/**
 * @fn             : f_binary_expand_op
 * @brief          :
 * @param          : emxArray_boolean_T *in1
 *                   const emxArray_boolean_T *in2
 *                   const emxArray_boolean_T *in3
 * @return         : void
 */
static void f_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_boolean_T *in2,
                               const emxArray_boolean_T *in3)
{
  emxArray_boolean_T *b_in1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  const boolean_T *in2_data;
  const boolean_T *in3_data;
  boolean_T *b_in1_data;
  boolean_T *in1_data;
  in3_data = in3->data;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_boolean_T(&b_in1, 1);
  i = b_in1->size[0];
  if (in3->size[0] == 1) {
    if (in2->size[0] == 1) {
      b_in1->size[0] = in1->size[0];
    } else {
      b_in1->size[0] = in2->size[0];
    }
  } else {
    b_in1->size[0] = in3->size[0];
  }
  emxEnsureCapacity_boolean_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_1_0 = (in2->size[0] != 1);
  stride_2_0 = (in3->size[0] != 1);
  if (in3->size[0] == 1) {
    if (in2->size[0] == 1) {
      loop_ub = in1->size[0];
    } else {
      loop_ub = in2->size[0];
    }
  } else {
    loop_ub = in3->size[0];
  }
  for (i = 0; i < loop_ub; i++) {
    b_in1_data[i] = (in1_data[i * stride_0_0] || in2_data[i * stride_1_0] ||
                     in3_data[i * stride_2_0]);
  }
  i = in1->size[0];
  in1->size[0] = b_in1->size[0];
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in1->size[0];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = b_in1_data[i];
  }
  emxFree_boolean_T(&b_in1);
}

/**
 * @fn             : maximum
 * @brief          :
 * @param          : const emxArray_real_T *x
 * @return         : double
 */
static double maximum(const emxArray_real_T *x)
{
  const double *x_data;
  double ex;
  int idx;
  int k;
  int last;
  x_data = x->data;
  last = x->size[0];
  if (!rtIsNaN(x_data[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= last)) {
      if (!rtIsNaN(x_data[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    ex = x_data[0];
  } else {
    ex = x_data[idx - 1];
    idx++;
    for (k = idx; k <= last; k++) {
      double d;
      d = x_data[k - 1];
      if (ex < d) {
        ex = d;
      }
    }
  }
  return ex;
}

/**
 * @fn             : minimum
 * @brief          :
 * @param          : const emxArray_real_T *x
 * @return         : double
 */
static double minimum(const emxArray_real_T *x)
{
  const double *x_data;
  double ex;
  int idx;
  int k;
  int last;
  x_data = x->data;
  last = x->size[0];
  if (!rtIsNaN(x_data[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= last)) {
      if (!rtIsNaN(x_data[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    ex = x_data[0];
  } else {
    ex = x_data[idx - 1];
    idx++;
    for (k = idx; k <= last; k++) {
      double d;
      d = x_data[k - 1];
      if (ex > d) {
        ex = d;
      }
    }
  }
  return ex;
}

/**
 * @fn             : minimum2
 * @brief          :
 * @param          : const emxArray_real_T *x
 *                   const emxArray_real_T *y
 *                   emxArray_real_T *ex
 * @return         : void
 */
static void minimum2(const emxArray_real_T *x, const emxArray_real_T *y,
                     emxArray_real_T *ex)
{
  const double *x_data;
  const double *y_data;
  double *ex_data;
  int nx;
  int u0;
  int u1;
  y_data = y->data;
  x_data = x->data;
  nx = ex->size[0];
  u0 = x->size[0];
  u1 = y->size[0];
  if (u0 <= u1) {
    u1 = u0;
  }
  ex->size[0] = u1;
  emxEnsureCapacity_real_T(ex, nx);
  ex_data = ex->data;
  u0 = x->size[0];
  nx = y->size[0];
  if (u0 <= nx) {
    nx = u0;
  }
  for (u1 = 0; u1 < nx; u1++) {
    ex_data[u1] = fmin(x_data[u1], y_data[u1]);
  }
}

/**
 * @fn             : repmat
 * @brief          :
 * @param          : const double a[2]
 *                   double varargin_1
 *                   emxArray_real_T *b
 * @return         : void
 */
static void repmat(const double a[2], double varargin_1, emxArray_real_T *b)
{
  double *b_data;
  int i;
  int ibmat;
  int itilerow;
  int jcol;
  i = (int)varargin_1;
  ibmat = b->size[0] * b->size[1];
  b->size[0] = (int)varargin_1;
  b->size[1] = 2;
  emxEnsureCapacity_real_T(b, ibmat);
  b_data = b->data;
  for (jcol = 0; jcol < 2; jcol++) {
    ibmat = jcol * (int)varargin_1;
    for (itilerow = 0; itilerow < i; itilerow++) {
      b_data[ibmat + itilerow] = a[jcol];
    }
  }
}

/**
 * @fn             : inpolygon2
 * @brief          : Brief: determine `points` are inside, on or outside a
 * polygon/contour or calculate signed distance between `points` and the nearest
 * contour edge. Details: This function determines whether points are inside a
 * contour, outside, or lies on an edge (or coincides with a vertex). It returns
 * positive (inside), negative (outside), or zero (on an edge) value,
 * correspondingly. When measureDist=false , the return value is +1, -1, and 0,
 * respectively. Otherwise, the return value is a signed distance between the
 * point and the nearest contour edge.
 *
 *                    Principle:
 *                       The number of points of intersection between a ray
 * passing through a point and a contour, if even, outside the polygon,
 * otherwise inside the polygon.(this function is equivalent to the OpenCV
 * function `pointPolygonTest`)
 *
 *                    Note:
 *                       This function is an enhancement of matlab's built-in
 * function `inpolygon`, which supports the calculation of the distances.
 *
 *                    Syntax:
 *                        dists = inpolygon2(contour,points,meatureDist)
 *
 *                    Inputs:
 *                       contour - [n,2] size,[double] type,Polygonal order
 * vertices. points - [m,2] size,[double] type,Coordinate points of the query.
 *                       meatureDist - [1,1] size,[logical] type,Whether meature
 * distances.
 *
 *                    Outputs:
 *                       dists - [m,1] size,[double] type,Description
 *
 *                    Example 1:
 *                          % Self-intersecting polygon
 *                          xv = rand(6,1); yv = rand(6,1);
 *                          xv = [xv ; xv(1)]; yv = [yv ; yv(1)];
 *                          x = rand(1000,1); y = rand(1000,1);
 *                          dists = inpolygon2([xv,yv],[x,y]);
 *                          in = dists==1; % in:1,on:0,out:-1
 *                          plot(xv,yv,x(in),y(in),'.r',x(~in),y(~in),'.b')
 *
 *                    Example 2:
 *                          % Self-intersecting polygon, calucate point nearst
 * distance xv = 2*rand(6,1)-1; yv = 2*rand(6,1)-1; xv = [xv ; xv(1)]; yv = [yv
 * ; yv(1)]; xy=-2:.01:2; [x,y] = meshgrid(xy); points = [x(:),y(:)]; dists =
 * inpolygon2([xv,yv],points,true);
 *
 *                          figure;hold on;
 *                          dists = reshape(dists,size(x));
 *                          xydata = [xy(1),xy(end)];
 *                          imagesc(xydata,xydata,dists)
 *                          plot(xv,yv,'w-')
 *                          colormap('jet');
 *                          colorbar
 *                          axis equal off
 *                          title("distance hot map")
 *
 *                      Class support for inputs contour,points:
 *                         float: double, single
 *
 *                    See also: inpolygon
 *
 * @param          : emxArray_real_T *contour
 *                   const emxArray_real_T *points
 *                   boolean_T meatureDist
 *                   emxArray_real_T *dists
 * @return         : void
 */
void inpolygon2(emxArray_real_T *contour, const emxArray_real_T *points,
                boolean_T meatureDist, emxArray_real_T *dists)
{
  emxArray_boolean_T *b_points;
  emxArray_boolean_T *c_points;
  emxArray_boolean_T *isInRange;
  emxArray_boolean_T *isOnLine;
  emxArray_boolean_T *onLineIdxs;
  emxArray_boolean_T *r11;
  emxArray_int32_T *r;
  emxArray_int32_T *r10;
  emxArray_int32_T *r2;
  emxArray_int32_T *r4;
  emxArray_int32_T *r5;
  emxArray_int32_T *r6;
  emxArray_int32_T *r7;
  emxArray_int32_T *r8;
  emxArray_int32_T *r9;
  emxArray_real_T b_contour;
  emxArray_real_T d_contour;
  emxArray_real_T *b_currDist;
  emxArray_real_T *b_maxDists;
  emxArray_real_T *counts;
  emxArray_real_T *currDist;
  emxArray_real_T *l1;
  emxArray_real_T *l1l2Orientation;
  emxArray_real_T *l1l3Orientation;
  emxArray_real_T *l1lnorm;
  emxArray_real_T *l2;
  emxArray_real_T *l3;
  emxArray_real_T *lnorm;
  emxArray_real_T *maxDists;
  emxArray_real_T *minDist;
  emxArray_real_T *p;
  emxArray_real_T *r1;
  emxArray_real_T *r12;
  emxArray_real_T *r13;
  emxArray_real_T *r3;
  emxArray_uint32_T *idxs;
  emxArray_uint32_T *p_idxs;
  emxArray_uint32_T *y;
  const double *points_data;
  double c;
  double g_contour;
  double *contour_data;
  double *counts_data;
  double *currDist_data;
  double *dists_data;
  double *l1_data;
  double *l1l2Orientation_data;
  double *l1l3Orientation_data;
  double *l1lnorm_data;
  double *l2_data;
  double *l3_data;
  double *lnorm_data;
  double *maxDists_data;
  double *minDist_data;
  double *p_data;
  double *r15;
  int b_i;
  int b_loop_ub;
  int c_contour;
  int c_loop_ub;
  int d_loop_ub;
  int e_contour;
  int i;
  int i1;
  int i2;
  int loop_ub;
  int nx;
  int vlen;
  unsigned int *idxs_data;
  unsigned int *p_idxs_data;
  int *r16;
  boolean_T f_contour[2];
  boolean_T *isInRange_data;
  boolean_T *isOnLine_data;
  boolean_T *onLineIdxs_data;
  boolean_T *r14;
  points_data = points->data;
  contour_data = contour->data;
  /*  Author:                          cuixingxing */
  /*  Email:                           cuixingxing150@gmail.com */
  /*  Created:                         22-Oct-2022 15:33:44 */
  /*  Version history revision notes: */
  /*                                   None */
  /*  Implementation In Matlab R2022b */
  /*  Copyright © 2022 TheMatrix.All Rights Reserved. */
  /*  */
  /*  close loop polygon */
  vlen = contour->size[0] << 1;
  nx = contour->size[0] << 1;
  b_contour = *contour;
  c_contour = vlen;
  b_contour.size = &c_contour;
  b_contour.numDimensions = 1;
  d_contour = *contour;
  e_contour = nx;
  d_contour.size = &e_contour;
  d_contour.numDimensions = 1;
  c = 3.0 * eps(maximum(&b_contour) - minimum(&d_contour));
  f_contour[0] = (contour_data[0] - contour_data[contour->size[0] - 1] > c);
  f_contour[1] = (contour_data[contour->size[0]] -
                      contour_data[(contour->size[0] + contour->size[0]) - 1] >
                  c);
  emxInit_real_T(&p, 2);
  if (any(f_contour)) {
    i = p->size[0] * p->size[1];
    p->size[0] = contour->size[0] + 1;
    p->size[1] = 2;
    emxEnsureCapacity_real_T(p, i);
    p_data = p->data;
    loop_ub = contour->size[0];
    for (i = 0; i < 2; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        p_data[i1 + p->size[0] * i] = contour_data[i1 + contour->size[0] * i];
      }
      p_data[contour->size[0] + p->size[0] * i] =
          contour_data[contour->size[0] * i];
    }
    i = contour->size[0] * contour->size[1];
    contour->size[0] = p->size[0];
    contour->size[1] = 2;
    emxEnsureCapacity_real_T(contour, i);
    contour_data = contour->data;
    loop_ub = p->size[0] * 2;
    for (i = 0; i < loop_ub; i++) {
      contour_data[i] = p_data[i];
    }
  }
  /*  pre-allocation */
  emxInit_real_T(&counts, 1);
  i = counts->size[0];
  counts->size[0] = points->size[0];
  emxEnsureCapacity_real_T(counts, i);
  counts_data = counts->data;
  loop_ub = points->size[0];
  for (i = 0; i < loop_ub; i++) {
    counts_data[i] = 0.0;
  }
  i = dists->size[0];
  dists->size[0] = points->size[0];
  emxEnsureCapacity_real_T(dists, i);
  dists_data = dists->data;
  loop_ub = points->size[0];
  for (i = 0; i < loop_ub; i++) {
    dists_data[i] = rtInf;
  }
  emxInit_real_T(&maxDists, 1);
  i = maxDists->size[0];
  maxDists->size[0] = points->size[0];
  emxEnsureCapacity_real_T(maxDists, i);
  maxDists_data = maxDists->data;
  loop_ub = points->size[0];
  for (i = 0; i < loop_ub; i++) {
    maxDists_data[i] = rtInf;
  }
  emxInit_real_T(&minDist, 1);
  i = minDist->size[0];
  minDist->size[0] = points->size[0];
  emxEnsureCapacity_real_T(minDist, i);
  minDist_data = minDist->data;
  loop_ub = points->size[0];
  for (i = 0; i < loop_ub; i++) {
    minDist_data[i] = rtInf;
  }
  emxInit_real_T(&currDist, 1);
  i = currDist->size[0];
  currDist->size[0] = points->size[0];
  emxEnsureCapacity_real_T(currDist, i);
  currDist_data = currDist->data;
  loop_ub = points->size[0];
  for (i = 0; i < loop_ub; i++) {
    currDist_data[i] = rtInf;
  }
  emxInit_boolean_T(&onLineIdxs, 1);
  i = onLineIdxs->size[0];
  onLineIdxs->size[0] = points->size[0];
  emxEnsureCapacity_boolean_T(onLineIdxs, i);
  onLineIdxs_data = onLineIdxs->data;
  loop_ub = points->size[0];
  for (i = 0; i < loop_ub; i++) {
    onLineIdxs_data[i] = false;
  }
  emxInit_uint32_T(&y, 2);
  p_idxs_data = y->data;
  if (points->size[0] < 1) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = points->size[0];
    emxEnsureCapacity_uint32_T(y, i);
    p_idxs_data = y->data;
    loop_ub = points->size[0] - 1;
    for (i = 0; i <= loop_ub; i++) {
      p_idxs_data[i] = (unsigned int)i + 1U;
    }
  }
  emxInit_uint32_T(&idxs, 1);
  i = idxs->size[0];
  idxs->size[0] = y->size[1];
  emxEnsureCapacity_uint32_T(idxs, i);
  idxs_data = idxs->data;
  loop_ub = y->size[1];
  for (i = 0; i < loop_ub; i++) {
    idxs_data[i] = p_idxs_data[i];
  }
  emxFree_uint32_T(&y);
  emxInit_uint32_T(&p_idxs, 1);
  i = p_idxs->size[0];
  p_idxs->size[0] = idxs->size[0];
  emxEnsureCapacity_uint32_T(p_idxs, i);
  p_idxs_data = p_idxs->data;
  loop_ub = idxs->size[0];
  for (i = 0; i < loop_ub; i++) {
    p_idxs_data[i] = idxs_data[i];
  }
  i = contour->size[0];
  loop_ub = points->size[0];
  b_loop_ub = points->size[0];
  c_loop_ub = points->size[0];
  emxInit_boolean_T(&isOnLine, 1);
  emxInit_real_T(&l1, 2);
  emxInit_real_T(&l2, 2);
  emxInit_real_T(&l3, 2);
  emxInit_real_T(&l1l2Orientation, 1);
  emxInit_real_T(&l1l3Orientation, 1);
  emxInit_boolean_T(&isInRange, 1);
  emxInit_real_T(&lnorm, 2);
  emxInit_real_T(&l1lnorm, 1);
  emxInit_int32_T(&r);
  emxInit_real_T(&r1, 1);
  emxInit_int32_T(&r2);
  emxInit_real_T(&r3, 1);
  emxInit_int32_T(&r4);
  emxInit_int32_T(&r5);
  emxInit_int32_T(&r6);
  emxInit_int32_T(&r7);
  emxInit_int32_T(&r8);
  emxInit_int32_T(&r9);
  emxInit_int32_T(&r10);
  emxInit_boolean_T(&r11, 1);
  emxInit_real_T(&r12, 1);
  emxInit_boolean_T(&b_points, 2);
  emxInit_boolean_T(&c_points, 1);
  emxInit_real_T(&r13, 1);
  emxInit_real_T(&b_currDist, 1);
  emxInit_real_T(&b_maxDists, 1);
  for (b_i = 0; b_i <= i - 2; b_i++) {
    double a;
    double b_contour_tmp;
    double contour_tmp;
    double d;
    /*  on line */
    /*  点p位于线段v1v2之间，满足向量v1p和pv2方向向量相同，即满足公式(p.y-v1.y)*(v2.x-p.x)==(v2.y-p.y)*(p.x-v1.x)
     */
    i1 = b_points->size[0] * b_points->size[1];
    b_points->size[0] = points->size[0];
    b_points->size[1] = 2;
    emxEnsureCapacity_boolean_T(b_points, i1);
    isInRange_data = b_points->data;
    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < loop_ub; i2++) {
        isInRange_data[i2 + b_points->size[0] * i1] =
            (points_data[i2 + points->size[0] * i1] -
                 contour_data[b_i + contour->size[0] * i1] ==
             0.0);
      }
    }
    all(b_points, isOnLine);
    isOnLine_data = isOnLine->data;
    i1 = b_points->size[0] * b_points->size[1];
    b_points->size[0] = points->size[0];
    b_points->size[1] = 2;
    emxEnsureCapacity_boolean_T(b_points, i1);
    isInRange_data = b_points->data;
    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < b_loop_ub; i2++) {
        isInRange_data[i2 + b_points->size[0] * i1] =
            (points_data[i2 + points->size[0] * i1] -
                 contour_data[(b_i + contour->size[0] * i1) + 1] ==
             0.0);
      }
    }
    all(b_points, r11);
    r14 = r11->data;
    a = contour_data[b_i + contour->size[0]];
    contour_tmp = contour_data[b_i + 1];
    b_contour_tmp = contour_data[(b_i + contour->size[0]) + 1];
    g_contour = contour_data[b_i];
    i1 = c_points->size[0];
    c_points->size[0] = points->size[0];
    emxEnsureCapacity_boolean_T(c_points, i1);
    isInRange_data = c_points->data;
    for (i1 = 0; i1 < c_loop_ub; i1++) {
      c = points_data[i1 + points->size[0]];
      d = points_data[i1];
      isInRange_data[i1] = ((c - a) * (contour_tmp - d) ==
                            (b_contour_tmp - c) * (d - g_contour));
    }
    b_all(c_points, isInRange);
    isInRange_data = isInRange->data;
    if (isOnLine->size[0] == 1) {
      i1 = r11->size[0];
    } else {
      i1 = isOnLine->size[0];
    }
    if ((isOnLine->size[0] == r11->size[0]) && (i1 == isInRange->size[0])) {
      d_loop_ub = isOnLine->size[0];
      for (i1 = 0; i1 < d_loop_ub; i1++) {
        isOnLine_data[i1] =
            (isOnLine_data[i1] || r14[i1] || isInRange_data[i1]);
      }
    } else {
      f_binary_expand_op(isOnLine, r11, isInRange);
      isOnLine_data = isOnLine->data;
    }
    /* . */
    /*  point 位于线段v1v2之间 */
    nx = isOnLine->size[0];
    for (d_loop_ub = 0; d_loop_ub < nx; d_loop_ub++) {
      if (isOnLine_data[d_loop_ub]) {
        dists_data[d_loop_ub] = 0.0;
      }
    }
    d_loop_ub = onLineIdxs->size[0];
    if (onLineIdxs->size[0] == isOnLine->size[0]) {
      for (i1 = 0; i1 < d_loop_ub; i1++) {
        onLineIdxs_data[i1] = (onLineIdxs_data[i1] || isOnLine_data[i1]);
      }
    } else {
      b_or(onLineIdxs, isOnLine);
      onLineIdxs_data = onLineIdxs->data;
    }
    nx = onLineIdxs->size[0] - 1;
    vlen = 0;
    for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
      if (!onLineIdxs_data[d_loop_ub]) {
        vlen++;
      }
    }
    i1 = r6->size[0];
    r6->size[0] = vlen;
    emxEnsureCapacity_int32_T(r6, i1);
    r16 = r6->data;
    vlen = 0;
    for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
      if (!onLineIdxs_data[d_loop_ub]) {
        r16[vlen] = d_loop_ub + 1;
        vlen++;
      }
    }
    d_loop_ub = r6->size[0];
    i1 = p->size[0] * p->size[1];
    p->size[0] = r6->size[0];
    p->size[1] = 2;
    emxEnsureCapacity_real_T(p, i1);
    p_data = p->data;
    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < d_loop_ub; i2++) {
        p_data[i2 + p->size[0] * i1] =
            points_data[(r16[i2] + points->size[0] * i1) - 1];
      }
    }
    nx = onLineIdxs->size[0] - 1;
    vlen = 0;
    for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
      if (!onLineIdxs_data[d_loop_ub]) {
        vlen++;
      }
    }
    i1 = p_idxs->size[0];
    p_idxs->size[0] = vlen;
    emxEnsureCapacity_uint32_T(p_idxs, i1);
    p_idxs_data = p_idxs->data;
    vlen = 0;
    for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
      if (!onLineIdxs_data[d_loop_ub]) {
        p_idxs_data[vlen] = idxs_data[d_loop_ub];
        vlen++;
      }
    }
    if (r6->size[0] != 0) {
      /*  determine in or out */
      i1 = l1->size[0] * l1->size[1];
      l1->size[0] = p->size[0];
      l1->size[1] = 2;
      emxEnsureCapacity_real_T(l1, i1);
      l1_data = l1->data;
      i1 = l2->size[0] * l2->size[1];
      l2->size[0] = p->size[0];
      l2->size[1] = 2;
      emxEnsureCapacity_real_T(l2, i1);
      l2_data = l2->data;
      i1 = l3->size[0] * l3->size[1];
      l3->size[0] = p->size[0];
      l3->size[1] = 2;
      emxEnsureCapacity_real_T(l3, i1);
      l3_data = l3->data;
      d_loop_ub = p->size[0];
      vlen = p->size[0];
      nx = p->size[0];
      for (i1 = 0; i1 < 2; i1++) {
        for (i2 = 0; i2 < d_loop_ub; i2++) {
          l1_data[i2 + l1->size[0] * i1] =
              contour_data[b_i + contour->size[0] * i1] -
              p_data[i2 + p->size[0] * i1];
        }
        for (i2 = 0; i2 < vlen; i2++) {
          l2_data[i2 + l2->size[0] * i1] =
              contour_data[(b_i + contour->size[0] * i1) + 1] -
              p_data[i2 + p->size[0] * i1];
        }
        for (i2 = 0; i2 < nx; i2++) {
          l3_data[i2 + l3->size[0] * i1] =
              0.5 * (contour_data[contour->size[0] * i1] +
                     contour_data[contour->size[0] * i1 + 1]) -
              p_data[i2 + p->size[0] * i1];
        }
      }
      if (l1->size[0] == 1) {
        i1 = l2->size[0];
      } else {
        i1 = l1->size[0];
      }
      if (l2->size[0] == 1) {
        i2 = l1->size[0];
      } else {
        i2 = l2->size[0];
      }
      if ((l1->size[0] == l2->size[0]) && (l2->size[0] == l1->size[0]) &&
          (i1 == i2)) {
        i1 = l1l2Orientation->size[0];
        l1l2Orientation->size[0] = l1->size[0];
        emxEnsureCapacity_real_T(l1l2Orientation, i1);
        l1l2Orientation_data = l1l2Orientation->data;
        d_loop_ub = l1->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          l1l2Orientation_data[i1] = l1_data[i1] * l2_data[i1 + l2->size[0]] -
                                     l2_data[i1] * l1_data[i1 + l1->size[0]];
        }
      } else {
        b_binary_expand_op(l1l2Orientation, l1, l2);
      }
      b_sign(l1l2Orientation);
      l1l2Orientation_data = l1l2Orientation->data;
      /*  外积判断方向 */
      if (l1->size[0] == 1) {
        i1 = l3->size[0];
      } else {
        i1 = l1->size[0];
      }
      if (l3->size[0] == 1) {
        i2 = l1->size[0];
      } else {
        i2 = l3->size[0];
      }
      if ((l1->size[0] == l3->size[0]) && (l3->size[0] == l1->size[0]) &&
          (i1 == i2)) {
        i1 = l1l3Orientation->size[0];
        l1l3Orientation->size[0] = l1->size[0];
        emxEnsureCapacity_real_T(l1l3Orientation, i1);
        l1l3Orientation_data = l1l3Orientation->data;
        d_loop_ub = l1->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          l1l3Orientation_data[i1] = l1_data[i1] * l3_data[i1 + l3->size[0]] -
                                     l3_data[i1] * l1_data[i1 + l1->size[0]];
        }
      } else {
        b_binary_expand_op(l1l3Orientation, l1, l3);
      }
      b_sign(l1l3Orientation);
      l1l3Orientation_data = l1l3Orientation->data;
      if (l3->size[0] == 1) {
        i1 = l2->size[0];
      } else {
        i1 = l3->size[0];
      }
      if (l2->size[0] == 1) {
        i2 = l3->size[0];
      } else {
        i2 = l2->size[0];
      }
      if ((l3->size[0] == l2->size[0]) && (l2->size[0] == l3->size[0]) &&
          (i1 == i2)) {
        i1 = r12->size[0];
        r12->size[0] = l3->size[0];
        emxEnsureCapacity_real_T(r12, i1);
        r15 = r12->data;
        d_loop_ub = l3->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          r15[i1] = l3_data[i1] * l2_data[i1 + l2->size[0]] -
                    l2_data[i1] * l3_data[i1 + l3->size[0]];
        }
      } else {
        b_binary_expand_op(r12, l3, l2);
      }
      b_sign(r12);
      r15 = r12->data;
      if (l1l2Orientation->size[0] == 1) {
        i1 = l1l3Orientation->size[0];
      } else {
        i1 = l1l2Orientation->size[0];
      }
      if (l1l3Orientation->size[0] == 1) {
        i2 = r12->size[0];
      } else {
        i2 = l1l3Orientation->size[0];
      }
      if ((l1l2Orientation->size[0] == l1l3Orientation->size[0]) &&
          (l1l3Orientation->size[0] == r12->size[0]) && (i1 == i2)) {
        i1 = isInRange->size[0];
        isInRange->size[0] = l1l2Orientation->size[0];
        emxEnsureCapacity_boolean_T(isInRange, i1);
        isInRange_data = isInRange->data;
        d_loop_ub = l1l2Orientation->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          isInRange_data[i1] =
              ((l1l2Orientation_data[i1] - l1l3Orientation_data[i1] == 0.0) &&
               (l1l3Orientation_data[i1] - r15[i1] == 0.0));
        }
      } else {
        e_binary_expand_op(isInRange, l1l2Orientation, l1l3Orientation, r12);
        isInRange_data = isInRange->data;
      }
      /*  射线位于pv1,pv2夹角之间 */
      if (isInRange->size[0] == l1l2Orientation->size[0]) {
        i1 = r11->size[0];
        r11->size[0] = isInRange->size[0];
        emxEnsureCapacity_boolean_T(r11, i1);
        r14 = r11->data;
        d_loop_ub = isInRange->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          r14[i1] = (isInRange_data[i1] && (l1l2Orientation_data[i1] == 0.0));
        }
      } else {
        d_binary_expand_op(r11, isInRange, l1l2Orientation);
        r14 = r11->data;
      }
      /* l1l2Orientation==0 为射线与边界线重合 */
      if (isInRange->size[0] == l1l2Orientation->size[0]) {
        d_loop_ub = isInRange->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          isInRange_data[i1] =
              (isInRange_data[i1] && (l1l2Orientation_data[i1] != 0.0));
        }
      } else {
        c_binary_expand_op(isInRange, l1l2Orientation);
        isInRange_data = isInRange->data;
      }
      nx = r11->size[0] - 1;
      vlen = 0;
      for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
        if (r14[d_loop_ub]) {
          vlen++;
        }
      }
      i1 = r->size[0];
      r->size[0] = vlen;
      emxEnsureCapacity_int32_T(r, i1);
      r16 = r->data;
      vlen = 0;
      for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
        if (r14[d_loop_ub]) {
          r16[vlen] = (int)p_idxs_data[d_loop_ub];
          vlen++;
        }
      }
      nx = r11->size[0] - 1;
      vlen = 0;
      for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
        if (r14[d_loop_ub]) {
          vlen++;
        }
      }
      i1 = r1->size[0];
      r1->size[0] = vlen;
      emxEnsureCapacity_real_T(r1, i1);
      r15 = r1->data;
      vlen = 0;
      for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
        if (r14[d_loop_ub]) {
          r15[vlen] = counts_data[(int)p_idxs_data[d_loop_ub] - 1];
          vlen++;
        }
      }
      d_loop_ub = r1->size[0];
      for (i1 = 0; i1 < d_loop_ub; i1++) {
        counts_data[r16[i1] - 1] = r15[i1] + 2.0;
      }
      nx = isInRange->size[0] - 1;
      vlen = 0;
      for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
        if (isInRange_data[d_loop_ub]) {
          vlen++;
        }
      }
      i1 = r2->size[0];
      r2->size[0] = vlen;
      emxEnsureCapacity_int32_T(r2, i1);
      r16 = r2->data;
      vlen = 0;
      for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
        if (isInRange_data[d_loop_ub]) {
          r16[vlen] = (int)p_idxs_data[d_loop_ub];
          vlen++;
        }
      }
      nx = isInRange->size[0] - 1;
      vlen = 0;
      for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
        if (isInRange_data[d_loop_ub]) {
          vlen++;
        }
      }
      i1 = r3->size[0];
      r3->size[0] = vlen;
      emxEnsureCapacity_real_T(r3, i1);
      r15 = r3->data;
      vlen = 0;
      for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
        if (isInRange_data[d_loop_ub]) {
          r15[vlen] = counts_data[(int)p_idxs_data[d_loop_ub] - 1];
          vlen++;
        }
      }
      d_loop_ub = r3->size[0];
      for (i1 = 0; i1 < d_loop_ub; i1++) {
        counts_data[r16[i1] - 1] = r15[i1] + 1.0;
      }
      /*  calculate dist */
      if (meatureDist) {
        double h_contour[2];
        double b;
        i1 = lnorm->size[0] * lnorm->size[1];
        lnorm->size[0] = l1l2Orientation->size[0];
        lnorm->size[1] = 2;
        emxEnsureCapacity_real_T(lnorm, i1);
        lnorm_data = lnorm->data;
        d_loop_ub = l1l2Orientation->size[0] << 1;
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          lnorm_data[i1] = 0.0;
        }
        i1 = isInRange->size[0];
        isInRange->size[0] = l1l2Orientation->size[0];
        emxEnsureCapacity_boolean_T(isInRange, i1);
        isInRange_data = isInRange->data;
        d_loop_ub = l1l2Orientation->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          isInRange_data[i1] = (l1l2Orientation_data[i1] < 0.0);
        }
        vlen = isInRange->size[0];
        if (isInRange->size[0] == 0) {
          nx = 0;
        } else {
          nx = isInRange_data[0];
          for (d_loop_ub = 2; d_loop_ub <= vlen; d_loop_ub++) {
            nx += isInRange_data[d_loop_ub - 1];
          }
        }
        g_contour = contour_data[b_i + contour->size[0]] - b_contour_tmp;
        h_contour[0] = g_contour;
        c = contour_tmp - contour_data[b_i];
        h_contour[1] = c;
        repmat(h_contour, nx, l3);
        l3_data = l3->data;
        nx = l1l2Orientation->size[0] - 1;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (l1l2Orientation_data[d_loop_ub] < 0.0) {
            vlen++;
          }
        }
        i1 = r7->size[0];
        r7->size[0] = vlen;
        emxEnsureCapacity_int32_T(r7, i1);
        r16 = r7->data;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (l1l2Orientation_data[d_loop_ub] < 0.0) {
            r16[vlen] = d_loop_ub + 1;
            vlen++;
          }
        }
        d_loop_ub = l3->size[0];
        for (i1 = 0; i1 < 2; i1++) {
          for (i2 = 0; i2 < d_loop_ub; i2++) {
            lnorm_data[(r16[i2] + lnorm->size[0] * i1) - 1] =
                l3_data[i2 + l3->size[0] * i1];
          }
        }
        /*  向量v1v2的法式量，方向位于pv1，pv2的夹角方向之间 */
        i1 = isInRange->size[0];
        isInRange->size[0] = l1l2Orientation->size[0];
        emxEnsureCapacity_boolean_T(isInRange, i1);
        isInRange_data = isInRange->data;
        d_loop_ub = l1l2Orientation->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          isInRange_data[i1] = !(l1l2Orientation_data[i1] < 0.0);
        }
        vlen = isInRange->size[0];
        if (isInRange->size[0] == 0) {
          nx = 0;
        } else {
          nx = isInRange_data[0];
          for (d_loop_ub = 2; d_loop_ub <= vlen; d_loop_ub++) {
            nx += isInRange_data[d_loop_ub - 1];
          }
        }
        h_contour[0] = -g_contour;
        h_contour[1] = -c;
        repmat(h_contour, nx, l3);
        l3_data = l3->data;
        nx = l1l2Orientation->size[0] - 1;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (!(l1l2Orientation_data[d_loop_ub] < 0.0)) {
            vlen++;
          }
        }
        i1 = r8->size[0];
        r8->size[0] = vlen;
        emxEnsureCapacity_int32_T(r8, i1);
        r16 = r8->data;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (!(l1l2Orientation_data[d_loop_ub] < 0.0)) {
            r16[vlen] = d_loop_ub + 1;
            vlen++;
          }
        }
        d_loop_ub = l3->size[0];
        for (i1 = 0; i1 < 2; i1++) {
          for (i2 = 0; i2 < d_loop_ub; i2++) {
            lnorm_data[(r16[i2] + lnorm->size[0] * i1) - 1] =
                l3_data[i2 + l3->size[0] * i1];
          }
        }
        if (l1->size[0] == 1) {
          i1 = lnorm->size[0];
        } else {
          i1 = l1->size[0];
        }
        if (lnorm->size[0] == 1) {
          i2 = l1->size[0];
        } else {
          i2 = lnorm->size[0];
        }
        if ((l1->size[0] == lnorm->size[0]) &&
            (lnorm->size[0] == l1->size[0]) && (i1 == i2)) {
          i1 = l1lnorm->size[0];
          l1lnorm->size[0] = l1->size[0];
          emxEnsureCapacity_real_T(l1lnorm, i1);
          l1lnorm_data = l1lnorm->data;
          d_loop_ub = l1->size[0];
          for (i1 = 0; i1 < d_loop_ub; i1++) {
            l1lnorm_data[i1] = l1_data[i1] * lnorm_data[i1 + lnorm->size[0]] -
                               lnorm_data[i1] * l1_data[i1 + l1->size[0]];
          }
        } else {
          b_binary_expand_op(l1lnorm, l1, lnorm);
        }
        b_sign(l1lnorm);
        l1lnorm_data = l1lnorm->data;
        if (lnorm->size[0] == 1) {
          i1 = l2->size[0];
        } else {
          i1 = lnorm->size[0];
        }
        if (l2->size[0] == 1) {
          i2 = lnorm->size[0];
        } else {
          i2 = l2->size[0];
        }
        if ((lnorm->size[0] == l2->size[0]) &&
            (l2->size[0] == lnorm->size[0]) && (i1 == i2)) {
          i1 = r12->size[0];
          r12->size[0] = lnorm->size[0];
          emxEnsureCapacity_real_T(r12, i1);
          r15 = r12->data;
          d_loop_ub = lnorm->size[0];
          for (i1 = 0; i1 < d_loop_ub; i1++) {
            r15[i1] = lnorm_data[i1] * l2_data[i1 + l2->size[0]] -
                      l2_data[i1] * lnorm_data[i1 + lnorm->size[0]];
          }
        } else {
          b_binary_expand_op(r12, lnorm, l2);
        }
        b_sign(r12);
        r15 = r12->data;
        if (l1l2Orientation->size[0] == 1) {
          i1 = l1lnorm->size[0];
        } else {
          i1 = l1l2Orientation->size[0];
        }
        if (l1lnorm->size[0] == 1) {
          i2 = r12->size[0];
        } else {
          i2 = l1lnorm->size[0];
        }
        if (l1l2Orientation->size[0] == 1) {
          vlen = l1lnorm->size[0];
        } else {
          vlen = l1l2Orientation->size[0];
        }
        if (vlen == 1) {
          if (l1lnorm->size[0] == 1) {
            vlen = r12->size[0];
          } else {
            vlen = l1lnorm->size[0];
          }
        } else if (l1l2Orientation->size[0] == 1) {
          vlen = l1lnorm->size[0];
        } else {
          vlen = l1l2Orientation->size[0];
        }
        if ((l1l2Orientation->size[0] == l1lnorm->size[0]) &&
            (l1lnorm->size[0] == r12->size[0]) && (i1 == i2) &&
            (vlen == l1l2Orientation->size[0])) {
          i1 = isInRange->size[0];
          isInRange->size[0] = l1l2Orientation->size[0];
          emxEnsureCapacity_boolean_T(isInRange, i1);
          isInRange_data = isInRange->data;
          d_loop_ub = l1l2Orientation->size[0];
          for (i1 = 0; i1 < d_loop_ub; i1++) {
            isInRange_data[i1] =
                ((l1l2Orientation_data[i1] - l1lnorm_data[i1] == 0.0) &&
                 (l1lnorm_data[i1] - r15[i1] == 0.0) &&
                 (l1l2Orientation_data[i1] != 0.0));
          }
        } else {
          binary_expand_op(isInRange, l1l2Orientation, l1lnorm, r12);
          isInRange_data = isInRange->data;
        }
        nx = isInRange->size[0] - 1;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (isInRange_data[d_loop_ub]) {
            vlen++;
          }
        }
        i1 = r9->size[0];
        r9->size[0] = vlen;
        emxEnsureCapacity_int32_T(r9, i1);
        r16 = r9->data;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (isInRange_data[d_loop_ub]) {
            r16[vlen] = d_loop_ub + 1;
            vlen++;
          }
        }
        d_loop_ub = r9->size[0];
        i1 = l3->size[0] * l3->size[1];
        l3->size[0] = r9->size[0];
        l3->size[1] = 2;
        emxEnsureCapacity_real_T(l3, i1);
        l3_data = l3->data;
        for (i1 = 0; i1 < 2; i1++) {
          for (i2 = 0; i2 < d_loop_ub; i2++) {
            l3_data[i2 + l3->size[0] * i1] =
                p_data[(r16[i2] + p->size[0] * i1) - 1];
          }
        }
        nx = isInRange->size[0] - 1;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (!isInRange_data[d_loop_ub]) {
            vlen++;
          }
        }
        i1 = r10->size[0];
        r10->size[0] = vlen;
        emxEnsureCapacity_int32_T(r10, i1);
        r16 = r10->data;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (!isInRange_data[d_loop_ub]) {
            r16[vlen] = d_loop_ub + 1;
            vlen++;
          }
        }
        d_loop_ub = r10->size[0];
        i1 = lnorm->size[0] * lnorm->size[1];
        lnorm->size[0] = r10->size[0];
        lnorm->size[1] = 2;
        emxEnsureCapacity_real_T(lnorm, i1);
        lnorm_data = lnorm->data;
        for (i1 = 0; i1 < 2; i1++) {
          for (i2 = 0; i2 < d_loop_ub; i2++) {
            lnorm_data[i2 + lnorm->size[0] * i1] =
                p_data[(r16[i2] + p->size[0] * i1) - 1];
          }
        }
        /*  平面中经过点v1(x1,y1),v2(x2,y2)的标准直线方程为：(y1-y2)*x+(x2-x1)*y+x1*y2-x2*y1==0
         */
        /*  点p(x0,y0)到直线l:a*x+b*y+c==0的距离公式为：d = */
        /*  abs(a*x0+b*y0+c)/sqrt(a^2+b^2) */
        c = contour_data[b_i + contour->size[0]];
        a = c - b_contour_tmp;
        d = contour_data[b_i];
        b = contour_tmp - d;
        c = d * b_contour_tmp - contour_tmp * c;
        nx = isInRange->size[0] - 1;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (isInRange_data[d_loop_ub]) {
            vlen++;
          }
        }
        i1 = r4->size[0];
        r4->size[0] = vlen;
        emxEnsureCapacity_int32_T(r4, i1);
        r16 = r4->data;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (isInRange_data[d_loop_ub]) {
            r16[vlen] = (int)p_idxs_data[d_loop_ub];
            vlen++;
          }
        }
        g_contour = sqrt(a * a + b * b);
        d_loop_ub = r9->size[0];
        i1 = l1lnorm->size[0];
        l1lnorm->size[0] = r9->size[0];
        emxEnsureCapacity_real_T(l1lnorm, i1);
        l1lnorm_data = l1lnorm->data;
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          l1lnorm_data[i1] =
              (a * l3_data[i1] + b * l3_data[i1 + l3->size[0]]) + c;
        }
        nx = l1lnorm->size[0];
        i1 = l1l3Orientation->size[0];
        l1l3Orientation->size[0] = l1lnorm->size[0];
        emxEnsureCapacity_real_T(l1l3Orientation, i1);
        l1l3Orientation_data = l1l3Orientation->data;
        for (d_loop_ub = 0; d_loop_ub < nx; d_loop_ub++) {
          l1l3Orientation_data[d_loop_ub] = fabs(l1lnorm_data[d_loop_ub]);
        }
        d_loop_ub = l1l3Orientation->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          currDist_data[r16[i1] - 1] = l1l3Orientation_data[i1] / g_contour;
        }
        a = contour_data[b_i];
        d_loop_ub = r10->size[0];
        i1 = l1l3Orientation->size[0];
        l1l3Orientation->size[0] = r10->size[0];
        emxEnsureCapacity_real_T(l1l3Orientation, i1);
        l1l3Orientation_data = l1l3Orientation->data;
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          c = lnorm_data[i1] - a;
          l1l3Orientation_data[i1] = c * c;
        }
        a = contour_data[b_i + contour->size[0]];
        d_loop_ub = r10->size[0];
        i1 = r12->size[0];
        r12->size[0] = r10->size[0];
        emxEnsureCapacity_real_T(r12, i1);
        r15 = r12->data;
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          c = lnorm_data[i1 + lnorm->size[0]] - a;
          r15[i1] = c * c;
        }
        d_loop_ub = l1l3Orientation->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          l1l3Orientation_data[i1] += r15[i1];
        }
        nx = l1l3Orientation->size[0];
        for (d_loop_ub = 0; d_loop_ub < nx; d_loop_ub++) {
          l1l3Orientation_data[d_loop_ub] =
              sqrt(l1l3Orientation_data[d_loop_ub]);
        }
        d_loop_ub = r10->size[0];
        i1 = l1lnorm->size[0];
        l1lnorm->size[0] = r10->size[0];
        emxEnsureCapacity_real_T(l1lnorm, i1);
        l1lnorm_data = l1lnorm->data;
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          c = lnorm_data[i1] - contour_tmp;
          l1lnorm_data[i1] = c * c;
        }
        d_loop_ub = r10->size[0];
        i1 = r12->size[0];
        r12->size[0] = r10->size[0];
        emxEnsureCapacity_real_T(r12, i1);
        r15 = r12->data;
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          c = lnorm_data[i1 + lnorm->size[0]] - b_contour_tmp;
          r15[i1] = c * c;
        }
        d_loop_ub = l1lnorm->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          l1lnorm_data[i1] += r15[i1];
        }
        nx = l1lnorm->size[0];
        for (d_loop_ub = 0; d_loop_ub < nx; d_loop_ub++) {
          l1lnorm_data[d_loop_ub] = sqrt(l1lnorm_data[d_loop_ub]);
        }
        nx = isInRange->size[0] - 1;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (!isInRange_data[d_loop_ub]) {
            vlen++;
          }
        }
        i1 = r5->size[0];
        r5->size[0] = vlen;
        emxEnsureCapacity_int32_T(r5, i1);
        r16 = r5->data;
        vlen = 0;
        for (d_loop_ub = 0; d_loop_ub <= nx; d_loop_ub++) {
          if (!isInRange_data[d_loop_ub]) {
            r16[vlen] = (int)p_idxs_data[d_loop_ub];
            vlen++;
          }
        }
        if (l1l3Orientation->size[0] == l1lnorm->size[0]) {
          d_loop_ub = l1l3Orientation->size[0];
          for (i1 = 0; i1 < d_loop_ub; i1++) {
            c = l1l3Orientation_data[i1];
            g_contour = l1lnorm_data[i1];
            currDist_data[r16[i1] - 1] = fmin(c, g_contour);
          }
        } else {
          expand_min(l1l3Orientation, l1lnorm, r13);
          r15 = r13->data;
          d_loop_ub = r13->size[0];
          for (i1 = 0; i1 < d_loop_ub; i1++) {
            currDist_data[r16[i1] - 1] = r15[i1];
          }
        }
        d_loop_ub = p_idxs->size[0];
        i1 = b_currDist->size[0];
        b_currDist->size[0] = p_idxs->size[0];
        emxEnsureCapacity_real_T(b_currDist, i1);
        p_data = b_currDist->data;
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          p_data[i1] = currDist_data[(int)p_idxs_data[i1] - 1];
        }
        d_loop_ub = p_idxs->size[0];
        i1 = b_maxDists->size[0];
        b_maxDists->size[0] = p_idxs->size[0];
        emxEnsureCapacity_real_T(b_maxDists, i1);
        p_data = b_maxDists->data;
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          p_data[i1] = maxDists_data[(int)p_idxs_data[i1] - 1];
        }
        minimum2(b_currDist, b_maxDists, r13);
        r15 = r13->data;
        d_loop_ub = r13->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          minDist_data[(int)p_idxs_data[i1] - 1] = r15[i1];
        }
        d_loop_ub = p_idxs->size[0];
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          vlen = (int)p_idxs_data[i1] - 1;
          maxDists_data[vlen] = minDist_data[vlen];
        }
      }
    }
  }
  emxFree_real_T(&b_maxDists);
  emxFree_real_T(&b_currDist);
  emxFree_real_T(&r13);
  emxFree_boolean_T(&c_points);
  emxFree_boolean_T(&b_points);
  emxFree_boolean_T(&r11);
  emxFree_int32_T(&r10);
  emxFree_int32_T(&r9);
  emxFree_int32_T(&r8);
  emxFree_int32_T(&r7);
  emxFree_int32_T(&r6);
  emxFree_int32_T(&r5);
  emxFree_int32_T(&r4);
  emxFree_real_T(&r3);
  emxFree_int32_T(&r2);
  emxFree_real_T(&r1);
  emxFree_int32_T(&r);
  emxFree_real_T(&l1lnorm);
  emxFree_real_T(&lnorm);
  emxFree_boolean_T(&isInRange);
  emxFree_real_T(&l1l3Orientation);
  emxFree_real_T(&l1l2Orientation);
  emxFree_real_T(&l3);
  emxFree_real_T(&l2);
  emxFree_real_T(&l1);
  emxFree_real_T(&p);
  emxFree_boolean_T(&onLineIdxs);
  emxFree_boolean_T(&isOnLine);
  emxFree_uint32_T(&idxs);
  emxFree_real_T(&currDist);
  emxFree_real_T(&maxDists);
  i = r12->size[0];
  r12->size[0] = p_idxs->size[0];
  emxEnsureCapacity_real_T(r12, i);
  r15 = r12->data;
  loop_ub = p_idxs->size[0];
  for (i = 0; i < loop_ub; i++) {
    c = counts_data[(int)p_idxs_data[i] - 1];
    if (rtIsNaN(c) || rtIsInf(c)) {
      g_contour = rtNaN;
    } else if (c == 0.0) {
      g_contour = 0.0;
    } else {
      g_contour = fmod(c, 2.0);
      if (g_contour == 0.0) {
        g_contour = 0.0;
      }
    }
    r15[i] = g_contour;
  }
  nx = r12->size[0];
  for (b_i = 0; b_i < nx; b_i++) {
    if (r15[b_i] != 0.0) {
      dists_data[(int)p_idxs_data[b_i] - 1] = 1.0;
    }
  }
  nx = r12->size[0];
  for (b_i = 0; b_i < nx; b_i++) {
    if (!(r15[b_i] != 0.0)) {
      dists_data[(int)p_idxs_data[b_i] - 1] = -1.0;
    }
  }
  emxFree_real_T(&r12);
  if (meatureDist) {
    i = counts->size[0];
    counts->size[0] = p_idxs->size[0];
    emxEnsureCapacity_real_T(counts, i);
    counts_data = counts->data;
    loop_ub = p_idxs->size[0];
    for (i = 0; i < loop_ub; i++) {
      vlen = (int)p_idxs_data[i] - 1;
      counts_data[i] = dists_data[vlen] * minDist_data[vlen];
    }
    loop_ub = counts->size[0];
    for (i = 0; i < loop_ub; i++) {
      dists_data[(int)p_idxs_data[i] - 1] = counts_data[i];
    }
  }
  emxFree_uint32_T(&p_idxs);
  emxFree_real_T(&minDist);
  emxFree_real_T(&counts);
}

/**
 * @fn             : inpolygon2_initialize
 * @brief          :
 * @param          : void
 * @return         : void
 */
void inpolygon2_initialize(void)
{
}

/**
 * @fn             : inpolygon2_terminate
 * @brief          :
 * @param          : void
 * @return         : void
 */
void inpolygon2_terminate(void)
{
}

/**
 * File trailer for inpolygon2.c
 *
 * [EOF]
 */
