// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "alli_common.h"

#ifdef ALLI_WIN32
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <WinSock2.h>
#endif


// TODO: reference additional headers your program requires here
#include <string>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <chrono>
#include <boost/filesystem.hpp>
#include "git2.h"
#include "sqlite3.h"
#include "openssl/pem.h"
