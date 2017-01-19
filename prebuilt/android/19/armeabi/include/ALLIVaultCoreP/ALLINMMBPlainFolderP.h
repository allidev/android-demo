#pragma once
#include "ALLINMPlainFolderExP.h"

namespace ALLIVaultCore
{
	class ALLINMMBPlainRepoP;
	class ALLINMMBPlainFolderP :
		public ALLINMPlainFolderExP
	{
	public:
		ALLIVAULTCOREP_API ALLINMMBPlainFolderP(ALLIVaultCore::ALLINMMBPlainRepoP *mbpRepo);
		ALLINMMBPlainFolderP(const ALLIVaultCore::ALLINMMBPlainFolderP &src);
		ALLIVAULTCOREP_API ~ALLINMMBPlainFolderP();

	private:
		ALLIVaultCore::ALLINMMBPlainRepoP *mbPlainRepo;

		virtual void downloadOneFileMT(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow) override;
		virtual std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBP() override;
		bool decryptFile(const boost::filesystem::path &filePathURL, const boost::filesystem::path &aesKeyURL, const boost::filesystem::path &destURL);
		virtual bool downloadOneFileEx(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow) override;
	};
}

