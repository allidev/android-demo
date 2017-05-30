#pragma once
#include "alli_event.h"
namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_mutex;
		class ALLIGroupP;
		class alli_event_args;
	}
	class ALLIGroupInvitesP
	{
	public:
		typedef ALLIVaultCore::Helpers::alli_event::slot_type GroupInvitesReceivedSlotType;

		ALLIGroupInvitesP(const std::string &guestName);
		~ALLIGroupInvitesP();

		void checkGroupInvites(void *obj);
		boost::signals2::connection connectGroupInvitesReceived(const GroupInvitesReceivedSlotType &slot);
		bool empty() const;
		std::vector<ALLIVaultCore::Helpers::ALLIGroupP> getGroupInvites() const;
		bool markAnInviteAsAccepted(const ALLIVaultCore::Helpers::ALLIGroupP &src);
		bool removeAGroup(const ALLIVaultCore::Helpers::ALLIGroupP &target);

	private:
		int timerCount;
		int error_code;
		ALLIVaultCore::Helpers::alli_mutex *invites_mutex;
		std::vector<ALLIVaultCore::Helpers::ALLIGroupP> groupInvites;
		ALLIVaultCore::Helpers::alli_mutex *mutex_timer;
		std::string guestUserName;
		ALLIVaultCore::Helpers::alli_event GroupInvitesReceived;

		void increaseTimerCount();
		void decreaseTimerCount();
		bool checkGroupInvitesEx();
		void OnGroupInvitesReceived(ALLIVaultCore::Helpers::alli_event_args &e);
		void OnGroupInvitesReceived(ALLIVaultCore::Helpers::alli_event_args &&e);
	};
}

