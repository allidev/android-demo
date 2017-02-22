#pragma once
#include "alli_common.h"
#include <unordered_map>

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	namespace Engine
	{
		class SimpleFolder;
		class ALLIFolderIndex;
	}
	namespace Helpers
	{
		class alli_mutex;
		class alli_semaphore;
	}
	class ALLIFolderP
	{
	public:
		typedef std::function<bool(const std::string &, const boost::filesystem::path &, void *)> DownloadOneFileExCallback;
		bool(*downloadOneFileExPtr) (const std::string &src, const boost::filesystem::path &dest, void *caller);
		void connectDownloadOneFileEx(DownloadOneFileExCallback cb);
		bool(*downloadOneFilePairExPtr) (const std::string &src, const boost::filesystem::path &dest, const std::string &src_key, const boost::filesystem::path &dest_key, void *caller);
		std::string(*retrieveGlobalResourcePtr) (const std::string &key);

		ALLIFolderP();
		ALLIFolderP(const ALLIVaultCore::ALLIFolderP &src);
		~ALLIFolderP();
		// set public scope due to template specialization issue when
		// running this member function in a separate thread.
		void deleteTempFile(const boost::filesystem::path &tempFile);
		ALLIVAULTCOREP_API boost::filesystem::path *getFileURL();
		ALLIVAULTCOREP_API void updateDownloadStatus(std::string &tempFile, long long bytesReceived);
		ALLIVAULTCOREP_API void setUserName(std::string &uname);

	protected:
		std::string username;
		ALLIVaultCore::Engine::SimpleFolder *folder;
		boost::filesystem::path *fileURL;
		long long totalBytesReceived;
		std::unordered_map<std::string, long long> totalBytesRecGroup;
		ALLIVaultCore::Helpers::alli_mutex *rec_group_mutex;
		DownloadOneFileExCallback m_download_one_file_ex_cb;

		std::string updateMessageWithBytesReceivedOSS();
		bool downloadOneFile(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow);
		bool extractServerPathForFile(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow, std::string &svrPath);
		bool createEmptyFolder(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow);
		void open_output_file(FILE **output, const boost::filesystem::path &dest);
		void validate_dest(const boost::filesystem::path &dest);
		void open_input_file(FILE **input, const boost::filesystem::path &src);
		FILE *open_input_file(const boost::filesystem::path &src, int _ShFlag);
		void open_public_key_file(FILE **pubKeyFile, const std::string &uname);
		void open_public_key_file(FILE **pubKeyFile);
		FILE *open_private_key_file(char **priKeyPath, int _ShFlag);
		std::string open_aes_key_file(FILE **aesKeyFile, const boost::filesystem::path &file_path, const std::string &uname);
		void open_aes_key_file(FILE **aesKeyFile, const boost::filesystem::path &file_path);
		void open_aes_key_file(FILE **aesKeyFile, const std::string &fmode, const boost::filesystem::path &file_path);
		bool decryptFile(const boost::filesystem::path &filePathURL, const boost::filesystem::path &aesKeyURL, const boost::filesystem::path &destURL);

	private:
		virtual bool downloadOneFileEx(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow);
	};
}

