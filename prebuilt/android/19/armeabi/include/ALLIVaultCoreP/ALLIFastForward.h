#pragma once
#include "alli_common.h"
#include "git2/types.h"

namespace libgit2cpp
{
	class commit;
	class repository;
}

namespace ALLIVaultCore
{
	namespace Engine
	{
		class SimpleRepositoryP;
		class ALLIFastForward
		{
		public:
			ALLIVAULTCOREP_API ALLIFastForward(const ALLIVaultCore::Engine::SimpleRepositoryP &clientRepo);
			ALLIVAULTCOREP_API ~ALLIFastForward();
			ALLIVAULTCOREP_API bool mergeFastForward(bool isFinishUploading, bool finishDownloading = false);
			ALLIVAULTCOREP_API bool mergeFastForwardMB(bool finishDownloading = false);

		private:
			ALLIVaultCore::Engine::SimpleRepositoryP *clientRepo;
			boost::filesystem::path repo_path;

			void mergeFastForwardInitialize();
			bool mergeFastForwardFastForward(bool isFinishUploading, bool finishDownloading = false);
			bool mergeFastForwardFastForwardMB(bool finishDownloading = false);
			void merge_fastforward__cleanup();
			bool hasMailProcessFinished();
			bool doRollback();
			std::vector<std::shared_ptr<libgit2cpp::commit>> createParentsVector(libgit2cpp::repository &repo);
			int rollbackRemoteRefs(git_oid wb_oid);
			bool isRemoteRefsRolledback(const git_oid &expected);
		};
	}
}
