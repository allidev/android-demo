#pragma once

#include "alli_common.h"

#include <condition_variable>

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class countdown_event
		{
		public:
			ALLIVAULTCOREP_API explicit countdown_event(unsigned int count);
			countdown_event(ALLIVaultCore::Helpers::countdown_event const &src) = delete;
			countdown_event &operator=(ALLIVaultCore::Helpers::countdown_event const &src) = delete;
			ALLIVAULTCOREP_API ~countdown_event(void);
			ALLIVAULTCOREP_API bool Signal();
			ALLIVAULTCOREP_API bool Wait();

		private:
			class countdown_event_impl;
			std::unique_ptr<countdown_event_impl> pimpl;
		};
	}
}
