#pragma once
#include "ALLIEXTRepoP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSecPlainRepoP :
		public ALLIEXTRepoP
	{
	public:
		ALLIEXTSecPlainRepoP();
		~ALLIEXTSecPlainRepoP();

		void openPlainRepository(const boost::filesystem::path &plainURL);

	private:
		ALLIVaultCore::Engine::SimpleRepositoryP *plainRepoP;
	};
}

