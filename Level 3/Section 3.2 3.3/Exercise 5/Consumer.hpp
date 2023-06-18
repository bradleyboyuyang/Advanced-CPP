/*
	Level 3.2 3.3: C++ Concurrency
	Problem 5: Barbershop Problem

	Name: Boyu Yang
	
	File: Consumer.hpp
	Description: Consumer classes implementation
*/

#pragma once

#include "SyncQueue.hpp"

/// a) Create consumer class
class Consumer
{
private:
	int id; // consumer id
	int cut_time; // time to cut the hair
	std::chrono::steady_clock::time_point close_time; // barbershop closing time
	SynchronisedQueue<std::string>* queue; // pointer to the shared queue

public:
	Consumer(int id, int cut_time, std::chrono::steady_clock::time_point& close_time, SynchronisedQueue<std::string>* queue)
		: id{ id }, cut_time{ cut_time }, close_time{ close_time }, queue{ queue }{};

	void operator()() {
		// barber closes the barber shop at close_time
		while (std::chrono::steady_clock::now() < close_time) {
			if (queue->Size() > 0) {
				std::string customer{ queue->Dequeue() };
				std::cout << customer << " has been taken in by the barber" << std::endl;

				// barber takes cut_time seconds to cut hair
				std::this_thread::sleep_for(std::chrono::seconds(cut_time));
				std::cout << customer << " is leaving like a new person" << std::endl;
			}
		}
		std::cout << "barber has finished his day: " << queue->Size() << " clients leave without being served" << std::endl;
	}
};