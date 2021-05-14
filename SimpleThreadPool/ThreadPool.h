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
	void SetVal(std::vector<NPC*>& t_npc);
	void addTask(std::function<void()> t_functionToAdd);
	void continueTask(ThreadPool& t_treadPool);
	void completedTasks();
private:
	std::queue<std::function<void()>> m_tasks;
	std::vector<NPC*> m_npc;
	std::mutex m_functionLock;
	std::condition_variable m_data;
	bool m_acceptFunctions = false;
	std::vector<std::thread> m_threads;
};
#endif // !THREAD_POOL_H

