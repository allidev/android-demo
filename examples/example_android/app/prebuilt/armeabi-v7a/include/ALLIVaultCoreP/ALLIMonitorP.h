#pragma once
#include "alli_common.h"
#include <atomic>

#ifndef ALLI_WIN32
namespace fsw
{
	class monitor;
    class event;
}
#endif

namespace ALLIVaultCore
{
	class ALLIEXTRepoP;
	class ALLIEXTFolderP;
	namespace Engine
	{
#ifndef ALLI_WIN32
        void process_events(const std::vector<fsw::event>& events, void *context);
		void process_events_folder(const std::vector<fsw::event>& events, void *context);
#endif
		class ALLIMonitorP
		{
		public:
			ALLIMonitorP(ALLIVaultCore::ALLIEXTRepoP &repo);
			~ALLIMonitorP();
			ALLIMonitorP(const ALLIVaultCore::Engine::ALLIMonitorP& orig) = delete;
			ALLIMonitorP& operator=(const ALLIVaultCore::Engine::ALLIMonitorP& that) = delete;

			void monitorRepo();
			void terminateThread();
			void pairingWithExistingFolder(ALLIVaultCore::ALLIEXTFolderP &folder);
			void monitorFolder();

		private:
			ALLIVaultCore::ALLIEXTRepoP &curRepo;
			ALLIVaultCore::ALLIEXTFolderP *curFolder;
			double latency;
#ifndef ALLI_WIN32
			fsw::monitor *active_monitor;
			fsw::monitor *active_monitor_folder;
#endif
			std::atomic_uchar repoQueue, folderQueue;

#ifndef ALLI_WIN32
            friend void process_events(const std::vector<fsw::event>& events, void *context);
			friend void process_events_folder(const std::vector<fsw::event>& events, void *context);
			void localRepoCallback(const std::vector<fsw::event>& events, void *context);
			void localFolderCallback(const std::vector<fsw::event>& events, void *context);
			void localRepoCallback_init(const std::vector<fsw::event>& events);
			void localFolderCallback_init(const std::vector<fsw::event>& events);
#endif
			void monitorLocalRepo();
			void monitorLocalFolder();
			void startLocalRepoCallbackEx(void *obj);
			void startLocalFolderCallbackEx(void *obj);
		};
	}
}

