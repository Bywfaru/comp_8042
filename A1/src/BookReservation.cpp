#include "../include/BookReservation.h"

#include "../include/LExceptions.h"

ReservationRecord::ReservationRecord(std::string &patronID, std::string &bookISBN) : patronID(patronID),
    bookISBN(bookISBN) {
}

ReservationRecord::ReservationRecord(const Patron &patron, const Book &book) : patronID(patron.ID),
                                                                               bookISBN(book.ISBN) {
}

BookReservationManagementSystem::BookReservationManagementSystem(int maxPendingReservations) : pendingReservations(
        CircularQueue<ReservationRecord>(maxPendingReservations)), maxPendingReservations(
        maxPendingReservations) {
}

void BookReservationManagementSystem::indexBookToDB(const Book &book) {
    booksDB.push_back(book);
}

void BookReservationManagementSystem::enqueueReservation(const Patron &patron, const Book &book) {
    // if (pendingReservations.isFull()) throw LibraryReservationQueueFull();

    const ReservationRecord reservation(patron, book);

    pendingReservations.enqueue(reservation);
}

ReservationRecord BookReservationManagementSystem::processReservation() {
    if (pendingReservations.isEmpty()) throw ReservationRecordUnavailable();

    Book *foundBook = nullptr;
    ReservationRecord *reservation = nullptr;
    CircularQueue<ReservationRecord> failedReservations(pendingReservations.size());

    do {
        reservation = &pendingReservations.front();
        pendingReservations.dequeue();

        for (Book &book: booksDB) {
            if (book.ISBN == reservation->bookISBN) {
                foundBook = &book;

                break;
            }
        }

        if (foundBook && foundBook->copies < 1) {
            failedReservations.enqueue(*reservation);
        }
    } while ((!foundBook || foundBook->copies < 1) && !pendingReservations.isEmpty());

    if (pendingReservations.isEmpty()) {
        while (!failedReservations.isEmpty()) {
            ReservationRecord failedReservation = failedReservations.front();
            failedReservations.dequeue();

            pendingReservations.enqueue(failedReservation);
        }

        if (foundBook && foundBook->copies < 1) throw ReservationRecordUnavailable();
    }

    if (foundBook) foundBook->copies -= 1;

    fulfilledReservations.push(*reservation);

    return *reservation;
}

void BookReservationManagementSystem::enqueueReservation(const ReservationRecord &reservation) {
    // if (pendingReservations.isFull()) throw LibraryReservationQueueFull();

    pendingReservations.enqueue(reservation);
}
