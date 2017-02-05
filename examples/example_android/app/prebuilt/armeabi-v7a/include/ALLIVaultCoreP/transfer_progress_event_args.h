#pragma once
#include "alli_event_args.h"

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class transfer_progress_event_args :
			public alli_event_args
		{
		public:
			unsigned int received_objects;
			unsigned int total_objects;
			unsigned int indexed_objects;
			size_t received_bytes;

			transfer_progress_event_args();
			~transfer_progress_event_args();
		};
	}
}

