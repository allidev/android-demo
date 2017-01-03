#pragma once
#include "alli_common.h"

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
		class ALLIPublicKeyPairP
		{
		public:
			ALLIVAULTCOREP_API explicit ALLIPublicKeyPairP(const std::string &uname);
			ALLIPublicKeyPairP(const ALLIVaultCore::Helpers::ALLIPublicKeyPairP &src);
			ALLIVAULTCOREP_API ~ALLIPublicKeyPairP();
			ALLIVAULTCOREP_API bool importKeyPair(const boost::filesystem::path &keyDir);
			ALLIVAULTCOREP_API void exportKeyPair(const boost::filesystem::path &keyDir);

		private:
			class ALLIPublicKeyPairP_impl;
			std::unique_ptr<ALLIPublicKeyPairP_impl> pimpl;
		};
	}
}

