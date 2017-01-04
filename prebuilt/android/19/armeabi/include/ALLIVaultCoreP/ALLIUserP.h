/*
* Copyright (C) ALLI Enterprises, Inc. ALL rights reserved.
*
* This file is part of ALLIVault. For full terms see the included
* COPYING file.
*/
#pragma once
#include "ALLINetworkStatus.h"
#include "alli_event.h"

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class ALLINewMachineStateP;
	}
	namespace FrontEnd
	{
		class new_machine_event_args;
		class ALLIUserP
		{
		public:
			std::string username;
			/**
			* Function pointer for plain repo.
			*
			* @param a boost filesystem path object
			*/
			void(*open_plain_repo_fn_ptr)(const boost::filesystem::path &);
			/**
			* Function pointer for encrypt repo.
			*
			* @param a boost filesystem path object
			*/
			void(*open_encrypt_repo_fn_ptr)(const boost::filesystem::path &);
			/**
			* Function pointer for plain folder.
			*
			* @param a boost filesystem path object
			*/
			void(*monitor_plain_folder_fn_ptr)(const boost::filesystem::path &);
			/**
			* Function pointer for mailbox registry. This is for Windows use only.
			*/
			void(*mb_registry_fn_ptr)();
			/**
			* Function pointer for mailbox plain repo.
			*
			* @param a boost filesystem path object
			*/
			void(*mb_open_plain_repo_fn_ptr)(const boost::filesystem::path &);
			/**
			* Function pointer for mailbox encrypt repo.
			*
			* @param a boost filesystem path object
			*/
			void(*mb_open_encrypt_repo_fn_ptr)(const boost::filesystem::path &);
			/**
			* Function pointer for mailbox plain folder.
			*
			* @param a boost filesystem path object
			*/
			void(*mb_monitor_plain_folder_fn_ptr)(const boost::filesystem::path &);
			/**
			 * Function pointer for network reachability
			 *
			 * @return a value from enum NetworkStatus
			 */
			ALLIVaultCore::Engine::NetworkStatus(*chkHost)();
			ALLIVaultCore::FrontEnd::mach_new_status_updated_event machNewStatusUpdated;
			ALLIVaultCore::Helpers::ALLINewMachineStateP *nmState;
			std::string(*retrieveGlobalResourcePtr) (const std::string &key);
			void(*filePermPtr) (const boost::filesystem::path &);

			ALLIUserP();
			ALLIUserP(const ALLIVaultCore::FrontEnd::ALLIUserP &src);
			~ALLIUserP();

			bool userNameExists(const std::string &userName, std::string &fullName, bool &timedOut);

		protected:
			void OnMachNewStatusUpdated(ALLIVaultCore::FrontEnd::new_machine_event_args &e);
			void passOnNewMachineUpdate(void *sender, ALLIVaultCore::FrontEnd::new_machine_event_args &e);
		};
	}
}

