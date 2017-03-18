#pragma once
#include "alli_common.h"
#include <map>

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	
	enum class ALLIXMLMode;
	class ALLIPropertyListP
	{
	private:
		boost::filesystem::path _propFile;
		ALLIVaultCore::ALLIXMLMode _mode;

	public:
		ALLIVAULTCOREP_API ALLIPropertyListP(const boost::filesystem::path &propFile, ALLIVaultCore::ALLIXMLMode mode);
		ALLIVAULTCOREP_API ~ALLIPropertyListP();

		ALLIVAULTCOREP_API std::map<std::string, std::string> getAllProperties();
		ALLIVAULTCOREP_API void writeAllProperties(const std::map<std::string, std::string> &properties);
	};
}

