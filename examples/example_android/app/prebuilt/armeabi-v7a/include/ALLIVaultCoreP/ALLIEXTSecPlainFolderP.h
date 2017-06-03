#pragma once
#include "ALLIEXTFolderP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSecPlainRepoP;
	class ALLIEXTSecPlainFolderP :
		public ALLIEXTFolderP
	{
	public:
		ALLIEXTSecPlainFolderP(ALLIVaultCore::ALLIEXTSecPlainRepoP &plainRepo);
		ALLIEXTSecPlainFolderP(ALLIVaultCore::ALLIEXTSecPlainFolderP const &src);
		ALLIEXTSecPlainFolderP &operator=(ALLIVaultCore::ALLIEXTSecPlainFolderP const &src) = delete;
		ALLIEXTSecPlainFolderP(ALLIVaultCore::ALLIEXTSecPlainFolderP &&src) = delete;
		ALLIEXTSecPlainFolderP &operator=(ALLIVaultCore::ALLIEXTSecPlainFolderP &&src) = delete;
		virtual ~ALLIEXTSecPlainFolderP();

		void monitorPlainFolder(const boost::filesystem::path &plainURL);
		void downloadContactPublicKey(const std::string &contactUserName, bool &dbTimedout);

	protected:
		ALLIVaultCore::Engine::SimpleFolder *plainFolder;

	private:
		friend class ALLIEXTSecPlainRepoP;
		ALLIVaultCore::ALLIEXTSecPlainRepoP *plainRepo;
		// init here and paired with plainRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_local_plain_folder;
		// not init here
		ALLIVaultCore::Helpers::alli_mutex *mutex_plain_repo;
		// init here
		ALLIVaultCore::Helpers::alli_mutex *mutex_encrypt_plain_folder;
		// init here
		ALLIVaultCore::ALLICacheP *syncCache;

		virtual void monitorPlainFolderImpl(const boost::filesystem::path &plainURL);
		void downloadPublicKeysForContacts(void *obj);
		void load_index_db_ex() override;
		void updateTotalBytesUsedImpl() override;
		bool downloadOneFileJsonImpl(const std::string &localPath, std::string &dest) override;
		bool decryptFileToPlainFolder(const std::string &src);
		bool decryptFileToPlainFolder(const std::string &src, const boost::filesystem::path &dest);
		bool trackFolderImpl(const std::string &fullPath) override;
		bool trackFolderImpl(const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &src, const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &dest, bool isDirectory) override;
		bool commitStagedFiles(const std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &files, std::vector<std::string> &messages, std::string &src) override;
		bool commitStagedFilesManual(const std::unordered_map<std::string, std::pair<ALLIVaultCore::Engine::ALLIFileStatusP, std::string>> &files, std::vector<std::string> &messages, std::string &src) override;
		void displayFileHistoryImpl() override;
		void commitStagedFile_impl(const std::string &relativePath, const boost::filesystem::path &filePath, std::unordered_map<std::string, std::string> &filesToUpload);
		void commitStagedFileManual_impl(const std::string &relativePath, const boost::filesystem::path &filePath, const std::string &orig, std::unordered_map<std::string, std::string> &filesToUpload);
		void deleteUploadedFiles(const std::unordered_map<std::string, std::string> &filesToUpload);
		/*
		* It encrypts a file using the relative file name, and saves the encrypted
		* file using the same name to a temp directory.
		* returns true if the operation is successful and false otherwise.
		*/
		bool encryptFileForPlainRepo(const std::string &fileName);
		bool downloadOneFileEx(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow) override;
		void createCacheForServerImpl(std::unordered_map<std::string, ALLIVaultCore::ALLIChangeStatusP> &changeSet) override;
		std::string trackFolderImpl_processLocalFile(const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &src, const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &dest, bool isDirectory);
		void downloadContactPublicKey(const std::string &contactUserName, std::string &contactFullName, bool &dbTimedout);
		std::string convertContact(const std::string &contact);
	};
}

