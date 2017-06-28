#pragma once
#include "alli_event_args.h"
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
		};
	}
}

