#pragma once
#include "ALLIEXTFolderP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSecPlainRepoP;
	class ALLIEXTSecPlainFolderP :
		public ALLIEXTFolderP
	{
	public:
		ALLIEXTSecPlainFolderP(const ALLIVaultCore::ALLIEXTSecPlainRepoP &plainRepo);
		~ALLIEXTSecPlainFolderP();

		void monitorPlainFolder(const boost::filesystem::path &plainURL);

	private:
		ALLIVaultCore::Engine::SimpleFolder *plainFolder;
		ALLIVaultCore::ALLIEXTSecPlainRepoP *plainRepo;

		virtual void monitorPlainFolderImpl(const boost::filesystem::path &plainURL);
		void downloadPublicKeysForContacts(void *obj);
		virtual void load_index_db_ex() override;
	};
}

