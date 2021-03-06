#include <ThreadPool.h>

ThreadPool::ThreadPool() :m_tasks(), m_functionLock(),m_data(), m_acceptFunctions(true){
	//set up all threadsa adn store
	int cores = std::thread::hardware_concurrency() - 1;
	for (int i = 0; i < cores; i++)
	{
		m_threads.push_back(std::thread(continueTask,std::ref(*this)));
	}
}

ThreadPool::~ThreadPool() {
	completedTasks();
}

void ThreadPool::addTask(std::function<void()> t_functionToAdd)
{
	//add a task to the task vector
	std::unique_lock<std::mutex> lock(m_functionLock);
	m_tasks.push(t_functionToAdd);
	m_data.notify_one();
}

void ThreadPool::continueTask(ThreadPool& t_threadPool)
{
	std::function<void()> function = std::function<void()>();
	while (true)
	{
		{
			std::unique_lock<std::mutex> lock(t_threadPool.m_functionLock);
			t_threadPool.m_data.wait(lock, [&]() {return t_threadPool.m_tasks.empty() == false || t_threadPool.m_acceptFunctions == false; });
			//if the function is accepting and thread pool is empty then do nothing
			if (t_threadPool.m_acceptFunctions == false || t_threadPool.m_tasks.empty() == true)
			{
				return;
			}
			//otherwise perform the task
			function = t_threadPool.m_tasks.front();
			t_threadPool.m_tasks.pop();
		}
		function();
	}
	
}

void ThreadPool::completedTasks()
{
	//prevent the aceepting of any more functions and nofify all data
	std::unique_lock<std::mutex> lock(m_functionLock);
	m_acceptFunctions = false;
	m_data.notify_all();
	//join all threads and clear vector after to prevent slow down
	for (std::thread& all_threads : m_threads)
	{
		all_threads.join();
	}
	m_threads.clear();
}



