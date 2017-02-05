/*
 * Copyright (C) ALLI Enterprises, Inc. ALL rights reserved.
 *
 * This file is part of ALLIVault. For full terms see the included
 * COPYING file.
 */
#pragma once
namespace ALLIVaultCore
{
	namespace Helpers
	{
		/**
		 * Class ALLINewMachineStateP. It reports whether a new 
		 * machine sync is in session.
		 */
		class ALLINewMachineStateP
		{
		public:
			bool isNewMachineInSession;

			ALLIVAULTCOREP_API ALLINewMachineStateP();
			~ALLINewMachineStateP();
		};
	}
}

