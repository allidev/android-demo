#pragma once
#include "ALLISharingExtP.h"

namespace ALLIVaultCore
{
	class ALLISharingFromP :
		public ALLISharingExtP
	{
	public:
		std::string(*uri_fn_ptr)(const std::string &repo, const std::string &host);
		//void(*monitor_fn_ptr)(const boost::filesystem::path &sharingURL);

		ALLISharingFromP();
		ALLISharingFromP(const ALLIVaultCore::ALLISharingFromP &src);
		~ALLISharingFromP();

		ALLIVAULTCOREP_API void setSharingGuestUserName(const std::string &hostUserName, const std::string &groupName);
	};
}

