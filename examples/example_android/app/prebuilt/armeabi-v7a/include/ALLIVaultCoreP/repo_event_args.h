#pragma once
#include "alli_event_args.h"
namespace ALLIVaultCore
{
	class repo_event_args :
		public ALLIVaultCore::Helpers::alli_event_args
	{
	public:
		repo_event_args();
		repo_event_args(unsigned long long totbytes);
		~repo_event_args();

		bool isFolderKeyEmpty() const;
		void setFolderKey(const std::string &fkey);
		std::string getFolderKey() const;
		bool isMembershipRevoked() const;
		unsigned long long getTotalBytesUsed() const;

	private:
		std::string m_folderKey;
		unsigned long long m_totalBytesUsed;
		bool m_membershipRevoked;
	};
}

