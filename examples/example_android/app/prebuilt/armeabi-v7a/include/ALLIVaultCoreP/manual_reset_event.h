#pragma once

#include "alli_common.h"


namespace ALLIVaultCore
{
	namespace Helpers
	{
		class manual_reset_event
		{
		public:
			ALLIVAULTCOREP_API manual_reset_event();
			ALLIVAULTCOREP_API manual_reset_event(bool signaled);
			ALLIVAULTCOREP_API ~manual_reset_event(void);
			ALLIVAULTCOREP_API bool Reset();
			ALLIVAULTCOREP_API bool Set();
			ALLIVAULTCOREP_API bool WaitOne();
			ALLIVAULTCOREP_API bool WaitOne(int millisecondsTimeout);

		private:
			class manual_reset_event_impl;
			std::unique_ptr<manual_reset_event_impl> pimpl;
		};
	}
}