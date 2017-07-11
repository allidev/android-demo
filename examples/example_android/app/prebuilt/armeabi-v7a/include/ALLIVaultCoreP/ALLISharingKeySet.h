#pragma once

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLISharingKeySet
		{
		public:
			ALLISharingKeySet();
			~ALLISharingKeySet();

			void setServerSha1(const std::string &serverSha1);
			std::string getServerSha1() const;
			void setKeyUser(const std::string &keyUser);
			std::string getKeyUser() const;
			void setAESKeyURL(const std::string &aesKeyURL);
			std::string getAESKeyURL() const;

		private:
			std::string m_serverSha1;
			std::string m_keyUser;
			std::string m_aesKeyURL;
		};
		bool operator==(ALLIVaultCore::Engine::ALLISharingKeySet const &lhs, ALLIVaultCore::Engine::ALLISharingKeySet const &rhs);
	}
}

namespace std
{
	template<>
	struct hash <ALLIVaultCore::Engine::ALLISharingKeySet>
	{
		typedef ALLIVaultCore::Engine::ALLISharingKeySet argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& g) const
		{
			std::string serverSha1 = g.getServerSha1();
			std::string keyUser = g.getKeyUser();
			result_type const h1(std::hash<std::string>{}(serverSha1));
			result_type const h2(std::hash<std::string>{}(keyUser));
			return h1 ^ (h2 << 1);
		}
	};

	template<>
	struct equal_to<ALLIVaultCore::Engine::ALLISharingKeySet>
	{
		typedef ALLIVaultCore::Engine::ALLISharingKeySet argument_type;
		bool operator()(argument_type const& lhs, argument_type const& rhs) const
		{
			return lhs.getServerSha1() == rhs.getServerSha1() &&
				lhs.getKeyUser() == rhs.getKeyUser();
		}
	};
}
