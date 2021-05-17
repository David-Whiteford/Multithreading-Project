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
	//set up the tasks and completed tasks functions
	void addTask(std::function<void()> t_functionToAdd);
	void completedTasks();
	std::vector<std::thread> m_threads;

private:
	//set up the tasks, function lock and data and accept function  
	std::queue<std::function<void()>> m_tasks;
	std::mutex m_functionLock;
	std::condition_variable m_data;
	bool m_acceptFunctions = false;
	//sets the continue task as a static function
	static void continueTask(ThreadPool& t_threadPool);
};
#endif // !THREAD_POOL_H

