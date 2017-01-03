#pragma once
#include "alli_common.h"
#include "ALLIUserP.h"
#include "ALLINetworkStatus.h"

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class transfer_progress_event_args;
	}
	namespace FrontEnd
	{
		class ALLINewMachineP :
			public ALLIUserP
		{
		public:
			void(*open_plain_repo_fn_ptr)(const boost::filesystem::path &);
			void(*open_encrypt_repo_fn_ptr)(const boost::filesystem::path &);
			void(*monitor_plain_folder_fn_ptr)(const boost::filesystem::path &);
			void(*mb_open_plain_repo_fn_ptr)(const boost::filesystem::path &);
			void(*mb_open_encrypt_repo_fn_ptr)(const boost::filesystem::path &);
			void(*mb_monitor_plain_folder_fn_ptr)(const boost::filesystem::path &);
			void(*init_db_fn_ptr)();
			void(*init_db_mb_fn_ptr)();
			void(*pass_uname_fn_ptr)(const std::string &);
			bool(*downloadOneFileExPtr) (const std::string &src, const boost::filesystem::path &dest, void *caller);
			void(*slot_callback_new_machine)(void *, ALLIVaultCore::FrontEnd::new_machine_event_args &);
			bool(*mb_friend_fn_ptr)();
			void(*mb_registry_fn_ptr)();
			void(*update_total_bytes_fn_ptr)();
			void(*update_total_bytes_mb_fn_ptr)();
			bool(*downloadOneFilePairExPtr) (const std::string &src, const boost::filesystem::path &dest, const std::string &src_key, const boost::filesystem::path &dest_key, void *caller);
			bool nm_mbexists;

			ALLIVAULTCOREP_API explicit ALLINewMachineP(void(*slot_callback)(void *, ALLIVaultCore::Helpers::transfer_progress_event_args &));
			ALLINewMachineP(const ALLIVaultCore::FrontEnd::ALLINewMachineP &src);
			ALLIVAULTCOREP_API ~ALLINewMachineP();

			ALLIVAULTCOREP_API bool userPasswordMatch(const std::string &username, const std::string &passwd, bool &dbTimeout);
			ALLIVAULTCOREP_API void openServerRepositoryForEncryptedRepo();
			ALLIVAULTCOREP_API void openServerRepositoryForMBEncryptedRepo();
			ALLIVAULTCOREP_API void batchActionsForNewMachine();

		private:
			class ALLINewMachineP_impl;
			std::unique_ptr<ALLINewMachineP_impl> pimpl;
		};
	}
}

