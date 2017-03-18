#pragma once
#include "ALLISharingP.h"
#include "ALLINetworkStatus.h"
#include "alli_event.h"
#include <unordered_map>

namespace ALLIVaultCore
{
	class ALLISharingExtP :
		public ALLISharingP
	{
	public:
		void(*filePermPtr) (const boost::filesystem::path &);
		bool(*dlPublicKey) (char **rawdata, unsigned int &fileSize, const std::string &guestUserName);
		ALLIVaultCore::Engine::NetworkStatus(*chkHost)();
		typedef ALLIVaultCore::Helpers::transfer_progress_event::slot_type transferSlotType;

		ALLISharingExtP();
		ALLISharingExtP(const ALLIVaultCore::ALLISharingExtP &src);
		virtual ~ALLISharingExtP();

		void openServerRepository(const std::string &remoteURL);
		bool cloneFromRemoteRepoToURL(const boost::filesystem::path &localURL, ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
		ALLIVAULTCOREP_API void moveRepositoryToURL(const boost::filesystem::path &localURL, bool checkRemoteRef);
		ALLIVAULTCOREP_API void load_guest_list_db();
		ALLIVAULTCOREP_API void downloadGroupMemberPublicKeys();
		bool minimumFilesFound();
		bool processLocalChangedFiles(const std::unordered_map<std::string, git_status_t> &files, std::vector<std::string> &messages);

		// helper methods
		boost::filesystem::path extractSharingWorkDirWithRepoType(const std::string &repoType);
		ALLIVAULTCOREP_API boost::signals2::connection connect(const transferSlotType &slot);

	protected:
		int init_fail_count;

		bool commitStagedFilesLocallyWithMessage(std::vector<std::string> &messages);
		virtual void moveRepositoryToURLImpl(const boost::filesystem::path &localURL, bool checkRemoteRef);
		bool copyToPlainRepo_prepare_folder(const boost::filesystem::path &plainURL);
		void decryptFilesToPlainRepo(const boost::filesystem::path &plainURL, bool &memberDeleted);
		std::unique_ptr<libgit2cpp::repository> copyToPlainRepo_init_raw_repo(const boost::filesystem::path &plainURL);
		std::unique_ptr<ALLIVaultCore::ALLISharingExtP> copyToPlainRepo_create_plain_repo(const boost::filesystem::path &plainURL);

	private:
		bool _cred_acquire_called;
		const char *_remote_user;
		char *_remote_pass;
		char *_publickey;
		const char *_privatekey;
		bool checkoutProgressCalled;
		bool transferProgressCalled;
		size_t total_bytes;
		unsigned int total_obj, comp_obj;
		ALLIVaultCore::Helpers::transfer_progress_event CloneTransferUpdate;

		bool publicKeyExists(const std::string &userName);
		bool createSharingRepositoryOnCurrentMachine(const boost::filesystem::path &localURL, bool checkRemoteRef);
		int load_guest_list_db_ex(const boost::filesystem::path &guestListDBURL);
		void downloadGuestPublicKey(const std::string &guestUserName);
		void writePublicKeyToFile(char *rawdata, unsigned int fileSize, const std::string &guestUserName);
		int gldb_query_callback(sqlite3_stmt *sqlstmt);
		int cred_acquire_cb(git_cred **cred,
			const char *url,
			const char *user_from_url,
			unsigned int allowed_types,
			void *payload);
		void cloneTransferProgress(const git_transfer_progress *progress);
		void checkoutProgressBlock(std::string *path, int completedSteps, int totalSteps);
		bool decryptFile(const std::string &fileName, const boost::filesystem::path &plainURL, bool &memberDeleted);
		bool decryptFile_set_src_and_dest(boost::filesystem::path &srcDir, boost::filesystem::path &srcPath, FILE **input, FILE **output, FILE *& priKeyFile, char **priKeyPath, const std::string &fileName, const boost::filesystem::path &plainURL);
		bool decryptFile_getAESKey(const boost::filesystem::path &srcDir, const boost::filesystem::path &srcPath, bool &memberDeleted, FILE **aesKeyFile, bool &membershipRevoked);
		boost::filesystem::path get_aes_key_path(const boost::filesystem::path &srcDir, const boost::filesystem::path &srcPath);
		void decryptFile_on_close(FILE *priKeyFile, FILE *input, FILE *output, char *priKeyPath, bool &membershipRevoked);
	};
}

