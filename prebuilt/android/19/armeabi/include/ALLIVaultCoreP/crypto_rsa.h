//
//  crypto_rsa.h
//  test_crypto_evp
//
//  Created by XUESONG HU on 4/30/13.
//  Copyright (c) 2013 XUESONG HU. All rights reserved.
//

#ifndef ALLIVault_crypto_rsa_h
#define ALLIVault_crypto_rsa_h

#include "alli_common.h"
#include <stdio.h>

ALLIVAULT_BEGIN_DECL
	
	ALLIVAULTCOREP_API int do_evp_seal(FILE *rsa_pkey_file, FILE *in_file, FILE *out_file);
	ALLIVAULTCOREP_API int do_evp_unseal(FILE *rsa_pkey_file, FILE *in_file, FILE *out_file);
	ALLIVAULTCOREP_API int do_evp_encrypt(FILE *rsa_pkey_file, FILE *in_file, FILE *out_file, FILE *aes_key_file);
	ALLIVAULTCOREP_API int do_evp_decrypt(FILE *rsa_pkey_file, FILE *in_file, FILE *out_file, FILE *aes_key_file);
	ALLIVAULTCOREP_API int transcrypt_aes_key(FILE *rsa_prikey_file, FILE *rsa_pubkey_file, FILE *in_file, FILE *out_file);
	ALLIVAULTCOREP_API int do_evp_sign(FILE *rsa_pkey_file, FILE *in_file, FILE *out_file);
	ALLIVAULTCOREP_API int do_evp_verify(FILE *rsa_pkey_file, FILE *in_file);
	ALLIVAULTCOREP_API int do_sign_using_rsa(FILE *rsa_pkey_file, const unsigned char *in, size_t inlen, unsigned char **dest, size_t &out_len);
	ALLIVAULTCOREP_API int do_verify_using_rsa(FILE *rsa_pkey_file, const unsigned char *in, size_t inlen);
	ALLIVAULTCOREP_API int do_encrypt_using_rsa(FILE *rsa_pubkey_file, const unsigned char *in, size_t inlen, unsigned char **dest, size_t &out_len);
	ALLIVAULTCOREP_API int do_decrypt_using_rsa(FILE *rsa_prikey_file, const unsigned char *in, size_t inlen, unsigned char **dest, size_t &out_len);
	
ALLIVAULT_END_DECL

#endif
