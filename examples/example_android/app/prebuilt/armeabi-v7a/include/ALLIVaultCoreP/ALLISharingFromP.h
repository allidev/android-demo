#pragma once
#include "ALLISharingExtP.h"

namespace ALLIVaultCore
{
	class ALLISharingFromP :
		public ALLISharingExtP
	{
	public:
		std::string(*uri_fn_ptr)(const std::string &repo, const std::string &host);

		ALLISharingFromP();
		ALLISharingFromP(const ALLIVaultCore::ALLISharingFromP &src);
		virtual ~ALLISharingFromP();

		ALLIVAULTCOREP_API void setSharingGuestUserName(const std::string &hostUserName, const std::string &groupName);
	};
}

