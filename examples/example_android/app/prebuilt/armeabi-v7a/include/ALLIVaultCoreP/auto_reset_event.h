#pragma once

#include "alli_common.h"


namespace ALLIVaultCore
{
	namespace Helpers
	{
		class auto_reset_event
		{
		public:
			ALLIVAULTCOREP_API auto_reset_event();
			ALLIVAULTCOREP_API explicit auto_reset_event(bool signaled);
			auto_reset_event(ALLIVaultCore::Helpers::auto_reset_event const &src) = delete;
			auto_reset_event &operator=(ALLIVaultCore::Helpers::auto_reset_event const &src) = delete;
			ALLIVAULTCOREP_API ~auto_reset_event(void);
			ALLIVAULTCOREP_API bool Reset();
			ALLIVAULTCOREP_API bool Set();
			ALLIVAULTCOREP_API bool WaitOne();
			ALLIVAULTCOREP_API bool WaitOne(int millisecondsTimeout);

		private:
			class auto_reset_event_impl;
			std::unique_ptr<auto_reset_event_impl> pimpl;
		};
	}
}
