#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <thread>
#include <queue>
#include <functional>

#include "NPC.h"

class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();
	void addTask(std::function<void()>);
	void SetVal(std::vector<NPC*>& t_npc);
	void continueTask();
private:
	std::vector<std::thread> m_threads;
	std::queue<std::function<void()>> m_tasks;
	std::vector<NPC*> m_npc;
};
#endif // !THREAD_POOL_H

