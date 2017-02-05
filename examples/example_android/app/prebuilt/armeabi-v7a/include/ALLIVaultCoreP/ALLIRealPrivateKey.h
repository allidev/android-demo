#pragma once

#include "alli_common.h"
#include "openssl/pem.h"
#include <string>


namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_mutex;
	}
}

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIRealPrivateKey
		{
		public:
			ALLIRealPrivateKey(void);
			static ALLIVAULTCOREP_API int getRealPrivateKey(char **real_privateKey, const boost::filesystem::path &btPath);
			static ALLIVAULTCOREP_API int getTempRealPriKeyName(char **temp_realPriKeyName, const boost::filesystem::path &rsa_privateKey);
			static ALLIVAULTCOREP_API void deleteRealPrivateKey(const char *privatekey);
			static ALLIVAULTCOREP_API void deleteRealPrivateKeyForce(const char *privateKey);
			static ALLIVAULTCOREP_API int writeEncryptedPrivateKey(EVP_PKEY *pkey, const boost::filesystem::path &rsa_privateKey);

		private:
			//static std::mutex *priKeyMutex;
			static ALLIVaultCore::Helpers::alli_mutex *priKeyMutex;
			static unsigned int keyCounter;
			static unsigned int dbKeyCounter;
		};
	}
}
