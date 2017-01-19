#pragma once
#include "alli_common.h"
#include "ALLINetworkStatus.h"

namespace ALLIVaultCore
{
	namespace Engine
	{
		class SimpleRepositoryP;
		class ALLIPushP
		{
		public:
			ALLIVaultCore::Engine::NetworkStatus(*chkHost)();
			ALLIVaultCore::Engine::NetworkStatus(*chkHostC)(bool &causeUnknown);
			void(*upload_files_fn_ptr)();
			void(*monitor_fn_ptr)();

			ALLIVAULTCOREP_API ALLIPushP(const ALLIVaultCore::Engine::SimpleRepositoryP &clientRepoP);
			ALLIVAULTCOREP_API ~ALLIPushP();
			ALLIVAULTCOREP_API bool pushCommitToServer();

		private:
			const ALLIVaultCore::Engine::SimpleRepositoryP *clientRepoP;
			char *_remote_user;

			int cred_acquire_cb(git_cred **cred,
				const char *url,
				const char *user_from_url,
				unsigned int allowed_types,
				void *payload);
		};
	}
}
