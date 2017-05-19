#pragma once
#include "alli_common.h"
#include <string>

#include "oss_sdk_cpp/oss/oss_client.h"

class AliyunOssPTest;

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_semaphore;
		class alli_mutex;
	}
	namespace Engine
	{
		class AliyunOssP
		{
		public:
			ALLIVAULTCOREP_API AliyunOssP();
			ALLIVAULTCOREP_API AliyunOssP(const std::string &bucket_name);
			ALLIVAULTCOREP_API AliyunOssP(const std::string &endpoint, std::string  &accessKeyID, std::string &accessKeySecret);
			ALLIVAULTCOREP_API ~AliyunOssP();

			ALLIVAULTCOREP_API bool uploadFile(const std::string &filePath, const std::string &serverPath);
			ALLIVAULTCOREP_API bool uploadFile(const boost::filesystem::path &filePath, const std::string &serverPath);
			ALLIVAULTCOREP_API bool downloadFile(const std::string &filePath, const std::string &localPath);
			ALLIVAULTCOREP_API bool downloadFile(const std::string &filePath, const boost::filesystem::path &localPath);
			ALLIVAULTCOREP_API bool reachableViaHttp(const std::string &filePath);
			ALLIVAULTCOREP_API void setOSSCredential(const std::string &keyID, const std::string &keySecret);
			ALLIVAULTCOREP_API void listBuckets();
			ALLIVAULTCOREP_API bool deleteFile(const std::string &serverPath);

		private:
			oss::OssClient client_;
			std::string endpoint_;
			std::string accessKeyID_;
			std::string accessKeySecret_;
			std::string m_bucket_name;
			friend class AliyunOssPTest;

			void Trace(const oss::Status& status, const std::string& funciton_name);
			bool uploadFileImpl(const std::string &filePath, const std::string &serverPath);
			bool multiPartUpload(const std::string &filePath, const std::string &serverPath);
			void uploadOneMultiPartMT(std::list<oss::PartEtag> &part_etags, std::ifstream *stream, const std::string &filePath, int i, const int64_t &file_size, const long long &part_count, const std::string &upload_id, const std::string &serverPath, ALLIVaultCore::Helpers::alli_semaphore &mpu_pool, ALLIVaultCore::Helpers::alli_mutex &mutex_part_etags);
			bool uploadOneMultiPartMTImpl(oss::PartEtag &etag, std::ifstream *stream, const std::string &filePath, int i, const int64_t &file_size, const long long &part_count, const std::string &upload_id, const std::string &serverPath);
		};
	}
}
