#pragma once
namespace ALLIVaultCore
{
	class ALLIMailP
	{
	public:
		ALLIMailP();
		ALLIMailP(const ALLIVaultCore::ALLIMailP &src);
		ALLIMailP &operator=(const ALLIVaultCore::ALLIMailP &src);
		ALLIMailP(ALLIVaultCore::ALLIMailP &&src);
		ALLIMailP &operator=(ALLIVaultCore::ALLIMailP &&src);
		~ALLIMailP();

		std::string getSender() const;
		void setSender(const std::string &src);
		std::chrono::time_point<std::chrono::system_clock> getSentDate() const;
		void setSentDate(const std::chrono::time_point<std::chrono::system_clock> &src);
		boost::filesystem::path getLocalFolderURL() const;
		void setLocalFolderURL(const boost::filesystem::path &src);

	private:
		std::string sender;
		std::chrono::time_point<std::chrono::system_clock> sentDate;
		boost::filesystem::path *localFolderURL;
	};
}

