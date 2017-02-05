#pragma once
#include "ALLINUEncryptedRepoP.h"

namespace ALLIVaultCore
{
	class ALLINUMBEncryptedRepoP :
		public ALLINUEncryptedRepoP
	{
	public:
		ALLIVAULTCOREP_API ALLINUMBEncryptedRepoP();
		ALLIVAULTCOREP_API ~ALLINUMBEncryptedRepoP();

	private:
		virtual bool createRemoteEncryptedRepoImpl(std::string userName) override;
		virtual bool createEncryptedFolderImpl() override;
		virtual bool createEncryptedRepositoryImpl(const boost::filesystem::path &encryptedURL) override;
	};
}

