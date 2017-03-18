#pragma once
#include "ALLIEXTRepoP.h"
#include <unordered_set>

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLISSHTunnelP;
	}
	class ALLISharingP :
		public ALLIEXTRepoP
	{
	public:
		// weak pointer, no need to release resources
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingRepoP;
		std::string hostUserName;
		std::string guestUserName;
		std::string groupName;
		std::unordered_set<std::string> guestList;
		boost::filesystem::path *guestListURL;
		std::string remoteSharingRepoURL;
		boost::filesystem::path *sharingURL;
		void(*fav_fn_ptr)();
		std::string(*resourceManagerGetString) (const std::string &key);
		void(*monitor_fn_ptr)(const boost::filesystem::path &sharingURL);
		void(*encrypt_monitor_fn_ptr)(const boost::filesystem::path &sharingURL, bool);

		ALLISharingP();
		ALLISharingP(const ALLIVaultCore::ALLISharingP &src);
		virtual ~ALLISharingP();

	protected:
		std::string *connStr;
		ALLIVaultCore::Engine::ALLISSHTunnelP *tunnel;

		void addSharingFolderToFavorites();
	};
}

