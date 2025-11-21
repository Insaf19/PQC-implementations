/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */


#include "lowmc_pars.h"

#include "macros.h"
#include "mzd_additional.h"


void lowmc_clear(lowmc_t* lowmc) {
  for (unsigned int i = 0; i < lowmc->r; ++i) {
  }
}
