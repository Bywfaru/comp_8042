/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef BOOKRESERVATIONTESTS_H
#define BOOKRESERVATIONTESTS_H
#include <iostream>
#include <cmath>
#include "TestEnvironment.h"
#include "../include/BookReservation.h"
#include "../include/LExceptions.h"

std::pair<int, int>  bookReservationTestPendingReservations() {
    int passedTests = 0;
    TestEnvironment te;
    te.book1.copies = 1;
    te.book2.copies = 0;
    te.book3.copies = 1;
    BookReservationManagementSystem brms( 5);
    passedTests += _assert_(brms.pendingReservations.isEmpty());
    try { // No book is indexed so processReservation must throw an exception!
        brms.processReservation();
        passedTests += _assert_(false);
    } catch (const ReservationRecordUnavailable& e) {
        passedTests += _assert_(true);
    }
    brms.indexBookToDB(te.book1);
    brms.indexBookToDB(te.book2);
    brms.indexBookToDB(te.book3);
    brms.indexBookToDB(te.book4);
    brms.indexBookToDB(te.book5);
    brms.indexBookToDB(te.book6);
    brms.indexBookToDB(te.book7);
    brms.indexBookToDB(te.book8);
    brms.indexBookToDB(te.book9);
    brms.indexBookToDB(te.book10);
    brms.enqueueReservation(te.user1, te.book1);
    brms.enqueueReservation(te.user2, te.book2);
    brms.enqueueReservation(te.user3, te.book3);
    passedTests += _assert_(!brms.pendingReservations.isEmpty());
    passedTests += _assert_(brms.pendingReservations.size() == 3);
    CircularQueue<ReservationRecord> tempQueue = brms.pendingReservations;
    ReservationRecord reservation = tempQueue.front();
    tempQueue.dequeue();
    passedTests += _assert_(reservation.patronID == te.user1.ID);
    passedTests += _assert_(reservation.bookISBN == te.book1.ISBN);
    passedTests += _assert_(!tempQueue.isEmpty());
    passedTests += _assert_(tempQueue.size() == 2);
    passedTests += _assert_(brms.pendingReservations.size() == 3);
    reservation = tempQueue.front();
    tempQueue.dequeue();
    passedTests += _assert_(reservation.patronID == te.user2.ID);
    passedTests += _assert_(reservation.bookISBN == te.book2.ISBN);
    passedTests += _assert_(!tempQueue.isEmpty());
    passedTests += _assert_(tempQueue.size() == 1);
    passedTests += _assert_(brms.pendingReservations.size() == 3);
    reservation = tempQueue.front();
    tempQueue.dequeue();
    passedTests += _assert_(reservation.patronID == te.user3.ID);
    passedTests += _assert_(reservation.bookISBN == te.book3.ISBN);
    passedTests += _assert_(tempQueue.isEmpty());
    passedTests += _assert_(tempQueue.size() == 0);
    passedTests += _assert_(brms.pendingReservations.size() == 3);

    passedTests += _assert_(brms.fulfilledReservations.isEmpty());
    ReservationRecord request = brms.processReservation();
    passedTests += _assert_(request.patronID == te.user1.ID);
    passedTests += _assert_(request.bookISBN == te.book1.ISBN);
    passedTests += _assert_(brms.fulfilledReservations.size() == 1);
    Stack<ReservationRecord> tempStack = brms.fulfilledReservations;
    ReservationRecord fulfilledReservation = tempStack.top();
    tempStack.pop();
    passedTests += _assert_(fulfilledReservation.patronID == te.user1.ID);
    passedTests += _assert_(fulfilledReservation.bookISBN == te.book1.ISBN);
    passedTests += _assert_(tempStack.isEmpty());
    passedTests += _assert_(tempStack.size() == 0);
    passedTests += _assert_(brms.fulfilledReservations.size() == 1);
    ReservationRecord request2 = brms.processReservation();
    passedTests += _assert_(request2.patronID == te.user3.ID);
    passedTests += _assert_(request2.bookISBN == te.book3.ISBN);
    passedTests += _assert_(brms.fulfilledReservations.size() == 2);
    try { // there is one request but the requested book is not available!
        brms.processReservation();
        passedTests += _assert_(false);
    } catch (const ReservationRecordUnavailable& e) {
        passedTests += _assert_(true);
    }
    Book& book2 = brms.booksDB.at(1);
    book2.copies = 1; // making the book available now!
    ReservationRecord request3 = brms.processReservation();
    passedTests += _assert_(request3.patronID == te.user2.ID);
    passedTests += _assert_(request3.bookISBN == te.book2.ISBN);
    passedTests += _assert_(brms.fulfilledReservations.size() == 3);
    Stack<ReservationRecord> tempStack2 = brms.fulfilledReservations;
    ReservationRecord fulfilledReservation2 = tempStack2.top();
    tempStack2.pop();
    passedTests += _assert_(fulfilledReservation2.patronID == te.user2.ID);
    passedTests += _assert_(fulfilledReservation2.bookISBN == te.book2.ISBN);
    passedTests += _assert_(tempStack2.size() == 2);
    fulfilledReservation2 = tempStack2.top();
    tempStack2.pop();
    passedTests += _assert_(fulfilledReservation2.patronID == te.user3.ID);
    passedTests += _assert_(fulfilledReservation2.bookISBN == te.book3.ISBN);
    passedTests += _assert_(tempStack2.size() == 1);
    fulfilledReservation2 = tempStack2.top();
    tempStack2.pop();
    passedTests += _assert_(fulfilledReservation2.patronID == te.user1.ID);
    passedTests += _assert_(fulfilledReservation2.bookISBN == te.book1.ISBN);
    passedTests += _assert_(tempStack2.isEmpty());
    passedTests += _assert_(tempStack2.size() == 0);
    return std::make_pair(passedTests, 45);
}

int bookReservationTests() {
    int passedTests = 0;
    int totalTests = 0;
    std::pair<int, int> r1 = bookReservationTestPendingReservations();
    passedTests += r1.first;
    totalTests += r1.second;
    double grade = static_cast<double>(passedTests * 100) / totalTests;
    grade = std::round(grade * 10) / 10;
    std::cout << "Total tests passed: " << passedTests << " out of " << totalTests << " (" << grade << "%)"  << std::endl;
    return 0;
}
#endif //BOOKRESERVATIONTESTS_H
