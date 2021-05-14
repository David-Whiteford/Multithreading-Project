#include <ThreadPool.h>

ThreadPool::ThreadPool() :m_tasks(), m_functionLock(),m_data(), m_acceptFunctions(true){
	int cores = std::thread::hardware_concurrency() - 1;
	for (int i = 0; i < cores; i++)
	{
		m_threads.push_back(std::thread());
	}
	
}

ThreadPool::~ThreadPool() 
{
	completedTasks();
}




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

void ThreadPool::continueTask(ThreadPool& t_treadPool)
{
	std::function<void()> function;
	while (true)
	{
		std::unique_lock<std::mutex> lock(m_functionLock);
		m_data.wait(lock, [this]() {return m_tasks.empty() == false || m_acceptFunctions == false; });
		if (m_acceptFunctions == false || m_tasks.empty() == true)
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
	m_acceptFunctions = false;
	completedTaskLock->unlock();
	m_data.notify_all();
}



