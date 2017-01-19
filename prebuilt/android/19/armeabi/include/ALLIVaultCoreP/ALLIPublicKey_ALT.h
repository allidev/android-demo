#pragma once

#include "alli_common.h"

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIPublicKey_ALT
		{
		public:
			ALLIVAULTCOREP_API ALLIPublicKey_ALT(void);
			char *userName;
			char *publicKey;
			char *privateKey;
			char *passPhrase;
		};
	}
}
