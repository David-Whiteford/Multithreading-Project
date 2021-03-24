#include <ThreadPool.h>

ThreadPool::ThreadPool() {
	int cores = std::thread::hardware_concurrency() - 1;
	for (int i = 0; i < cores; i++)
	{
		m_threads.push_back(std::thread());
		// Need to add a function thats listens for 
		// Tasks to be added to the queue
		/*addTask(AddNums());*/
	}

}

ThreadPool::~ThreadPool() {}


void ThreadPool::addTask(std::function<void()> task) 
{
	m_tasks.push(task);
}

//std::function<void()> ThreadPool::AddNums()
//{
//	int numVal = 0;
//	for (int i = 0; i < 100000; i++)
//	{
//		for (int j = 0; j < 100000; j++)
//		{
//			numVal = i + j;
//			std::cout << "Num Val: " << numVal << std::endl;
//		}
//	}
//	return AddNums();
//}
