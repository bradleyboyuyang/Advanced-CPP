/*
    Level 3.2 3.3: C++ Concurrency
    Problem 5: Barbershop Problem

    Name: Boyu Yang

    Problem objective:
    Consider the following problem:
    “A barbershop consists of a waiting room with n chairs. There is one barber chair in the room. The barber
    goes to sleep if there are no customers in the room. If a customer enters the barber shop and all chairs are
    occupied then the customer leaves the shop. If the barber is busy and there are chairs available then the
    customer occupies one of these free chairs. If the barber is asleep he is woken by a customer.”
    The main events in this example are:
    • Arrival of a client.
    • Starting of a service for a client.
    • Client leaves barber shop after having received service.
    • Client leaves the barber shop if it is full.
    • The barber waits (sleeps or does something else) if there are no clients waiting for service.
    The objective of this exercise is to write a program to coordinate the barber and the customers using the
    Producer-Consumer pattern.
    Answer the following questions:
    a) Create producer and consumer classes. Producers arrive every 10 seconds. There is one customer.
    b) Reuse the class for synchronising queues.
    c) Test the code.
*/

#include "Producer.hpp"
#include "Consumer.hpp"

int main() {
    /// c) Test the code.
    // creating shared queue and mutex
    SynchronisedQueue<std::string> queue;

    // Simulate the barbershop for a certain amount of time, e.g. 120s
    std::chrono::steady_clock::time_point close_time{ std::chrono::steady_clock::now() + std::chrono::seconds(120) };

    // producer thread
    int chair_num = 3;
    Producer p(1, chair_num, close_time, &queue);
    std::thread producer(p);

    // consumer thread
    int cut_time = 27; // amount of time to finish hair cutting
    Consumer c(1, cut_time, close_time, &queue);
    std::thread consumer(c);

    // wait the threads to finish
    producer.join();
    consumer.join();

}