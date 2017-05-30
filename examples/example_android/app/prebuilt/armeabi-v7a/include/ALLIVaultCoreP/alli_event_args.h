#pragma once

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_event_args
		{
		public:
			alli_event_args(void);
			~alli_event_args(void);

			ALLIVAULTCOREP_API std::string to_string() const;

		private:
			virtual std::string to_string_impl() const;
		};
	}
}
