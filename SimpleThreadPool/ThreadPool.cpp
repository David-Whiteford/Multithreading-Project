#include <ThreadPool.h>

ThreadPool::ThreadPool() {
	

}

ThreadPool::~ThreadPool() {}




void ThreadPool::SetVal(std::vector<NPC*>& t_npc)
{
	m_npc = t_npc;
}

void ThreadPool::addTask(std::function<void()> t_functionToAdd)
{
	std::mutex* addTaskLock = new std::mutex;
	addTaskLock->lock();
	m_tasks.push(t_functionToAdd);
	addTaskLock->unlock();
}

void ThreadPool::continueTask(ThreadPool& t_threadPool)
{
	std::function<void()> function;
	while (true)
	{
		std::unique_lock<std::mutex> lock(m_functionLock);
		m_data.wait(lock, [this] {return m_tasks.empty() == false || m_endPool == false; });
		if (m_endPool == false || m_tasks.empty() == true)
		{
			return;
		}
		function = m_tasks.front();
		m_tasks.pop();
	}
	function();
}

void ThreadPool::completedTasks()
{
	std::mutex* completedTaskLock = new std::mutex;
	completedTaskLock->lock();
	m_endPool = false;
	completedTaskLock->unlock();

	m_data.notify_all();
}



