#pragma once

#include "ALLIUserP.h"

#include <boost/filesystem.hpp>

namespace ALLIVaultCore
{
	class ALLINUClientFolderP;
	class ALLINUMBPlainFolderP;
	class ALLINUPlainFolderP;
	class ALLINUClientRepoP;
	class ALLINUEncryptedRepoP;
	class ALLINUMBEncryptedRepoP;
	class ALLINUMBPlainRepoP;
	class ALLINUPlainRepoP;
	namespace Helpers
	{
		class ALLIUserAccount;
	}
	namespace FrontEnd
	{
		class ALLINewUserP :
			public ALLIUserP
		{
		public:
			void(*open_plain_repo_fn_ptr)(const boost::filesystem::path &);
			void(*open_encrypt_repo_fn_ptr)(const boost::filesystem::path &);
			void(*monitor_plain_folder_fn_ptr)(const boost::filesystem::path &);
			void(*mb_registry_fn_ptr)();
			void(*mb_open_plain_repo_fn_ptr)(const boost::filesystem::path &);
			void(*mb_open_encrypt_repo_fn_ptr)(const boost::filesystem::path &);
			void(*mb_monitor_plain_folder_fn_ptr)(const boost::filesystem::path &);

			ALLIVAULTCOREP_API ALLINewUserP(std::string(*uri_fn_ptr)(const std::string &repo, const std::string &host));
			ALLINewUserP(const ALLIVaultCore::FrontEnd::ALLINewUserP &src);
			ALLIVAULTCOREP_API ~ALLINewUserP();

			ALLIVAULTCOREP_API int userNameORemailAddressExists(const std::string &username, const std::string &email);
			static ALLIVAULTCOREP_API bool createRSAKeyPair(const std::string &uname, boost::filesystem::path &pubKeyPath);
			ALLIVAULTCOREP_API bool createUserAccount(const ALLIVaultCore::Helpers::ALLIUserAccount &uacct);
			ALLIVAULTCOREP_API void processNewUser(const std::string &uname);
			ALLIVAULTCOREP_API bool userNameValid(const std::string &username);
			ALLIVAULTCOREP_API bool emailAddressValid(const std::string &email);
			ALLIVAULTCOREP_API bool validateCode(const std::string &lowsrc);

		private:
			ALLIVaultCore::ALLINUClientRepoP *nuClientReppo;
			ALLIVaultCore::ALLINUClientFolderP *nuClientFolder;
			ALLIVaultCore::ALLINUEncryptedRepoP *nuEncryptedRepo;
			ALLIVaultCore::ALLINUPlainRepoP *nuPlainRepo;
			ALLIVaultCore::ALLINUPlainFolderP *nuPlainFolder;
			ALLIVaultCore::ALLINUMBEncryptedRepoP *nuMBEncryptedRepo;
			ALLIVaultCore::ALLINUMBPlainRepoP *nuMBPlainRepo;
			ALLIVaultCore::ALLINUMBPlainFolderP *nuMBPlainFolder;
			std::string(*uri_fn_ptr)(const std::string &repo, const std::string &host);

			void batchActionForNewUser(const std::string &uname);
			bool createRemoteEncryptedRepo(const std::string &userName);
			bool createRemoteEncryptedFolder(const std::string &userName);
			bool createPlainRepository(const boost::filesystem::path &plainURL);
			bool createPlainWorkDir();
			bool createEncryptedRepository(const boost::filesystem::path &encryptedURL);
			bool createEncryptedWorkDir();
			bool createPlainFolder();
			bool createPlainWorkDirEx();
			bool createEncryptedWorkDirEx();
			bool createPlainFolderEx(const boost::filesystem::path &pFolderURL);
		};
	}
}

