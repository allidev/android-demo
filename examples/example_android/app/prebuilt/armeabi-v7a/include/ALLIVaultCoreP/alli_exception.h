#pragma once

#include "alli_common.h"
#include <string>

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_exception :
			public std::exception
		{
		public:
			ALLIVAULTCOREP_API alli_exception(void);
			ALLIVAULTCOREP_API alli_exception(const std::string &err_title, const std::string &err_text);
			ALLIVAULTCOREP_API ~alli_exception(void);
			ALLIVAULTCOREP_API const char* what() const noexcept override;

		private:
			std::string title_, text_;
		};
	}
}
