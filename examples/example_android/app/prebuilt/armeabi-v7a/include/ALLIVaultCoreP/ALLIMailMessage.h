#pragma once

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class ALLIMailMessage
		{
		public:
			ALLIVAULTCOREP_API ALLIMailMessage(const std::string &sender, const std::string &recipient);
			ALLIVAULTCOREP_API ALLIMailMessage(const ALLIVaultCore::Helpers::ALLIMailMessage &src);
			ALLIVAULTCOREP_API ~ALLIMailMessage();

			ALLIVAULTCOREP_API void loadRawData(unsigned char *src, int src_size);
			ALLIVAULTCOREP_API std::string getSenderUserName() const;
			ALLIVAULTCOREP_API std::string getRecipientUserName() const;
			ALLIVAULTCOREP_API std::string getRawData() const;
			ALLIVAULTCOREP_API int getDataSize() const;
			ALLIVAULTCOREP_API void setReadDate(const std::chrono::time_point<std::chrono::system_clock> &src);
			std::chrono::time_point<std::chrono::system_clock> getReadDate() const;
			ALLIVAULTCOREP_API void setSentDate(const std::chrono::time_point<std::chrono::system_clock> &src);
			ALLIVAULTCOREP_API std::chrono::time_point<std::chrono::system_clock> getSentDate() const;

		private:
			std::string _userName;
			std::string _recipientUserName;
			unsigned char *_rawData;
			int _dataSize;
			std::chrono::time_point<std::chrono::system_clock> _readDate, _sentDate;
		};
	}
}

