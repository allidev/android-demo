#pragma once
#include "alli_event.h"
#include "ALLINetworkStatus.h"

namespace ALLIVaultCore
{
	class ALLINUMBPlainFolderP;
	class ALLINUMBEncryptedRepoP;
	class ALLINUMBPlainRepoP;
	class ALLINMMBPlainRepoP;
	class ALLINMMBEncryptedRepoP;
	class ALLINMMBPlainFolderP;
	namespace Helpers
	{
		class ALLINewMachineStateP;
	}
	namespace FrontEnd
	{
		class ALLINewUserP;
		class ALLINewMachineP;
		class ALLIExistingUserP;
		class ALLIMailboxP
		{
		public:
			std::string username;
			ALLIVaultCore::Engine::NetworkStatus(*chkHost)();
			void(*filePermPtr) (const boost::filesystem::path &);
			void(*registry_fn_ptr)();
			typedef std::function<void(const boost::filesystem::path &)> OpenCallback;
			void(*open_plain_repo_fn_ptr)(const boost::filesystem::path &);
			void connectOpenPlainRepo(OpenCallback cb);
			void(*open_encrypt_repo_fn_ptr)(const boost::filesystem::path &);
			void connectOpenEncryptRepo(OpenCallback cb);
			void(*monitor_plain_folder_fn_ptr)(const boost::filesystem::path &);
			std::string(*uri_fn_ptr)(const std::string &repo, const std::string &host);
			std::string(*retrieveGlobalResourcePtr) (const std::string &key);
			typedef std::function<void()> UpdateTotalBytesCallback;
			void(*update_total_bytes_fn_ptr)();
			void connectUpdateTotalBytes(UpdateTotalBytesCallback cb);
			void(*init_db_fn_ptr)();
			void(*slot_callback_mailbox)(void *, ALLIVaultCore::FrontEnd::new_machine_event_args &);
			bool(*downloadOneFilePairExPtr) (const std::string &src, const boost::filesystem::path &dest, const std::string &src_key, const boost::filesystem::path &dest_key, void *caller);
			void(*mb_registry_fn_ptr)();
			ALLIVaultCore::Helpers::ALLINewMachineStateP *nmState;
			ALLIVaultCore::FrontEnd::mach_new_status_updated_event machNewStatusUpdated;

			ALLIMailboxP(const ALLIVaultCore::FrontEnd::ALLINewUserP &nu);
			ALLIMailboxP(const ALLIVaultCore::FrontEnd::ALLINewMachineP &nm);
			ALLIVAULTCOREP_API ALLIMailboxP(const ALLIVaultCore::FrontEnd::ALLIExistingUserP &eu);
			ALLIMailboxP(const ALLIVaultCore::FrontEnd::ALLIMailboxP &src);
			ALLIVAULTCOREP_API ~ALLIMailboxP();

			void openServerRepositoryForMBEncryptedRepo(const std::string &remoteEncryptURL);
			ALLIVAULTCOREP_API void createMailbox(const std::string &uname);
			ALLIVAULTCOREP_API void retrieveMailbox();
			void set_slot_callback(void(*slot_callback)(void *, ALLIVaultCore::Helpers::transfer_progress_event_args &));

		private:
			ALLIVaultCore::FrontEnd::ALLINewUserP *userNew;
			ALLIVaultCore::FrontEnd::ALLINewMachineP *machNew;
			ALLIVaultCore::FrontEnd::ALLIExistingUserP *existUser;
			ALLIVaultCore::ALLINUMBEncryptedRepoP *nuMBEncryptedRepo;
			ALLIVaultCore::ALLINUMBPlainRepoP *nuMBPlainRepo;
			ALLIVaultCore::ALLINUMBPlainFolderP *nuMBPlainFolder;
			ALLIVaultCore::ALLINMMBEncryptedRepoP *nmMBEncryptedRepo;
			ALLIVaultCore::ALLINMMBPlainRepoP *nmMBPlainRepo;
			ALLIVaultCore::ALLINMMBPlainFolderP *nmMBPlainFolder;
			void(*slot_callback)(void *, ALLIVaultCore::Helpers::transfer_progress_event_args &);
			UpdateTotalBytesCallback m_update_total_bytes_cb;
			OpenCallback m_open_plain_repo_cb, m_open_crypt_repo_cb;

			void initRepoesandFolder();
			bool createRemoteMBEncryptedRepo(std::string userName);
			bool createMBPlainRepository(const boost::filesystem::path &mbPlainRepoURL);
			bool createMBPlainWorkDir();
			bool createMBEncryptedRepository(const boost::filesystem::path &mbEncryptedURL);
			bool createMBEncryptedWorkDir();
			bool createMBPlainFolder();
			bool createMBPlainWorkDirEx();
			bool createMBEncryptedWorkDirEx();
			bool createMBPlainFolderEx(const boost::filesystem::path &mbpFolderURL);
			void OnMachNewStatusUpdated(ALLIVaultCore::FrontEnd::new_machine_event_args &e);
			void cloneFromRemoteMBEncryptedRepo(const boost::filesystem::path &mbEncryptURL);
			bool moveMBPlainRepository(const boost::filesystem::path &mbpURL);
			bool moveMBEncryptedRepository(const boost::filesystem::path &mbeURL);
			void copyFilesFromServerToMBPlainFolder(const boost::filesystem::path &plainFolderURL);
			void initializeDBForMailboxFolder();
			bool cloneFromRemoteMBEncryptedRepoImpl(const boost::filesystem::path &mbeURL);
			void copyMBEncryptedRepoToMBPlainRepo(const boost::filesystem::path &plainURL);
			void copyFilesFromServerToMBPlainFolderImpl(const boost::filesystem::path &mbpFolderURL);
		};
	}
}

