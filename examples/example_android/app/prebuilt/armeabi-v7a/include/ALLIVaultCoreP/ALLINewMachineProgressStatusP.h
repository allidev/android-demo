#pragma once

namespace ALLIVaultCore
{
	namespace Helpers
	{
		enum class ALLINMStatusP
		{
			NM_Status_Null = 0,

			NM_Status_Sync_Start = 1,
			NM_Status_Sync_Clone_End,
			NM_Status_Sync_PostClone_StepOne,
			NM_Status_Sync_PostClone_StepTwo,
			NM_Status_Sync_Finish,

			NM_Status_Mailbox_Start,
			NM_Status_Mailbox_Clone_End,
			NM_Status_Mailbox_PostClone_StepOne,
			NM_Status_Mailbox_PostClone_StepTwo,
			NM_Status_Mailbox_Finish,

			NM_Status_Sharing_Total,

			NM_Status_SharingCurrent_Start,
			NM_Status_SharingCurrent_Clone_End,
			NM_Status_SharingCurrent_PostClone_StepOne,
			NM_Status_SharingCurrent_PostClone_StepTwo,
			NM_Status_SharingCurrent_Finish,
		};
	}
}
