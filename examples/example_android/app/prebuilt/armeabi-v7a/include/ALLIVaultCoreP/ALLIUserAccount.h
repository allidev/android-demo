/*
* Copyright (C) ALLI Enterprises, Inc. ALL rights reserved.
*
* This file is part of ALLIVault. For full terms see the included
* COPYING file.
*/
#pragma once
#include "alli_common.h"
#include <chrono>

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	namespace Helpers
	{
		/**
		 * Class ALLIUserAccount. A data structure consisting of elements required
		 * to create a user account.
		 */
		class ALLIUserAccount
		{
		public:
			/**
			 * Class constructor. Create an ALLIUserAccount object.
			 */
			ALLIVAULTCOREP_API ALLIUserAccount();
			/**
			 * Class copy constructor.
			 *
			 * @param src a const reference to an ALLIUserAccount object
			 */
			ALLIVAULTCOREP_API ALLIUserAccount(const ALLIVaultCore::Helpers::ALLIUserAccount &src);
			/**
			 * Class destructor.
			 */
			ALLIVAULTCOREP_API ~ALLIUserAccount();

			/**
			 * Set username.
			 *
			 * @param uname username chosen
			 */
			ALLIVAULTCOREP_API void set_userName(const std::string &uname);
			std::string get_userName() const;
			/**
			 * Set password SHA1.
			 *
			 * @param pwdSha1 password SHA1 hash
			 */
			ALLIVAULTCOREP_API void set_passwdSha1(const std::string &pwdSha1);
			std::string get_passwdSha1() const;
			/**
			 * Set user full name.
			 *
			 * @param fname the full name of a new user account
			 */
			ALLIVAULTCOREP_API void set_fullName(const std::string &fname);
			std::string get_fullName() const;
			/**
			 * Set email address for the new user account.
			 *
			 * @param email the email address of the new user
			 */
			ALLIVAULTCOREP_API void set_emailAddress(const std::string &email);
			std::string get_emailAddress() const;
			/**
			 * Set the public key file path.
			 *
			 * @param pubkey the path for the newly created public key file
			 */
			ALLIVAULTCOREP_API void set_publicKeyFile(const boost::filesystem::path &pubkey);
			boost::filesystem::path get_publicKeyFile() const;
			/**
			 * Set today's date.
			 *
			 * @param td a time point for today, it has a default value if not set
			 */
			ALLIVAULTCOREP_API void set_today(const std::chrono::time_point<std::chrono::system_clock> &td);
			std::chrono::time_point<std::chrono::system_clock> get_today() const;
			/**
			 * Set expiration date for the user account.
			 *
			 * @param expdate the expiration date for the user account, it has a default value if not set
			 */
			ALLIVAULTCOREP_API void set_expiration(const std::chrono::time_point<std::chrono::system_clock> &expdate);
			std::chrono::time_point<std::chrono::system_clock> get_expiration() const;
			/**
			 * Set quote size for the user account.
			 *
			 * @param qsize the quota size for the user account, it has a default value if not set
			 */
			ALLIVAULTCOREP_API void set_quotaSize(const unsigned long long &qsize);
			unsigned long long get_quotaSize() const;

		private:
			// one: userName
			std::string _userName;
			// two: passwdSha1
			std::string _passwdSha1;
			// three: fullName
			std::string _fullName;
			// four: emailAddress
			std::string _emailAddress;
			// five: publicKeyFile
			boost::filesystem::path *_publicKeyFile;
			// six: today
			std::chrono::time_point<std::chrono::system_clock> _today;
			// seven: expiration
			std::chrono::time_point<std::chrono::system_clock> _expiration;
			// eight: quotaSize
			unsigned long long _quotaSize;
		};
	}
}

