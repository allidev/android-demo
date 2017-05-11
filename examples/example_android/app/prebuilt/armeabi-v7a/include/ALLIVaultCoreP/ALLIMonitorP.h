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
		void remote_repo_timer_wrapper(void *payload);
		class ALLIReachabilityP;
		class ALLIMonitorP
		{
		public:
			ALLIMonitorP(ALLIVaultCore::ALLIEXTRepoP &repo);
			~ALLIMonitorP();
			ALLIMonitorP(const ALLIVaultCore::Engine::ALLIMonitorP& orig) = delete;
			ALLIMonitorP& operator=(const ALLIVaultCore::Engine::ALLIMonitorP& that) = delete;
			ALLIMonitorP(ALLIVaultCore::Engine::ALLIMonitorP &&orig) = delete;
			ALLIMonitorP &operator=(ALLIVaultCore::Engine::ALLIMonitorP &&that) = delete;

			void monitorRepo();
			void terminateThread();
			void pairingWithExistingFolder(ALLIVaultCore::ALLIEXTFolderP &folder);
			void monitorFolder();
			void increaseTimerCount();
			void decreaseTimerCount();

		private:
			ALLIVaultCore::ALLIEXTRepoP &curRepo;
			ALLIVaultCore::ALLIEXTFolderP *curFolder;
			double latency;
#ifndef ALLI_WIN32
			fsw::monitor *active_monitor;
			fsw::monitor *active_monitor_folder;
#endif
			std::atomic_uchar repoQueue, folderQueue, timerCount;
			void *encryptTimer;
			ALLIVaultCore::Engine::ALLIReachabilityP *hostReach;

#ifndef ALLI_WIN32
            friend void process_events(const std::vector<fsw::event>& events, void *context);
			friend void process_events_folder(const std::vector<fsw::event>& events, void *context);
			void localRepoCallback(const std::vector<fsw::event>& events, void *context);
			void localFolderCallback(const std::vector<fsw::event>& events, void *context);
			void localRepoCallback_init(const std::vector<fsw::event>& events);
			void localFolderCallback_init(const std::vector<fsw::event>& events);
#endif
			friend void remote_repo_timer_wrapper(void *payload);
			void monitorLocalRepo();
			void monitorRemoteRepo(void *obj);
			void monitorLocalFolder();
			void startLocalRepoCallbackEx(void *obj);
			void startLocalFolderCallbackEx(void *obj);
			void remoteRepoTimer(void *obj);
			void runOnRemoteTimer(void *obj);
		};
	}
}

