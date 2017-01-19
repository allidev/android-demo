#pragma once
#include "alli_event_args.h"

namespace ALLIVaultCore
{
	namespace Helpers
	{
		enum class ALLINMStatusP;
	}
	namespace FrontEnd
	{
		class new_machine_event_args :
			public ALLIVaultCore::Helpers::alli_event_args
		{
		public:
			std::string statusUpdate;
			std::string filesUpdate;
			ALLIVaultCore::Helpers::ALLINMStatusP nmstatus;

			new_machine_event_args();
			new_machine_event_args(const std::string &su);
			new_machine_event_args(const std::string &su, ALLIVaultCore::Helpers::ALLINMStatusP status);
			~new_machine_event_args();
		};
	}
}

