#pragma once
#include "ALLIFolderIndex.h"

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIFolderIndexHistory :
			public ALLIFolderIndex
		{
		public:
			ALLIVAULTCOREP_API ALLIFolderIndexHistory();
			ALLIVAULTCOREP_API ~ALLIFolderIndexHistory();

			// Column 10 is committer
			ALLIVAULTCOREP_API std::string get_col10() const;
			ALLIVAULTCOREP_API void set_col10(const std::string &col10);
			// Column 11 is commit time
			ALLIVAULTCOREP_API time_t get_col11() const;
			ALLIVAULTCOREP_API void set_col11(time_t col11);
			// Column 12 is flag for current version
			ALLIVAULTCOREP_API bool get_col12() const;
			ALLIVAULTCOREP_API void set_col12(bool col12);

		private:
			std::string committer;
			time_t commit_time;
			bool isCurrentVersion;
		};
	}
}

