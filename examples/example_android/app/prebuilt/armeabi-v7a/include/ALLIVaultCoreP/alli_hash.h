#pragma once
#include "ALLIGroupP.h"
#include <array>
typedef std::tuple<int, std::string, std::string> group_t;
typedef std::array<void *, 3> running_sharing_group_t;

// specialization of std::hash for group_t
namespace std
{
	template<>
	struct hash<ALLIVaultCore::Helpers::ALLIGroupP>
	{
		typedef ALLIVaultCore::Helpers::ALLIGroupP argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& g) const
		{
			return 0;
		}
	};

	template<>
	struct equal_to<ALLIVaultCore::Helpers::ALLIGroupP>
	{
		typedef ALLIVaultCore::Helpers::ALLIGroupP argument_type;
		bool operator()(argument_type const& lhs, argument_type const& rhs) const
		{
			return false;
		}
	};

	template<>
	struct hash<group_t>
	{
		typedef group_t argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& g) const
		{
			result_type const h0(std::hash<int>{}
			(std::get<0>(g)));
			result_type const h1(std::hash<std::string>{}
			(std::get<1>(g)));
			result_type const h2(std::hash<std::string>{}
			(std::get<2>(g)));
			return h1 ^ (h2 << 1);
		}
	};

	template<>
	struct hash<running_sharing_group_t>
	{
		typedef running_sharing_group_t argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& rsg) const
		{
			void *ptr0 = rsg[0];
			void *ptr1 = rsg[1];
			void *ptr2 = rsg[2];
			auto i0 = reinterpret_cast<std::uintptr_t>(ptr0);
			auto i1 = reinterpret_cast<std::uintptr_t>(ptr1);
			auto i2 = reinterpret_cast<std::uintptr_t>(ptr2);
			result_type const h0(std::hash<std::uintptr_t>{}
			(i0));
			result_type const h1(std::hash<std::uintptr_t>{}
			(i1));
			result_type const h2(std::hash<std::uintptr_t>{}
			(i2));
			return h1 ^ (h2 << 1);
		}
	};
}
