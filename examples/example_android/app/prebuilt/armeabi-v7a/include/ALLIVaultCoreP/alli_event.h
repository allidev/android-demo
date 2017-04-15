#pragma once

#include <boost/signals2/signal.hpp>

namespace ALLIVaultCore
{
	class repo_event_args;
	typedef boost::signals2::signal<void(void *, ALLIVaultCore::repo_event_args &)> repo_updated_event;
	namespace FrontEnd
	{
		class new_machine_event_args;
		typedef boost::signals2::signal<void(void *, ALLIVaultCore::FrontEnd::new_machine_event_args &)> files_to_download_update_event;
		typedef boost::signals2::signal<void(void *, ALLIVaultCore::FrontEnd::new_machine_event_args &)> mach_new_status_updated_event;
		class exist_user_event_args;
		typedef boost::signals2::signal<void(void *, ALLIVaultCore::FrontEnd::exist_user_event_args &)> app_status_update_event;
	}
	namespace Helpers
	{
		class alli_event_args;
		class transfer_progress_event_args;
		typedef boost::signals2::signal<void (void *, ALLIVaultCore::Helpers::alli_event_args &)> alli_event;
		typedef boost::signals2::signal<void(void *, ALLIVaultCore::Helpers::transfer_progress_event_args &)> transfer_progress_event;
	}
}
