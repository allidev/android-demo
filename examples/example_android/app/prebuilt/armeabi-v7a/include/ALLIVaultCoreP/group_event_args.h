#pragma once
#include "alli_event_args.h"
namespace ALLIVaultCore
{
	namespace Helpers
	{
		class ALLIGroupP;
	}
	class group_event_args :
		public ALLIVaultCore::Helpers::alli_event_args
	{
	public:
		group_event_args();
		~group_event_args();

		void setGroupInvites(std::vector<ALLIVaultCore::Helpers::ALLIGroupP> &&src);

	private:
		std::vector<ALLIVaultCore::Helpers::ALLIGroupP> m_groupInvites;

		std::string to_string_impl() const override;
	};
}

