#pragma once

#include "alli_common.h"
#include "ALLINetworkStatus.h"

#include "git2/transport.h"
#include "git2/types.h"

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	namespace Engine
	{
		typedef struct lspayload {
			int type;
			void *payload;
		} lspayload;

		int show_ref_wrapper(git_remote_head *head, void *payload);
		class ALLIFetch
		{
		public:
			NetworkStatus (*checkHostReach)();

			ALLIVAULTCOREP_API ALLIFetch(boost::filesystem::path *client_path);
			ALLIVAULTCOREP_API ~ALLIFetch();
			ALLIVAULTCOREP_API bool fetchFromServer(bool &update, bool &git_threads_counter_orphan);
			ALLIVAULTCOREP_API int cred_acquire_cb(git_cred **cred,
				const char *url,
				const char *user_from_url,
				unsigned int allowed_types,
				void *payload);
			ALLIVAULTCOREP_API int show_ref__cb(git_remote_head *head, void *payload);

		private:
			boost::filesystem::path *client_path;
			lspayload *lsp;
			bool _cred_acquire_called;
			const char *_remote_user;
			char *_privatekey;
			bool _remote_refs_empty;

			friend int show_ref_wrapper(git_remote_head *head, void *payload);
		};
	}
}
