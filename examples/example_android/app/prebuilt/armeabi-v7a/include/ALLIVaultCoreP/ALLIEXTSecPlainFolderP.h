#pragma once
#include "ALLIEXTFolderP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSecPlainRepoP;
	class ALLIEXTSecPlainFolderP :
		public ALLIEXTFolderP
	{
	public:
		ALLIEXTSecPlainFolderP(ALLIVaultCore::ALLIEXTSecPlainRepoP &plainRepo);
		~ALLIEXTSecPlainFolderP();

		void monitorPlainFolder(const boost::filesystem::path &plainURL);

	protected:
		ALLIVaultCore::Engine::SimpleFolder *plainFolder;

	private:
		ALLIVaultCore::ALLIEXTSecPlainRepoP *plainRepo;

		virtual void monitorPlainFolderImpl(const boost::filesystem::path &plainURL);
		void downloadPublicKeysForContacts(void *obj);
		virtual void load_index_db_ex() override;
		virtual void updateTotalBytesUsedImpl() override;
		bool downloadOneFileJsonImpl(const std::string &localPath) override;
		bool decryptFileToPlainFolder(const std::string &src);
		bool decryptFileToPlainFolder(const std::string &src, const boost::filesystem::path &dest);
	};
}

