#include "../alli_common.h"
#include <mutex>          // std::mutex

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLILock
		{
			std::mutex mtx;
		public:
			ALLIVAULTCOREP_API ALLILock();
			ALLIVAULTCOREP_API ~ALLILock();
			ALLIVAULTCOREP_API void enter();
			ALLIVAULTCOREP_API bool try_enter();
			ALLIVAULTCOREP_API void exit();
		};
	}
}

