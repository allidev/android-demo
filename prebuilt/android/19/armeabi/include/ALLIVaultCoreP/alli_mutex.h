#pragma once

#include "alli_common.h"


namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_mutex
		{
		public:
			ALLIVAULTCOREP_API alli_mutex(void);
			ALLIVAULTCOREP_API ~alli_mutex(void);
			ALLIVAULTCOREP_API bool WaitOne();
			ALLIVAULTCOREP_API bool TryWaitOne();
			ALLIVAULTCOREP_API void ReleaseMutex();

		private:
			class alli_mutex_impl;
			std::unique_ptr<alli_mutex_impl> pimpl;
		};
	}
}
