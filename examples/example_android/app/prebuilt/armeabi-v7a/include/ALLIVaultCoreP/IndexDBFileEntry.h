#pragma once

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace libgit2cpp
{
	class signature;
	class tree_entry;
}

namespace ALLIVaultCore
{
	namespace Engine
	{
		class IndexDBFileEntry
		{
		public:
			IndexDBFileEntry(std::string &cmtSha1, libgit2cpp::signature &cmtter);
			ALLIVAULTCOREP_API IndexDBFileEntry(const ALLIVaultCore::Engine::IndexDBFileEntry &src);
			ALLIVAULTCOREP_API ~IndexDBFileEntry();

			void setTreeEntry(const libgit2cpp::tree_entry &src);
			ALLIVAULTCOREP_API libgit2cpp::tree_entry getTreeEntry() const;
			ALLIVAULTCOREP_API libgit2cpp::signature getSignature() const;
			ALLIVAULTCOREP_API std::string getCommitSHA1() const;

		private:
			std::string commitSha1;
			libgit2cpp::signature *committer;
			libgit2cpp::tree_entry *entry_;
			boost::filesystem::path *entryPath;
		};
	}
}

