#ifndef __SERVER_THREAD_H__
#define __SERVER_THREAD_H__

#include <thread>

class Thread {
private:
	std::thread thread;

protected:
	bool alive;

public:
	Thread();

	void start();

	void join();

	void stop();

	virtual void run() = 0;

	bool isDead();

	virtual ~Thread();

	Thread(const Thread &) = delete;

	Thread &operator=(const Thread &) = delete;

	Thread(Thread &&other) noexcept;

	Thread &operator=(Thread &&other) noexcept;
};


#endif //__SERVER_THREAD_H__
