/*
 * Copyright (C) ALLI Enterprises, Inc. ALL rights reserved.
 * 
 * This file is part of ALLIVault. For full terms see the included
 * COPYING file.
 */
#pragma once

#include "alli_common.h"
#include "ALLIUserP.h"

#include <boost/filesystem.hpp>

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class ALLIUserAccount;
	}
	namespace FrontEnd
	{
		/**
		 * Class ALLINewUserP. It handles all operations related to
		 * new user registration.
		 */
		class ALLINewUserP :
			public ALLIUserP
		{
		public:
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
			 * Class constructor. Create an ALLINewUserP object.
			 *
			 * @param uri_fn_ptr a function pointer to build a uri string
			 */
			ALLIVAULTCOREP_API ALLINewUserP(std::string(*uri_fn_ptr)(const std::string &repo, const std::string &host));
			/**
			 * Class copy constructor.
			 *
			 * @param src a const reference to an ALLINewUserP object
			 */
			ALLINewUserP(const ALLIVaultCore::FrontEnd::ALLINewUserP &src);
			/**
			 * Class destructor.
			 */
			ALLIVAULTCOREP_API ~ALLINewUserP();

			/**
			 * Check if the username or email address has already existed.
			 *
			 * @param username username chosen for the new account
			 * @param email email address for the new account
			 * @return 0 on success or error code
			 */
			ALLIVAULTCOREP_API int userNameORemailAddressExists(const std::string &username, const std::string &email);
			/**
			 * Create a pair of public-private keys. This is a static method.
			 *
			 * @param uname username for the account
			 * @param out pubKeyPath path for the created public key file
			 * @return true on success or false
			 */
			static ALLIVAULTCOREP_API bool createRSAKeyPair(const std::string &uname, boost::filesystem::path &pubKeyPath);
			/**
			 * Create the user account on the remtoe server.
			 *
			 * @param uacct an ALLIUserAccount object consisting of all information required to create a new account
			 * @return true on success or false
			 */
			ALLIVAULTCOREP_API bool createUserAccount(const ALLIVaultCore::Helpers::ALLIUserAccount &uacct);
			/**
			 * Conduct required operations on local device and remote server to get the account ready to use
			 *
			 * @param uname username for the account
			 */
			ALLIVAULTCOREP_API void processNewUser(const std::string &uname);
			/**
			 * Check if the username is valid. It is a helper function.
			 *
			 * @param username username to be verified
			 * @return true if the username conforms to the rules, false otherwise
			 */
			ALLIVAULTCOREP_API bool userNameValid(const std::string &username);
			/**
			 * Check if the email address is valid. It is a helper function.
			 *
			 * @param email email address to be verified
			 * @return true if the format conforms to a regular email address, false otherwise
			 */
			ALLIVAULTCOREP_API bool emailAddressValid(const std::string &email);
			/**
			 * Check if the registration code is valid. It is a helper function.
			 *
			 * @param lowsrc the registration code to be verified
			 * @return true if the code conforms to the internal rule, false otherwise
			 */
			ALLIVAULTCOREP_API bool validateCode(const std::string &lowsrc);
			/**
			 * Check if the registration code is actually registered on the remote server.
			 *
			 * @param regcode the registration code to be verified
			 * @param out timedOut a flag set to true if the connection timed out
			 * @return true if the code is registered, false otherwise
			 */
			ALLIVAULTCOREP_API bool validateRegistrationCode(const std::string &regcode, bool &timedOut);
			/**
			 * Activate the registration code with the remote server
			 *
			 * @param regcode the registration code to be used
			 * @param uname the username the code to be associated with
			 * @return true if the operation is successful, false otherwise
			 */
			ALLIVAULTCOREP_API bool activateRegistrationCode(const std::string &regcode, const std::string &uname);

		private:
			class ALLINewUserP_impl;
			std::unique_ptr<ALLINewUserP_impl> pimpl;
		};
	}
}

