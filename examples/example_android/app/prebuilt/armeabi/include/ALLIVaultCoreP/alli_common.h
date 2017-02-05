#pragma once

#ifndef ALLIVault_alli_common_h
#define ALLIVault_alli_common_h

#ifndef ALLI_SEE_SQLITE
#define ALLI_SEE_SQLITE 1
#endif

#ifndef SQLITE_HAS_CODEC
#define SQLITE_HAS_CODEC 1
#endif

//&& !defined(__CYGWIN__)
#if (defined(_WIN32))
#ifndef ALLI_WIN32
#define ALLI_WIN32 1
#endif
#endif

#if __GNUC__ >= 4
  #define ALLIVAULTCOREP_API __attribute__ ((__visibility__("default")))
#elif defined (ALLI_WIN32)
  #ifdef ALLIVAULTCOREP_EXPORTS
    #define ALLIVAULTCOREP_API __declspec(dllexport)
  #else
    #define ALLIVAULTCOREP_API __declspec(dllimport)
  #endif
#endif


#ifdef __cplusplus
# define ALLIVAULT_BEGIN_DECL extern "C" {
# define ALLIVAULT_END_DECL	}
#else
 /** Start declarations in C mode */
# define ALLIVAULT_BEGIN_DECL /* empty */
 /** End declarations in C mode */
# define ALLIVAULT_END_DECL	/* empty */
#endif

#endif