#pragma once
#include <unordered_set>
typedef std::array<void *, 3> running_sharing_group_t;

namespace ALLIVaultCore
{
	class ALLIEXTSharingPlainFolderP;
	namespace Helpers
	{
		class ALLIGroupP
		{
		public:
			ALLIVAULTCOREP_API ALLIGroupP(const std::string &huname, const std::string &gname);
			ALLIVAULTCOREP_API ALLIGroupP(const ALLIVaultCore::Helpers::ALLIGroupP &src);
			ALLIVAULTCOREP_API ~ALLIGroupP();

			void loadMembers(const std::unordered_set<std::string> &guestList);
			ALLIVAULTCOREP_API std::string getHostUserName() const;
			ALLIVAULTCOREP_API std::string getGroupName() const;
			ALLIVAULTCOREP_API std::unordered_set<std::string> getMemberList() const;
			ALLIVAULTCOREP_API std::string getFolderContentListJson(const std::unordered_set<running_sharing_group_t> &runningGroups);

		private:
			std::string _hostUserName;
			std::string _groupName;
			std::unordered_set<std::string> *_memberList;
			ALLIVaultCore::ALLIEXTSharingPlainFolderP *_shPlainFolder;

			void getSharingPlainFolder(const std::unordered_set<running_sharing_group_t> &runningGroups);
		};
	}
}

