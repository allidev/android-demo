#pragma once
#include "alli_exception.h"
namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_nonfastforward_exception :
			public alli_exception
		{
		public:
			alli_nonfastforward_exception();
			~alli_nonfastforward_exception();
		};
	}
}

