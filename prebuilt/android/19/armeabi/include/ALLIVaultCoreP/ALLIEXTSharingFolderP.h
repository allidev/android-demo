#pragma once
#include "ALLIEXTFolderP.h"
#include <unordered_set>
namespace ALLIVaultCore
{
	class ALLIEXTSharingFolderP :
		public ALLIEXTFolderP
	{
	public:
		ALLIEXTSharingFolderP();
		~ALLIEXTSharingFolderP();

		void setHostUserName(const std::string &huname);
		void setGroupName(const std::string &gname);
		void setGuestList(const std::unordered_set<std::string> src);
		void setGuestListURL(const boost::filesystem::path &src);

	protected:
		std::string hostUserName;
		std::string groupName;

	private:
		std::unordered_set<std::string> guestList;
		boost::filesystem::path *guestListURL;
		boost::filesystem::path *sharingURL;
	};
}

