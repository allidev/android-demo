#pragma once

#include "alli_common.h"
#include <string>
#include "../ALLIVaultCore/git2.h"

typedef void (*TransferProgressFnPtr) (const git_transfer_progress *);
typedef void (*CheckoutProgressFnPtr) (std::string *, int, int);

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLICloneOptions
		{
		public:
			bool barely;
			bool withCheckout;
			TransferProgressFnPtr transferProgressFnPtr;
			CheckoutProgressFnPtr checkoutProgressFnPtr;
			std::string *remoteName;
			git_cred_acquire_cb cred_acquire_cb;
			void *cred_acquire_payload;

			ALLIVAULTCOREP_API ALLICloneOptions(void);
		};
	}
}
