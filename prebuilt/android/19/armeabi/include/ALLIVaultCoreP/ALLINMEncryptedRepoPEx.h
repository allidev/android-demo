#pragma once
#include "ALLINMRepoP.h"

namespace ALLIVaultCore
{
	class ALLINMEncryptedRepoPEx :
		public ALLINMRepoP
	{
	public:
		ALLINMEncryptedRepoPEx();
		ALLINMEncryptedRepoPEx(const ALLIVaultCore::ALLINMEncryptedRepoPEx &src);
		~ALLINMEncryptedRepoPEx();
		ALLIVAULTCOREP_API boost::filesystem::path getEncryptedURL();

	protected:
		ALLIVaultCore::Engine::SimpleRepositoryP *encryptedRepoP;

		void decryptFilesToPlainRepoP(const boost::filesystem::path &plainURL);
		bool decryptFile(const std::string &fileName, const boost::filesystem::path &plainURL);
		// overload member functions from the base class
		virtual bool moveRepositoryEx(const boost::filesystem::path &localURL, bool checkRemoteRef) override;

	private:
		boost::filesystem::path *encryptedURL;
	};

}

