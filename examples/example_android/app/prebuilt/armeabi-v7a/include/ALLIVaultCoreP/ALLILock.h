#pragma once

#include "alli_common.h"

#ifdef ALLI_WIN32
#include "win32\ALLILock.h"
#else
#include "unix/ALLILock.h"
#endif
