#pragma once

namespace ALLIVaultCore
{
	namespace Engine
	{
		enum class IndexState
		{
			UN_SPECIFIED = 0,
			EMPTY_DIR = (1u << 0),
			DELETED   =	(1u << 1),
		};
	}
}