#pragma once
#include "ALLISharingFromP.h"

namespace ALLIVaultCore
{
	class ALLISFPlainRepoP;
	class ALLISFEncryptedRepoP :
		public ALLISharingFromP
	{
	public:
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingEncryptedRepoP;
		boost::filesystem::path *sharingEncryptedURL;

		ALLIVAULTCOREP_API ALLISFEncryptedRepoP();
		ALLISFEncryptedRepoP(const ALLIVaultCore::ALLISFEncryptedRepoP &src);
		ALLIVAULTCOREP_API ~ALLISFEncryptedRepoP();

		ALLIVAULTCOREP_API std::unique_ptr<ALLIVaultCore::ALLISFPlainRepoP> copyToPlainRepo(const boost::filesystem::path &plainURL);
		ALLIVAULTCOREP_API bool cloneFromRemoteEncryptedRepoToURL(const boost::filesystem::path &encryptedURL, ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
		ALLIVAULTCOREP_API boost::filesystem::path extractSharingWorkDir();
		ALLIVAULTCOREP_API void monitorSharingFromEncryptedRepo(const std::string &hostUserName);

		//TODO: add override
		virtual void moveRepositoryToURL(const boost::filesystem::path &localURL, bool checkRemoteRef);

	private:
		std::string buildRepoString();
		std::unique_ptr<ALLIVaultCore::ALLISFPlainRepoP> copyToPlainRepo_create_plain_repo(const boost::filesystem::path &plainURL);
	};
}
