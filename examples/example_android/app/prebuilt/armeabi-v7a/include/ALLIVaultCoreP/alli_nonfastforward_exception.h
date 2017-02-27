#pragma once
#include "../ALLIVaultCommon/alli_exception.h"
namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_nonfastforward_exception :
			public ALLIVault::Common::alli_exception
		{
		public:
			alli_nonfastforward_exception();
			~alli_nonfastforward_exception();
		};
	}
}

