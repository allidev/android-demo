#pragma once

#include "alli_common.h"
#include "../ALLIVaultCore/git2/types.h"

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class git_deleters
		{
		public:
			ALLIVAULTCOREP_API git_deleters(void);
			ALLIVAULTCOREP_API ~git_deleters(void);
			ALLIVAULTCOREP_API void operator()(git_repository * repo);
		};
	}
}
