#pragma once

#include "alli_common.h"

#ifdef ALLI_WIN32
#include "win32\fileops.h"
#else
#include "unix/fileops.h"
#endif
