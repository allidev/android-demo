#pragma once
#include "ALLISharingSyncP.h"

namespace ALLIVaultCore
{
	class ALLISharingSyncP_external :
		public ALLISharingSyncP
	{
	public:
		std::string(*uri_fn_ptr)(const std::string &repo, const std::string &host);

		ALLISharingSyncP_external();
		ALLISharingSyncP_external(const ALLIVaultCore::ALLISharingSyncP_external &src);
		~ALLISharingSyncP_external();
	};
}

