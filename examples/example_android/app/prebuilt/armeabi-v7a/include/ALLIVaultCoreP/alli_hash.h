#pragma once
#include "ALLIGroupP.h"
#include "ALLIFolderIndex.h"
#include <array>
typedef std::tuple<int, std::string, std::string> group_t;
typedef std::array<void *, 3> running_sharing_group_t;

// specialization of std::hash for group_t
namespace std
{
	template<>
	struct hash <ALLIVaultCore::Engine::ALLIFolderIndex>
	{
		typedef ALLIVaultCore::Engine::ALLIFolderIndex argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& g) const
		{
			std::string localURL = g.get_col2();
			std::string sha1 = g.get_col3();
			result_type const h1(std::hash<std::string>{}(localURL));
			result_type const h2(std::hash<std::string>{}(sha1));
			return h1 ^ (h2 << 1);
		}
	};

	template<>
	struct equal_to<ALLIVaultCore::Engine::ALLIFolderIndex>
	{
		typedef ALLIVaultCore::Engine::ALLIFolderIndex argument_type;
		bool operator()(argument_type const& lhs, argument_type const& rhs) const
		{
			return lhs.get_col2() == rhs.get_col2() &&
				lhs.get_col3() == rhs.get_col3();
		}
	};

	template<>
	struct hash < std::tuple<std::string, std::string, bool>>
	{
		typedef std::tuple<std::string, std::string, bool> argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& g) const
		{
			std::string localURL = std::get<0>(g);
			std::string sha1 = std::get<1>(g);
			result_type const h1(std::hash<std::string>{}(localURL));
			result_type const h2(std::hash<std::string>{}(sha1));
			return h1 ^ (h2 << 1);
		}
	};

	template<>
	struct hash<ALLIVaultCore::Helpers::ALLIGroupP>
	{
		typedef ALLIVaultCore::Helpers::ALLIGroupP argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& g) const
		{
			std::string huname = g.getHostUserName();
			std::string gname = g.getGroupName();
			result_type const h1(std::hash<std::string>{}(huname));
			result_type const h2(std::hash<std::string>{}(gname));
			return h1 ^ (h2 << 1);
		}
	};

	template<>
	struct equal_to<ALLIVaultCore::Helpers::ALLIGroupP>
	{
		typedef ALLIVaultCore::Helpers::ALLIGroupP argument_type;
		bool operator()(argument_type const& lhs, argument_type const& rhs) const
		{
			return lhs.getHostUserName() == rhs.getHostUserName() &&
				lhs.getGroupName() == rhs.getGroupName();
		}
	};

	template<>
	struct hash<group_t>
	{
		typedef group_t argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& g) const
		{
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
			void *ptr1 = rsg[1];
			void *ptr2 = rsg[2];
			auto i1 = reinterpret_cast<std::uintptr_t>(ptr1);
			auto i2 = reinterpret_cast<std::uintptr_t>(ptr2);
			result_type const h1(std::hash<std::uintptr_t>{}
			(i1));
			result_type const h2(std::hash<std::uintptr_t>{}
			(i2));
			return h1 ^ (h2 << 1);
		}
	};
}
