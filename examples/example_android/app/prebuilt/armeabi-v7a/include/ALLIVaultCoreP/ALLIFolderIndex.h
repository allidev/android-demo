#pragma once

#include "alli_common.h"
#include "alli_types.h"

#include <string>

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIFolderIndex
		{
		public:
			ALLIVAULTCOREP_API ALLIFolderIndex(void);
			ALLIVAULTCOREP_API ~ALLIFolderIndex(void);

			// Column 1 is idx_id
			ALLIVAULTCOREP_API int get_col1() const;
			ALLIVAULTCOREP_API void set_col1(int col1);
			// Column 2 is idx_localURL
			ALLIVAULTCOREP_API std::string get_col2() const;
			ALLIVAULTCOREP_API void set_col2(const std::string &col2);
			// Column 3 is idx_localSHA1
			ALLIVAULTCOREP_API std::string get_col3() const;
			ALLIVAULTCOREP_API void set_col3(const std::string &col3);
			// Column 4 is idx_isEmptyFolder
			ALLIVAULTCOREP_API int get_col4() const;
			ALLIVAULTCOREP_API void set_col4(int col4);
			// Column 5 is idx_st_mode
			ALLIVAULTCOREP_API mode_t get_col5() const;
			ALLIVAULTCOREP_API void set_col5(mode_t col5);
			// Column 6 is idx_st_size
			ALLIVAULTCOREP_API unsigned long long get_col6() const;
			ALLIVAULTCOREP_API void set_col6(unsigned long long col6);
			// Column 7 is idx_st_mtime
			ALLIVAULTCOREP_API time_t get_col7() const;
			ALLIVAULTCOREP_API void set_col7(time_t col7);
			// Column 8 is idx_st_ctime
			ALLIVAULTCOREP_API time_t get_col8() const;
			ALLIVAULTCOREP_API void set_col8(time_t col8);
			// Column 9 is file_state
			ALLIVAULTCOREP_API int get_col9() const;
			ALLIVAULTCOREP_API void set_col9(int col9);

		private:
			int idx_id;							// Column 1
			std::string idx_localURL;		// Column 2
			std::string idx_localSHA1;		// Column 3
			int idx_isEmptyFolder;				// Column 4
			mode_t idx_st_mode;					// Column 5
			unsigned long long idx_st_size;		// Column 6
			time_t idx_st_mtime;				// Column 7
			time_t idx_st_ctime;				// Column 8
			int file_state;                     // Column 9
		};
		bool operator<(const ALLIVaultCore::Engine::ALLIFolderIndex &lhs, const ALLIVaultCore::Engine::ALLIFolderIndex &rhs);
	}
}
