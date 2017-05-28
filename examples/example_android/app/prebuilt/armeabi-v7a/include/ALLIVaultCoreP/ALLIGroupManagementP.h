#pragma once

namespace ALLIVaultCore
{
	class ALLIGroupManagementP
	{
	public:
		ALLIGroupManagementP(const std::string &hostName, const std::string &grpName, const std::string &guestName);
		~ALLIGroupManagementP();

		bool addGroupMemberToServer();

	private:
		std::string hostUserName;
		std::string groupName;
		std::string guestUserName;
	};
}

