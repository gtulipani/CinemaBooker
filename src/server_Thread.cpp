#include <iostream>
#include "server_Thread.h"

Thread::Thread() : alive(true) {}

void Thread::start() {
	thread = std::thread(&Thread::run, this);
}

void Thread::join() {
	thread.join();
}

void Thread::stop() {
	alive = false;
}

bool Thread::isDead() {
	return !alive;
}

Thread::~Thread() = default;

Thread::Thread(Thread &&other) noexcept {
	this->thread = std::move(other.thread);
}

Thread &Thread::operator=(Thread &&other) noexcept {
	this->thread = std::move(other.thread);
	return *this;
}

