#pragma once
#include "ALLISharingSyncP_external.h"

namespace ALLIVaultCore
{
	class ALLISSPlainRepoP;
	class ALLISSEncryptedRepoP :
		public ALLISharingSyncP_external
	{
	public:
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingEncryptedRepoP;
		boost::filesystem::path *sharingEncryptedURL;
		ALLIVaultCore::Helpers::alli_event GroupMembershipRevoked;

		ALLIVAULTCOREP_API ALLISSEncryptedRepoP();
		ALLIVAULTCOREP_API ALLISSEncryptedRepoP(const ALLIVaultCore::ALLISSEncryptedRepoP &src);
		ALLIVAULTCOREP_API ~ALLISSEncryptedRepoP();

		ALLIVAULTCOREP_API std::unique_ptr<ALLIVaultCore::ALLISSPlainRepoP> copyToPlainRepo(const boost::filesystem::path &plainURL, bool &memberDeleted);
		ALLIVAULTCOREP_API bool cloneFromRemoteEncryptedRepoToURL(const boost::filesystem::path &encryptedURL, ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
		ALLIVAULTCOREP_API boost::filesystem::path extractSharingWorkDir();
		ALLIVAULTCOREP_API void monitorSharingSyncEncryptedRepo(const std::string &hostUserName);

	protected:
		virtual void moveRepositoryToURLImpl(const boost::filesystem::path &localURL, bool checkRemoteRef) override;

	private:
		int init_fail_count;

		bool copyToPlainRepo_prepare_folder(const boost::filesystem::path &plainURL);
		std::unique_ptr<libgit2cpp::repository> copyToPlainRepo_init_raw_repo(const boost::filesystem::path &plainURL);
		std::unique_ptr<ALLIVaultCore::ALLISSPlainRepoP> copyToPlainRepo_create_plain_repo(const boost::filesystem::path &plainURL);
		void decryptFilesToPlainRepo(const boost::filesystem::path &plainURL, bool &memberDeleted);
		bool decryptFile(const std::string &fileName, const boost::filesystem::path &plainURL, bool &memberDeleted);
		void decryptFile_on_close(FILE *priKeyFile, FILE *input, FILE *output, char *priKeyPath, bool &membershipRevoked);
		bool decryptFile_set_src_and_dest(boost::filesystem::path &srcDir, boost::filesystem::path &srcPath, FILE **input, FILE **output, FILE *& priKeyFile, char **priKeyPath, const std::string &fileName, const boost::filesystem::path &plainURL);
		bool decryptFile_getAESKey(const boost::filesystem::path &srcDir, const boost::filesystem::path &srcPath, bool &memberDeleted, FILE **aesKeyFile, bool &membershipRevoked);
		boost::filesystem::path get_aes_key_path(const boost::filesystem::path &srcDir, const boost::filesystem::path &srcPath);
		std::string buildRepoString();
	};
}

