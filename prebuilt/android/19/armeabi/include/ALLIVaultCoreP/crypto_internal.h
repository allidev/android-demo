//
//  crypto_internal.h
//  test_crypto_internal
//
//  Created by XUESONG HU on 8/6/13.
//  Copyright (c) 2013 XUESONG HU. All rights reserved.
//

#ifndef ALLIVault_crypto_internal_h
#define ALLIVault_crypto_internal_h

#include "alli_common.h"
#include "openssl/pem.h"
#include <stdio.h>

ALLIVAULT_BEGIN_DECL
	
	ALLIVAULTCOREP_API int do_evp_seal_inKey(FILE *in_file, FILE *out_file);
	ALLIVAULTCOREP_API int do_evp_unseal_inKey(FILE *in_file, FILE *out_file);
	ALLIVAULTCOREP_API int create_temp_filename(char **temp_file, const char *src_file);
	ALLIVAULTCOREP_API int increase_ref_count(void);
	ALLIVAULTCOREP_API int decrease_ref_count(void);
	ALLIVAULTCOREP_API int get_ref_count();
	ALLIVAULTCOREP_API EVP_PKEY *generate_key();
	ALLIVAULTCOREP_API int write_prikey_to_disk(FILE *prikey_file, EVP_PKEY *pkey);
	ALLIVAULTCOREP_API int write_pubkey_to_disk(FILE *pubkey_file, EVP_PKEY *pkey);
	
ALLIVAULT_END_DECL

#endif
