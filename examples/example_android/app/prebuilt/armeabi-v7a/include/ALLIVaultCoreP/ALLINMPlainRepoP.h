#pragma once
#include "ALLINMRepoP.h"

namespace ALLIVaultCore
{
	class ALLINMPlainRepoP :
		public ALLINMRepoP
	{
	public:
		ALLIVAULTCOREP_API ALLINMPlainRepoP();
		ALLINMPlainRepoP(const ALLIVaultCore::ALLINMPlainRepoP &src);
		ALLIVAULTCOREP_API ~ALLINMPlainRepoP();
		ALLIVAULTCOREP_API bool processLocalChangedFilesWithCommitMessage(const std::unordered_map<std::string, git_status_t> &files, std::vector<std::string> &messages);
		ALLIVAULTCOREP_API void setPlainURL(const boost::filesystem::path &plainURL);
		ALLIVAULTCOREP_API boost::filesystem::path getPlainURL();

	protected:
		virtual void setRepoEx(ALLIVaultCore::Engine::SimpleRepositoryP &repo) override;
		// overloading member functions from the base class
		virtual bool moveRepositoryEx(const boost::filesystem::path &localURL, bool checkRemoteRef) override;

	private:
		boost::filesystem::path *plainURL;
		ALLIVaultCore::Engine::SimpleRepositoryP *plainRepoP;
	};

}

