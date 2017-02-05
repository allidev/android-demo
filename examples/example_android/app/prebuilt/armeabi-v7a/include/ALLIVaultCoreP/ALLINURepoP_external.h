#pragma once
#include "ALLINURepoP.h"

namespace ALLIVaultCore
{
	class ALLINURepoP_external :
		public ALLINURepoP
	{
	public:
		std::string(*uri_fn_ptr)(const std::string &repo, const std::string &host);

		ALLINURepoP_external();
		ALLINURepoP_external(const ALLIVaultCore::ALLINURepoP_external &src);
		~ALLINURepoP_external();
	};
}

