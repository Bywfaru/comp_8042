/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef UNORDEREDSETTESTS_H
#define UNORDEREDSETTESTS_H
#include <iostream>
#include <cmath>
#include "../include/Utils.h"
#include "TestEnvironment.h"
#include "../include/UnorderedSet.h"

std::pair<int, int> unorderedSetTestForBookDataStructure() {
    int passedTests = 0;
    TestEnvironment env;
    UnorderedSet<Book> bookSet;
    bookSet.insert(env.book1);
    bookSet.insert(env.book2);
    passedTests += a_assert(bookSet.size() == 2);
    passedTests += a_assert(bookSet.search(env.book1));
    passedTests += a_assert(!bookSet.search(env.book3));
    bookSet.erase(env.book1);
    passedTests += a_assert(bookSet.size() == 1);
    bookSet.insert(env.book2);
    bookSet.erase(env.book2);
    passedTests += a_assert(bookSet.size() == 0);
    bookSet.insert(env.book1);
    bookSet.insert(env.book4);
    bookSet.insert(env.book5);
    passedTests += a_assert(bookSet.size() == 3);
    bookSet.clear();
    passedTests += a_assert(bookSet.size() == 0);
    bookSet.insert(env.book2);
    passedTests += a_assert(bookSet.search(env.book2));
    bookSet.insert(env.book1);
    passedTests += a_assert(bookSet.search(env.book1));
    passedTests += a_assert(bookSet.search(env.book2));
    bookSet.insert(env.book3);
    passedTests += a_assert(bookSet.search(env.book3));
    passedTests += a_assert(bookSet.search(env.book1));
    passedTests += a_assert(bookSet.search(env.book2));
    bookSet.erase(env.book1);
    passedTests += a_assert(!bookSet.search(env.book1));
    passedTests += a_assert(bookSet.size() == 2);
    bookSet.clear();
    bookSet.insert(env.book1);
    bookSet.insert(env.book2);
    bookSet.insert(env.book3);
    bookSet.insert(env.book4);
    bookSet.insert(env.book5);
    auto it = bookSet.begin();
    passedTests += a_assert(it != bookSet.end());
    passedTests += a_assert(
        *it == env.book1 || *it == env.book2 || *it == env.book3 || *it == env.book4 || *it == env.book5);
    ++it;
    ++it;
    ++it;
    ++it;
    ++it;
    passedTests += a_assert(it == bookSet.end());
    return std::make_pair(passedTests, 18);
}

std::pair<int, int> unorderedSetTestForUserDataStructure() {
    int passedTests = 0;
    TestEnvironment env;
    UnorderedSet<Patron> userSet;
    userSet.insert(env.user1);
    userSet.insert(env.user2);
    passedTests += a_assert(userSet.size() == 2);
    passedTests += a_assert(userSet.search(env.user1));
    passedTests += a_assert(!userSet.search(env.user3));
    userSet.erase(env.user1);
    passedTests += a_assert(userSet.size() == 1);
    userSet.insert(env.user2);
    userSet.erase(env.user2);
    passedTests += a_assert(userSet.size() == 0);
    userSet.insert(env.user1);
    userSet.insert(env.user4);
    userSet.insert(env.user5);
    passedTests += a_assert(userSet.size() == 3);
    userSet.clear();
    passedTests += a_assert(userSet.size() == 0);
    userSet.insert(env.user2);
    passedTests += a_assert(userSet.search(env.user2));
    userSet.insert(env.user1);
    passedTests += a_assert(userSet.search(env.user1));
    passedTests += a_assert(userSet.search(env.user2));
    userSet.insert(env.user3);
    passedTests += a_assert(userSet.search(env.user3));
    passedTests += a_assert(userSet.search(env.user1));
    passedTests += a_assert(userSet.search(env.user2));
    userSet.erase(env.user1);
    passedTests += a_assert(!userSet.search(env.user1));
    passedTests += a_assert(userSet.size() == 2);
    userSet.clear();
    userSet.insert(env.user1);
    userSet.insert(env.user2);
    userSet.insert(env.user3);
    userSet.insert(env.user4);
    userSet.insert(env.user5);
    auto it = userSet.begin();
    passedTests += a_assert(it != userSet.end());
    passedTests += a_assert(
        *it == env.user1 || *it == env.user2 || *it == env.user3 || *it == env.user4 || *it == env.user5);
    ++it;
    ++it;
    ++it;
    ++it;
    ++it;
    passedTests += a_assert(it == userSet.end());
    return std::make_pair(passedTests, 18);
}

std::pair<int, int> unorderedSetTestBalacingFunctionality() {
    int passedTests = 0;
    UnorderedSet<int> intSet;

    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(3);
    passedTests += a_assert(intSet.root->color == Color::BLACK);
    passedTests += a_assert(intSet.root->key == 2);

    intSet.clear();
    intSet.insert(3);
    intSet.insert(2);
    intSet.insert(1);
    passedTests += a_assert(intSet.root->color == Color::BLACK);
    passedTests += a_assert(intSet.root->key == 2);

    intSet.clear();
    intSet.insert(2);
    intSet.insert(1);
    intSet.insert(3);
    passedTests += a_assert(intSet.root->color == Color::BLACK);
    passedTests += a_assert(intSet.root->key == 2);

    intSet.clear();
    intSet.insert(2);
    intSet.insert(1);
    intSet.insert(3);
    intSet.insert(4);
    passedTests += a_assert(intSet.root->key == 2);


    intSet.clear();
    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(2);
    passedTests += a_assert(intSet.root->color == Color::BLACK);

    intSet.clear();
    intSet.insert(1);
    intSet.insert(2);
    intSet.erase(1);
    passedTests += a_assert(intSet.root->color == Color::BLACK);

    intSet.clear();
    intSet.insert(1);
    intSet.insert(2);
    intSet.erase(1);
    intSet.erase(2);
    passedTests += a_assert(intSet.root == nullptr);

    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(3);
    intSet.clear();
    passedTests += a_assert(intSet.root == nullptr);

    intSet.insert(2);
    intSet.insert(1);
    intSet.insert(3);
    intSet.erase(1);
    passedTests += a_assert(intSet.root->color == Color::BLACK);
    passedTests += a_assert(intSet.root->key == 2);

    intSet.clear();
    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(3);
    intSet.erase(2);
    passedTests += a_assert(intSet.root->color == Color::BLACK);

    intSet.clear();
    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(3);
    intSet.insert(4);
    intSet.insert(5);
    passedTests += a_assert(intSet.root->color == Color::BLACK);

    return std::make_pair(passedTests, 15);
}


std::pair<int, int> unorderedSetTestForGeneralDataStructures() {
    int passedTests = 0;
    UnorderedSet<int> intSet;
    passedTests += a_assert(intSet.size() == 0);
    passedTests += a_assert(intSet.insert(42));
    intSet.insert(7);
    passedTests += a_assert(!intSet.insert(42));
    passedTests += a_assert(intSet.size() == 2);
    passedTests += a_assert(intSet.search(7));
    passedTests += a_assert(!intSet.search(8));
    passedTests += a_assert(intSet.erase(7));
    passedTests += a_assert(!intSet.erase(8));
    passedTests += a_assert(intSet.size() == 1);
    passedTests += a_assert(intSet.erase(42));
    passedTests += a_assert(intSet.size() == 0);
    intSet.insert(10);
    intSet.insert(5);
    intSet.insert(15);
    UnorderedSet<int>::Iterator it = intSet.begin();
    passedTests += a_assert(it != intSet.end());
    passedTests += a_assert(*it == 5 || *it == 10 || *it == 15);
    ++it;
    passedTests += a_assert(*it == 5 || *it == 10 || *it == 15);
    ++it;
    ++it;
    passedTests += a_assert(it == intSet.end());
    intSet.clear();
    passedTests += a_assert(intSet.size() == 0);
    UnorderedSet<int>::Iterator emptyIt = intSet.begin();
    passedTests += a_assert(emptyIt == intSet.end());
    return std::make_pair(passedTests, 17);
}


int unorderedSetTests() {
    int passedTests = 0;
    int totalTests = 0;
    std::pair<int, int> r1 = unorderedSetTestForBookDataStructure();
    passedTests += r1.first;
    totalTests += r1.second;
    std::cout << "unorderedSetTestForBookDataStructure: " << r1.first << " /  " << r1.second << std::endl;
    std::pair<int, int> r2 = unorderedSetTestForUserDataStructure();
    passedTests += r2.first;
    totalTests += r2.second;
    std::cout << "unorderedSetTestForUserDataStructure: " << r2.first << " /  " << r2.second << std::endl;
    std::pair<int, int> r3 = unorderedSetTestForGeneralDataStructures();
    passedTests += r3.first;
    totalTests += r3.second;
    std::cout << "unorderedSetTestForGeneralDataStructures: " << r3.first << " /  " << r3.second << std::endl;
    // std::pair<int, int> r4 = unorderedSetTestBalacingFunctionality();
    // passedTests += r4.first;
    // totalTests += r4.second;
    // std::cout << "unorderedSetTestBalacingFunctionality: " << r4.first << " /  " << r4.second << std::endl;
    double grade = static_cast<double>(passedTests * 100) / totalTests;
    grade = std::round(grade * 10) / 10;
    std::cout << "Total tests passed: " << passedTests << " out of " << totalTests << " (" << grade << "%)" <<
            std::endl;
    return 0;
}
#endif //UNORDEREDSETTESTS_H
