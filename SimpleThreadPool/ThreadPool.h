#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <cassert>
#include <mutex>
#include "NPC.h"

class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();

	void addTask(std::function<void()> t_functionToAdd);
	void completedTasks();
	std::vector<std::thread> m_threads;

private:
	std::queue<std::function<void()>> m_tasks;
	std::mutex m_functionLock;
	std::condition_variable m_data;
	bool m_acceptFunctions = false;
	static void continueTask(ThreadPool& t_threadPool);
};
#endif // !THREAD_POOL_H

