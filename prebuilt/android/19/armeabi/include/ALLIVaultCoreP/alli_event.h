#pragma once

#include <boost/signals2/signal.hpp>

namespace ALLIVaultCore
{
	namespace FrontEnd
	{
		class new_machine_event_args;
		typedef boost::signals2::signal<void(void *, ALLIVaultCore::FrontEnd::new_machine_event_args &)> files_to_download_update_event;
		typedef boost::signals2::signal<void(void *, ALLIVaultCore::FrontEnd::new_machine_event_args &)> mach_new_status_updated_event;
	}
	namespace Helpers
	{
		class alli_event_args;
		class transfer_progress_event_args;
		typedef boost::signals2::signal<void (void *, ALLIVaultCore::Helpers::alli_event_args &)> alli_event;
		typedef boost::signals2::signal<void(void *, ALLIVaultCore::Helpers::transfer_progress_event_args &)> transfer_progress_event;
	}
}
