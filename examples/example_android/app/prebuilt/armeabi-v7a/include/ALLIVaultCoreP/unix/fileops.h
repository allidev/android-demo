#include "../alli_common.h"

#ifndef ALLI_WIN32
#ifndef ALLIVaultCoreP_unix_fileops_h
#define ALLIVaultCoreP_unix_fileops_h

#include "../ALLIVaultCoreP.h"
#include "../alli_types.h"
#include <cstdio>

#ifdef  __cplusplus
extern "C" {
#endif

	ALLIVAULTCOREP_API int alli_close(int _FileHandle);
	ALLIVAULTCOREP_API int alli_closesocket(int socketfds);
	ALLIVAULTCOREP_API errno_t alli_fopen_s(FILE **_File, const char *_Filename, const char *_Mode);
	ALLIVAULTCOREP_API FILE *alli_fsopen(const char *_Filename, const char *_Mode, int _ShFlag);
	ALLIVAULTCOREP_API int alli_read(int _FileHandle, void *_DstBuf, unsigned int _MaxCharCount);
	ALLIVAULTCOREP_API errno_t alli_sopen_s(int *_FileHandle, const char *_Filename, int _OpenFlag, int _ShareFlag, int _PermissionFlag);
	ALLIVAULTCOREP_API int alli_stat(const char *_Name, alli_stat_t *_Stat);
	ALLIVAULTCOREP_API int alli_chmod(const char *_Name, alli_stat_t *_Stat);
	ALLIVAULTCOREP_API bool alli_set_file_attributes(const char *_Filename, unsigned long _FileAttributes);

#ifdef  __cplusplus
}
#endif

#endif // ALLIVaultCoreP_unix_fileops_h
#endif // ALLI_WIN32
