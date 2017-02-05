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

			ALLIErrorP();
			~ALLIErrorP();
		};
	}
}

