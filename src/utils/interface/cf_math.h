/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2018 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Utilities to simplify unit testing
 *
 */

#pragma once


#ifndef SITL_CF2

// Include "arm_math.h". This header generates some warnings, especially in
// unit tests. We hide them to avoid noise.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "arm_math.h"
#pragma GCC diagnostic pop

#endif

#ifdef SITL_CF2

#include <string.h>
#include <stdint.h>
#include "math.h"

#define PI                            3.1415926f
#define arm_matrix_instance_f32       Matrixf
#define arm_sqrt(x)                   sqrtf(x)
#define arm_sqrt_f32(x)               sqrtf(x)
#define arm_cos_f32(x)                cosf(x)
#define arm_sin_f32(x)                sinf(x)
#define float32_t                     float_t

typedef struct{
  uint16_t numRows;
  uint16_t numCols;
  float *pData;
} Matrixf;

// typedef float_t float32_t

#endif


#define DEG_TO_RAD (PI/180.0f)
#define RAD_TO_DEG (180.0f/PI)
