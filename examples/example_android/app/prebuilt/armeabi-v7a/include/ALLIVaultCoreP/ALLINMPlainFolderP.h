#pragma once
#include "ALLINMPlainFolderExP.h"

namespace ALLIVaultCore
{
	class ALLINMPlainRepoP;
	class ALLINMPlainFolderP :
		public ALLINMPlainFolderExP
	{
	public:
		ALLIVAULTCOREP_API ALLINMPlainFolderP(ALLIVaultCore::ALLINMPlainRepoP *plainRepo);
		ALLINMPlainFolderP(const ALLIVaultCore::ALLINMPlainFolderP &src);
		ALLIVAULTCOREP_API ~ALLINMPlainFolderP();

	private:
		ALLIVaultCore::ALLINMPlainRepoP *plainRepo;

		virtual std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBP() override;
		virtual void downloadOneFileMT(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow) override;
		virtual void copyFilesFromServerToPlainFolderEx(const boost::filesystem::path &plainFolderURL) override;
		bool decryptFileToPlainFolder(const std::string &fileName, const ALLIVaultCore::Engine::ALLIFolderIndex &aRow);
		// bad prcatice, as it will hide the function with the same name in the base class
		void setRegistryKey(int value);
	};
}

