#pragma once

#include "alli_common.h"
#include <sys/types.h>
#include <sys/stat.h>

#ifdef ALLI_WIN32
typedef struct __stat64 alli_stat_t;
typedef unsigned short mode_t;
typedef unsigned int __w64 SOCKET;
typedef int socklen_t;
#else
typedef struct stat64 alli_stat_t;
typedef int SOCKET;
typedef int errno_t;
#define INVALID_SOCKET  (SOCKET)(-1)
#define SOCKET_ERROR            (-1)
#endif
