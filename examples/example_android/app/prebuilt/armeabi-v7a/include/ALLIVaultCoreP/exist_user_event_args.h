#pragma once
#include "alli_event_args.h"

namespace ALLIVaultCore
{
	namespace FrontEnd
	{
		class exist_user_event_args :
			public ALLIVaultCore::Helpers::alli_event_args
		{
		public:
			exist_user_event_args();
			exist_user_event_args(const std::string &fu);
			~exist_user_event_args();

			void setJobCompleted(bool status);

		private:
			std::string statusUpdate;
			std::string filesUpdate;
			bool jobCompleted;
		};
	}
}

