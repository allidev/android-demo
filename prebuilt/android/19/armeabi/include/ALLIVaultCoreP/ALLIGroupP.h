#pragma once
#include <unordered_set>

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class ALLIGroupP
		{
		public:
			ALLIVAULTCOREP_API ALLIGroupP(const std::string &huname, const std::string &gname);
			ALLIGroupP(const ALLIVaultCore::Helpers::ALLIGroupP &src);
			ALLIVAULTCOREP_API ~ALLIGroupP();

			void loadMembers(const std::unordered_set<std::string> &guestList);
			ALLIVAULTCOREP_API std::string getHostUserName() const;
			ALLIVAULTCOREP_API std::string getGroupName() const;

		private:
			std::string _hostUserName;
			std::string _groupName;
			std::unordered_set<std::string> *_memberList;
		};
	}
}

