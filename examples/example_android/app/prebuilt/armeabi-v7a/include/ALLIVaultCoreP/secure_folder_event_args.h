#pragma once
#include "alli_event_args.h"
#include "alli_hash.h"
namespace ALLIVaultCore
{
	namespace Engine
	{
		class secure_folder_event_args :
			public ALLIVaultCore::Helpers::alli_event_args
		{
		public:
			secure_folder_event_args();
			~secure_folder_event_args();

			running_sharing_group_t getSharingCurGroup() const;
			void setSharingCurGroup(running_sharing_group_t &&src);

		private:
			running_sharing_group_t sharingCurGroup;
		};
	}
}

