#pragma once

#include "alli_common.h"
#include <string>

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_logging
		{
		public:
			alli_logging(void);
			~alli_logging(void);
			static ALLIVAULTCOREP_API void init();
			static void write_error_message(const std::string &msg, bool shouldFlush = false);
			static ALLIVAULTCOREP_API void write_trace_message(const std::string &msg);
			static std::string build_header(const boost::filesystem::path &src_file_name, int line_number);
			static void flush();
		};
	}
}
