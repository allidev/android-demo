#pragma once

namespace ALLIVaultCore
{
	namespace Engine
	{
		// this is a native enum class, only to be consumed
		// by a native type
		enum class ALLIFileStatusP
		{
			ALLI_STATUS_CURRENT = 0,

			ALLI_STATUS_WD_NEW =		(1u << 0),
			ALLI_STATUS_WD_MODIFIED =	(1u << 1),
			ALLI_STATUS_WD_DELETED =	(1u << 2),
		};
	}
}
