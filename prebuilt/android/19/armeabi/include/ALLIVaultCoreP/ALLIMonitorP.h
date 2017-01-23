#pragma once
namespace ALLIVaultCore
{
	class ALLIEXTRepoP;
	class ALLIEXTFolderP;
	namespace Engine
	{
		class ALLIMonitorP
		{
		public:
			ALLIMonitorP(ALLIVaultCore::ALLIEXTRepoP &repo);
			~ALLIMonitorP();

			void monitorRepo();
			void terminateThread();
			void pairingWithExistingFolder(ALLIVaultCore::ALLIEXTFolderP &folder);
			void monitorFolder();
		};
	}
}

