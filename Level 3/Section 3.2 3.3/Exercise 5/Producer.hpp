/*
	Level 3.2 3.3: C++ Concurrency
	Problem 5: Barbershop Problem

	Name: Boyu Yang

	File: Producer.hpp
	Description: Producer classes implementation
*/

#pragma once

#include "SyncQueue.hpp"

/// a) Create producer class
class Producer
{
private:
	int id; // producer id
	int chair_num; // total number of chairs
	std::chrono::steady_clock::time_point close_time; // barbershop closing time
	SynchronisedQueue<std::string>* queue; // pointer to the shared queue

public:
	Producer(int id, int chair_num, std::chrono::steady_clock::time_point& close_time, SynchronisedQueue<std::string>* queue)
		: id{ id }, chair_num{ chair_num }, close_time{ close_time }, queue{ queue }{};
	void operator()() {
		int client_id = 1;
		// when the barbershop is open
		while (std::chrono::steady_clock::now() < close_time) {
			std::string str{ "customer " + std::to_string(client_id) };
			if (queue->Size() < chair_num) {
				queue->Enqueue(str);
				if ((queue->Size() > 0) and (client_id > 1)) { 
					std::cout << str << " is " << queue->Size() << "th in line for the cut" << std::endl; 
				}
			}
			else {
				std::cout << str << " is leaving because the barber shop is full..." << std::endl;
			};
			// next customer arrives in 10 seconds
			std::this_thread::sleep_for(std::chrono::seconds(10));
			client_id++;
		}
	}
};
