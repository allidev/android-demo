#pragma once
#include "ALLIEXTRepoP.h"

namespace ALLIVaultCore
{
	class ALLIEXTSharingRepoP :
		public ALLIEXTRepoP
	{
	public:
		ALLIEXTSharingRepoP();
		~ALLIEXTSharingRepoP();

		void setHostUserName(const std::string &huname);
		void setGroupName(const std::string &gname);
		void setGuestListURL(const boost::filesystem::path &glu);
		void setGuestList(const std::unordered_set<std::string> &src);
		std::unordered_set<std::string> getGuestList() const;
		void load_guest_list_db();

	private:
		std::string hostUserName;
		std::string guestUserName;
		std::string groupName;
		boost::filesystem::path *guestListURL;
		std::unordered_set<std::string> guestList;
	};
}

