#pragma once
namespace ALLIVaultCore
{
	enum class ALLIErrorCodeP;
	namespace Helpers
	{
		class ALLIErrorP
		{
		public:
			ALLIVaultCore::ALLIErrorCodeP err_code;

			ALLIVAULTCOREP_API ALLIErrorP();
			ALLIVAULTCOREP_API ~ALLIErrorP();
		};
	}
}

