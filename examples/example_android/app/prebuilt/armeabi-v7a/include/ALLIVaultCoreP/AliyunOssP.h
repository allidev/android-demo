#pragma once
#include "alli_common.h"
#include <string>

#include "oss_sdk_cpp/oss/oss_client.h"

class AliyunOssPTest;

namespace ALLIVaultCore
{
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
		};
	}
}
