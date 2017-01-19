#pragma once
#include "ALLINUPlainRepoP.h"

namespace ALLIVaultCore
{
	class ALLINUMBPlainRepoP :
		public ALLINUPlainRepoP
	{
	public:
		ALLIVAULTCOREP_API ALLINUMBPlainRepoP();
		ALLIVAULTCOREP_API ALLINUMBPlainRepoP(const ALLIVaultCore::ALLINUMBPlainRepoP &src);
		ALLIVAULTCOREP_API ~ALLINUMBPlainRepoP();

	private:
		virtual bool createPlainFolderImpl() override;
	};
}

