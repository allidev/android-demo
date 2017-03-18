#pragma once

#include "../alli_common.h"

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_mutex;
		class ALLIAppInit
		{
		public:
            static ALLIVAULTCOREP_API void appInitialize();
			static ALLIVAULTCOREP_API void appInitialize(const
            boost::filesystem::path &rootPath);
			static ALLIVAULTCOREP_API void appInitialize(const boost::filesystem::path &rootPath, bool isTesting);
			static ALLIVAULTCOREP_API void appTearDown();
			static ALLIVAULTCOREP_API void increment_git_threads_counter();
			static ALLIVAULTCOREP_API void decrement_git_threads_counter();

		private:
			static alli_mutex *git_mutex;
			static unsigned int git_threads_counter;
		};
	}
}
