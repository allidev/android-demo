#pragma once

#include "alli_common.h"
#include <string>

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
		class ALLITempPath
		{
		public:
			ALLITempPath(void);
			static ALLIVAULTCOREP_API const boost::filesystem::path *getALLITempPath();
			static void setALLITempPath(const boost::filesystem::path &src);
			static void resetALLITempPath();

		private:
			static boost::filesystem::path *myTempPath;
		};
	}
}
