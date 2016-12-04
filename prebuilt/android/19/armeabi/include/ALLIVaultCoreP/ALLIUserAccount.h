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
		class ALLIUserAccount
		{
		public:
			ALLIVAULTCOREP_API ALLIUserAccount();
			ALLIVAULTCOREP_API ALLIUserAccount(const ALLIVaultCore::Helpers::ALLIUserAccount &src);
			ALLIVAULTCOREP_API ~ALLIUserAccount();

			ALLIVAULTCOREP_API void set_userName(const std::string &uname);
			std::string get_userName() const;
			ALLIVAULTCOREP_API void set_passwdSha1(const std::string &pwdSha1);
			std::string get_passwdSha1() const;
			ALLIVAULTCOREP_API void set_fullName(const std::string &fname);
			std::string get_fullName() const;
			ALLIVAULTCOREP_API void set_emailAddress(const std::string &email);
			std::string get_emailAddress() const;
			ALLIVAULTCOREP_API void set_publicKeyFile(const boost::filesystem::path &pubkey);
			boost::filesystem::path get_publicKeyFile() const;
			ALLIVAULTCOREP_API void set_today(const std::chrono::time_point<std::chrono::system_clock> &td);
			std::chrono::time_point<std::chrono::system_clock> get_today() const;
			ALLIVAULTCOREP_API void set_expiration(const std::chrono::time_point<std::chrono::system_clock> &expdate);
			std::chrono::time_point<std::chrono::system_clock> get_expiration() const;
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

