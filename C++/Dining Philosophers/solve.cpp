#include <array>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include <queue>

bool isDinner = false;
class Compare
{
public:
	bool operator() (std::pair<int, int> &a, std::pair<int, int> &b)
	{
		return a.second < b.second;
	}
};


class Fork {
	int ID;
public:
	std::mutex mutex;
	Fork(int _ID) : ID(_ID)
	{}
};

class Waiter {
	std::array<Fork, 5> forks
	{
	   {
		  { 0 },
		  { 1 },
		  { 2 },
		  { 3 },
		  { 4 },
	   }
	};
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> PQ;
	std::mutex m1;
public:
	void askForForks(int ID,int eatingCTR) 
	{
		std::pair<int, int> newInQueue{ ID, eatingCTR };

		m1.lock();
		//philosopher is added to the queue - he wants to eat
		PQ.push(newInQueue);
		m1.unlock();

		while (PQ.top().first != ID)
		{
			//philosopher is waiting for his turn
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		m1.lock();
		//philosopher have access to forks - he is removed from the queue
		PQ.pop();
		m1.unlock();

		//philosopher gets forks - he starts eating
		forks[(ID + 1) % 5].mutex.lock();
		forks[ID].mutex.lock();
	}
	void releaseForks(int ID)
	{
		//philosopher release forks - he stops eating
		forks[(ID + 1) % 5].mutex.unlock();
		forks[ID].mutex.unlock();
	}
	// void initQueue() 
	// {
	// 	for (int i = 0; i < 4; i++) 
	// 	{
	// 		PQ.push(std::make_pair(0, 0));
	// 	}
	// }
};


class Philosopher {
private:
	int ID;
	int eatingCTR = 0;
	Waiter &w;
public:
	std::thread t;
	Philosopher(int _ID, Waiter &_w) :
		ID(_ID), w(_w), t(&Philosopher::dine,this)
	{}
	~Philosopher()
	{
		if(t.joinable())
			t.join();
	}
	void dine() 
	{
		do 
		{
			think();
			eat();
		} while (isDinner);
	}
	void eat() 
	{
		//request forks
		w.askForForks(ID, eatingCTR);
		printf("%d is eating\n", ID);

		//simulating eating time for philosopher
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50));
		//increment the number of times he ate
		incrementCTR();
		printf("%d stopped eating\n", ID);
		//release forks to let others eat
		w.releaseForks(ID);
	}
	void think() 
	{
		printf("%d is thinking\n",ID);
		//simulating thinking time for philosopher
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50));
	}
	void incrementCTR() 
	{
		this->eatingCTR++;
	}
	int getCTR() 
	{
		return this->eatingCTR;
	}
	int getID() 
	{
		return this->ID;
	}
};

int main() {
	Waiter w;
	srand(time(NULL));

	isDinner = true;
	std::array<Philosopher, 5> philosophers
	{
	   {
		  { 0, w },
		  { 1, w },
		  { 2, w },
		  { 3, w },
		  { 4, w },
	   }
	};
	
	//simulating time of whole dinner
	std::this_thread::sleep_for(std::chrono::seconds(rand() % 15));
	isDinner = false;
	
	for (int i = 0; i < 5; i++) 
	{
		philosophers[i].~Philosopher();
	}
	std::cout << "\n";
	for (int i = 0; i < 5; i++)
	{
		std::cout << philosophers[i].getID() << " ate " << philosophers[i].getCTR() << " times\n";
	}
}