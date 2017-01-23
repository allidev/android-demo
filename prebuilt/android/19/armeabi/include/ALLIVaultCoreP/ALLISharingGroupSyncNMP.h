#pragma once
#include "ALLISharingGroupSyncP.h"
#include "alli_event.h"

namespace boost
{
	namespace signals2
	{
		class connection;
	}
}
namespace ALLIVaultCore
{
	namespace FrontEnd
	{
		class ALLIExistingUserP;
	}
	namespace Helpers
	{
		class alli_semaphore;
		class ALLIStatusP;
		class ALLINewMachineStateP;
		class ALLISharingGroupSyncNMP :
			public ALLISharingGroupSyncP
		{
		public:
			typedef ALLIVaultCore::FrontEnd::mach_new_status_updated_event::slot_type MachNewStatusUpdatedSlotType;

			ALLISharingGroupSyncNMP(ALLIVaultCore::FrontEnd::ALLIExistingUserP &eu);
			~ALLISharingGroupSyncNMP();

			void initNMState();
			void setNMState(ALLIVaultCore::Helpers::ALLINewMachineStateP *src);
			void setSharingCurSemap(ALLIVaultCore::Helpers::alli_semaphore *src);
			void setSharingALLIGroupList(std::vector<ALLIVaultCore::Helpers::ALLIGroupP> *src);
			void processSharingSyncNM(const std::string &hostUserName, const std::string &groupName, ALLIVaultCore::Helpers::ALLIStatusP &alli_status, int counter);
			boost::signals2::connection connectMachNewStatusUpdated(const MachNewStatusUpdatedSlotType &slot);

		private:
			//ALLIVaultCore::FrontEnd::ALLIExistingUserP &existUser;
			ALLIVaultCore::Helpers::ALLINewMachineStateP *nmState;
			// this semaphore is used to sync for new machine and sharing groups
			// when the user is a guest user.
			ALLIVaultCore::Helpers::alli_semaphore *sharingCurSemap;
			ALLIVaultCore::FrontEnd::mach_new_status_updated_event machNewStatusUpdated;

			void OnMachNewStatusUpdated(ALLIVaultCore::FrontEnd::new_machine_event_args &e);
			void setSharingUserNameSync(const std::string &hostUserName, const std::string &groupName);
			void batchActionsForSharingSync(const std::string &hostUserName, const std::string &groupName, ALLIVaultCore::Helpers::ALLIStatusP &alli_status, int counter);
			void setSharingHostUserNameSync(const std::string &guestUserName, const std::string &groupName);
			void setSharingGuestUserNameSync(const std::string &hostUserName, const std::string &hostFullName, const std::string &groupName);
			void setSharingGuestUserNameSync(const std::string &hostUserName, const std::string &groupName);
			void attachToNativeEventHandlerForCloneTransferUpdate();
			void copyFilesFromServerToSharingPlainFolderImpl(void *obj) override;
			void copyFilesFromServerToSharingPlainFolderExImpl(const boost::filesystem::path &sharingPlainFolderURL) override;
			void monitorSharingSyncPlainRepoImpl(const std::string &hostUserName) override;
			void monitorSharingSyncEncryptedRepoImpl(const std::string &hostUserName) override;
			void monitorSharingSyncPlainFolderAtURLImpl(const boost::filesystem::path &sharingPlainFolder, const std::string &hostUserName) override;
		};
	}
}

