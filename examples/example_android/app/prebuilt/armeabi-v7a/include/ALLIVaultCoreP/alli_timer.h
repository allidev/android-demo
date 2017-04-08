#pragma once
#include <iostream>
#include <thread>

namespace ALLIVaultCore
{
	namespace Helpers
	{
		template<class Function, class... Params>
		class alli_timer {
		public:
			explicit alli_timer(Function && f) :
				callback(f),
				m_interval(1),
                m_running(false)
			{
			}

			~alli_timer()
			{
				while (m_running)
				{
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}
			}

			void stopMointor() {
                std::unique_lock<std::mutex> timer_guard(timer_mutex);
				monitorFolder = false;
                std::cout << "stopMonitor called." << std::endl;
			}

			template<class... Args>
			std::thread startMonitor(Args &&... args) {
                std::unique_lock<std::mutex> timer_guard(timer_mutex);
				monitorFolder = true;
                timer_guard.unlock();
                m_running = true;

				return std::thread([=] { doWork(args...); });
			}

			void setInterval(const int internal)
			{
				m_interval = internal;
			}
            
            bool is_running() const
            {
                return m_running;
            }

		private:
			bool monitorFolder;
			Function callback;
			int m_interval;
            std::mutex timer_mutex;
            bool m_running;
            
			template<class... Args>
			void doWork(Args &&... args)
			{
				while (1) {
                    std::unique_lock<std::mutex> timer_guard(timer_mutex);
                    if (!monitorFolder) break;
                    timer_guard.unlock();
                    
					std::cout << "--working---!" << std::endl;
					callback(args...);
					std::this_thread::sleep_for(std::chrono::seconds(m_interval));
					std::cout << "--waking up---" << std::endl;
				}

				std::cout << "monitor stopped!" << std::endl;
                m_running = false;
			}
		};
	}
}
