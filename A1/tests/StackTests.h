/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef STACKTESTS_H
#define STACKTESTS_H
#include <iostream>
#include <cmath>
#include "../include/Utils.h"
#include "TestEnvironment.h"
#include "../include/Stack.h"

std::pair<int, int> stackTestForBookDataStructure() {
    int passedTests = 0;
    TestEnvironment env;
    Stack<Book> bookStack;
    passedTests += _assert_(bookStack.isEmpty());
    bookStack.push(env.book1);
    bookStack.push(env.book2);
    bookStack.push(env.book3);
    bookStack.push(env.book4);
    bookStack.push(env.book5);
    bookStack.push(env.book6);
    bookStack.push(env.book7);
    bookStack.push(env.book8);
    bookStack.push(env.book9);
    bookStack.push(env.book10);
    passedTests += _assert_(bookStack.size() == 10);
    passedTests += _assert_(bookStack.top().ISBN == "0515118567");
    for (int i = 0; i < 5; i++)
        bookStack.pop();
    passedTests += _assert_(bookStack.size());
    passedTests += _assert_(bookStack.top().author == "Michael Johnstone");
    bookStack.pop();
    passedTests += _assert_(bookStack.size() == 4);
    passedTests += _assert_(bookStack.top().title == "Until the Sun Dies");
    bookStack.pop();
    passedTests += _assert_(bookStack.size() == 3);
    bookStack.pop();
    bookStack.pop();
    passedTests += _assert_(bookStack.size() == 1);
    passedTests += _assert_(bookStack.top().ISBN == "0486411044");
    bookStack.pop();
    passedTests += _assert_(bookStack.isEmpty());
    passedTests += _assert_(bookStack.size() == 0);
    return std::make_pair(passedTests, 12);
}

std::pair<int, int> stackTestForUserDataStructure() {
    int passedTests = 0;
    TestEnvironment env;
    Stack<Patron> userStack;
    passedTests += _assert_(userStack.isEmpty());
    userStack.push(env.user1);
    userStack.push(env.user2);
    userStack.push(env.user3);
    userStack.push(env.user4);
    userStack.push(env.user5);
    userStack.push(env.user6);
    userStack.push(env.user7);
    userStack.push(env.user8);
    userStack.push(env.user9);
    userStack.push(env.user10);
    passedTests += _assert_(userStack.size() == 10);
    passedTests += _assert_(userStack.top().ID == "user10");
    for (int i = 0; i < 5; i++)
        userStack.pop();
    passedTests += _assert_(userStack.size() == 5);
    passedTests += _assert_(userStack.top().name == "Charles Williams");
    userStack.pop();
    passedTests += _assert_(userStack.size() == 4);
    passedTests += _assert_(userStack.top().email == "brandon.gillespie@morris.com");
    userStack.pop();
    passedTests += _assert_(userStack.size() == 3);
    userStack.pop();
    userStack.pop();
    passedTests += _assert_(userStack.size() == 1);
    passedTests += _assert_(userStack.top().ID == "user1");
    userStack.pop();
    passedTests += _assert_(userStack.isEmpty());
    passedTests += _assert_(userStack.size() == 0);
    return std::make_pair(passedTests, 12);
}

std::pair<int, int> stackTestForGeneralDataStructures() {
    int passedTests = 0;
    Stack<int> intStack;
    passedTests += _assert_(intStack.isEmpty());
    for (int i = 0; i < 99999999; ++i)
        intStack.push(i);
    passedTests += _assert_(!intStack.isEmpty());
    passedTests += _assert_(intStack.size() == 99999999);
    for (int i = 0; i < 99999998; ++i)
        intStack.pop();
    passedTests += _assert_(intStack.top() == 0);
    intStack.pop();
    passedTests += _assert_(intStack.isEmpty());

    Stack<std::string> strStack;
    for (int i = 0; i < 99999999; ++i)
        strStack.push("# " + std::to_string(i));
    int all_passed = 0;
    for (int i = 99999998; i > -1; --i) {
        all_passed += _assert_(strStack.top() == "# " + std::to_string(i));
        strStack.pop();
    }
    passedTests += _assert_(all_passed == 99999999);
    return std::make_pair(passedTests, 6);
}

int stackTests() {
    int passedTests = 0;
    int totalTests = 0;
    std::pair<int, int> r1 = stackTestForBookDataStructure();
    passedTests += r1.first;
    totalTests += r1.second;
    std::pair<int, int> r2 = stackTestForUserDataStructure();
    passedTests += r2.first;
    totalTests += r2.second;
    std::pair<int, int> r3 = stackTestForGeneralDataStructures();
    passedTests += r3.first;
    totalTests += r3.second;
    double grade = static_cast<double>(passedTests * 100) / totalTests;
    grade = std::round(grade * 10) / 10;
    std::cout << "Total tests passed: " << passedTests << " out of " << totalTests << " (" << grade << "%)"  << std::endl;
    return 0;
}

#endif //STACKTESTS_H
