#pragma once

#include "alli_common.h"

#define ALLIVAULT_CORE_VER_MAJOR 1
#define ALLIVAULT_CORE_VER_MINOR 3
#define ALLIVAULT_CORE_VER_REVISION 0

ALLIVAULT_BEGIN_DECL

  ALLIVAULTCOREP_API void allivault_core_version(int *major, int *minor, int *rev);

ALLIVAULT_END_DECL
