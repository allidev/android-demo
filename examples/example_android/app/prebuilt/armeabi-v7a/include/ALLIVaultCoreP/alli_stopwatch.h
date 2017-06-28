#pragma once

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_stopwatch
		{
		public:
			alli_stopwatch();
			~alli_stopwatch();

			void Start();
			void Stop();
			void Restart();
			long long ElapsedMilliseconds() const;

		private:
			std::chrono::time_point<std::chrono::system_clock> m_stopwatch;
			long long m_elapsed;
		};
	}
}
