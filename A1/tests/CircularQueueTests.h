/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef CIRCULARQUEUETESTS_H
#define CIRCULARQUEUETESTS_H
#include <iostream>
#include <cmath>
#include "../include/Utils.h"
#include "TestEnvironment.h"
#include "../include/CircularQueue.h"

std::pair<int, int> circularQueueTestForBookDataStructure() {
    int passedTests = 0;
    TestEnvironment env;
    CircularQueue<Book> bookQueue(10);
    passedTests += _assert_(bookQueue.isEmpty());
    bookQueue.enqueue(env.book10);
    bookQueue.enqueue(env.book9);
    bookQueue.enqueue(env.book8);
    bookQueue.enqueue(env.book7);
    bookQueue.enqueue(env.book6);
    bookQueue.enqueue(env.book5);
    bookQueue.enqueue(env.book4);
    bookQueue.enqueue(env.book3);
    bookQueue.enqueue(env.book2);
    bookQueue.enqueue(env.book1);
    passedTests += _assert_(bookQueue.size() == 10);
    passedTests += _assert_(bookQueue.front().ISBN == "0515118567");
    for (int i = 0; i < 5; i++)
        bookQueue.dequeue();
    passedTests += _assert_(bookQueue.size());
    passedTests += _assert_(bookQueue.front().author == "Michael Johnstone");
    bookQueue.dequeue();
    passedTests += _assert_(bookQueue.size() == 4);
    passedTests += _assert_(bookQueue.front().title == "Until the Sun Dies");
    bookQueue.dequeue();
    passedTests += _assert_(bookQueue.size() == 3);
    bookQueue.dequeue();
    bookQueue.dequeue();
    passedTests += _assert_(bookQueue.size() == 1);
    passedTests += _assert_(bookQueue.front().ISBN == "0486411044");
    bookQueue.dequeue();
    passedTests += _assert_(bookQueue.isEmpty());
    passedTests += _assert_(bookQueue.size() == 0);
    return std::make_pair(passedTests, 12);
}

std::pair<int, int> circularQueueTestForUserDataStructure() {
    int passedTests = 0;
    TestEnvironment env;
    CircularQueue<Patron> userQueue(10);
    passedTests += _assert_(userQueue.isEmpty());
    userQueue.enqueue(env.user10);
    userQueue.enqueue(env.user9);
    userQueue.enqueue(env.user8);
    userQueue.enqueue(env.user7);
    userQueue.enqueue(env.user6);
    userQueue.enqueue(env.user5);
    userQueue.enqueue(env.user4);
    userQueue.enqueue(env.user3);
    userQueue.enqueue(env.user2);
    userQueue.enqueue(env.user1);
    passedTests += _assert_(userQueue.size() == 10);
    passedTests += _assert_(userQueue.front().ID == "user10");
    for (int i = 0; i < 5; i++)
        userQueue.dequeue();
    passedTests += _assert_(userQueue.size() == 5);
    passedTests += _assert_(userQueue.front().name == "Charles Williams");
    userQueue.dequeue();
    passedTests += _assert_(userQueue.size() == 4);
    passedTests += _assert_(userQueue.front().email == "brandon.gillespie@morris.com");
    userQueue.dequeue();
    passedTests += _assert_(userQueue.size() == 3);
    userQueue.dequeue();
    userQueue.dequeue();
    passedTests += _assert_(userQueue.size() == 1);
    passedTests += _assert_(userQueue.front().ID == "user1");
    userQueue.dequeue();
    passedTests += _assert_(userQueue.isEmpty());
    passedTests += _assert_(userQueue.size() == 0);
    return std::make_pair(passedTests, 12);
}

std::pair<int, int> circularQueueTestForGeneralDataStructures() {
    int passedTests = 0;
    CircularQueue<int> intQueue(99999999);
    passedTests += _assert_(intQueue.isEmpty());
    for (int i = 0; i < 99999999; ++i)
        intQueue.enqueue(i);
    passedTests += _assert_(!intQueue.isEmpty());
    passedTests += _assert_(intQueue.size() == 99999999);
    for (int i = 0; i < 99999998; ++i)
        intQueue.dequeue();
    passedTests += _assert_(intQueue.front() == 99999998);
    intQueue.dequeue();
    passedTests += _assert_(intQueue.isEmpty());

    CircularQueue<std::string> strQueue(99999999);
    for (int i = 0; i < 99999999; ++i)
        strQueue.enqueue("# " + std::to_string(i));
    int all_passed = 0;
    for (int i = 0; i < 99999999; ++i) {
        all_passed += _assert_(strQueue.front() == "# " + std::to_string(i));
        strQueue.dequeue();
    }
    passedTests += _assert_(all_passed == 99999999);
    return std::make_pair(passedTests, 6);
}

int circularQueueTests() {
    int passedTests = 0;
    int totalTests = 0;
    std::pair<int, int> r1 = circularQueueTestForBookDataStructure();
    passedTests += r1.first;
    totalTests += r1.second;
    std::pair<int, int> r2 = circularQueueTestForUserDataStructure();
    passedTests += r2.first;
    totalTests += r2.second;
    std::pair<int, int> r3 = circularQueueTestForGeneralDataStructures();
    passedTests += r3.first;
    totalTests += r3.second;
    double grade = static_cast<double>(passedTests * 100) / totalTests;
    grade = std::round(grade * 10) / 10;
    std::cout << "Total tests passed: " << passedTests << " out of " << totalTests << " (" << grade << "%)"  << std::endl;
    return 0;
}

#endif //CIRCULARQUEUETESTS_H
