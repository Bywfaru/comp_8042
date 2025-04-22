#include "../include/BookReservation.h"

#include "../include/LExceptions.h"

/**
 * Initializes the reservation record with the patron's ID and book's ISBN.
 * @param patronID the ID of the patron the reservation belongs to
 * @param bookISBN the ISBN of the book to reserve
 */
ReservationRecord::ReservationRecord(std::string &patronID, std::string &bookISBN) : patronID(patronID),
    bookISBN(bookISBN) {
}

/**
 * Initializes the reservation record with the Patron's object and Book's object.
 * @param patron the Patron object representing the patron the reservation belongs to
 * @param book the Book object representing the book to reserve
 */
ReservationRecord::ReservationRecord(const Patron &patron, const Book &book) : patronID(patron.ID),
                                                                               bookISBN(book.ISBN) {
}

/**
 * Initializes the book reservation management system with the maximum number of books allowed to be pending.
 * @param maxPendingReservations the maximum number of books to allow to be pending
 */
BookReservationManagementSystem::BookReservationManagementSystem(int maxPendingReservations) : pendingReservations(
        CircularQueue<ReservationRecord>(maxPendingReservations)), maxPendingReservations(
        maxPendingReservations) {
}

/**
 * Adds the given book to the database.
 * @param book the Book object representing the book to be added to the database
 */
void BookReservationManagementSystem::indexBookToDB(const Book &book) {
    booksDB.push_back(book);
}

/**
 * Creates a ReservationRecord from the given Patron and Book objects and adds it to the end of the pending reservations queue.
 * @param patron the Patron object representing the patron the reservation belongs to
 * @param book the Book object representing the book to reserve
 * @throws LibraryReservationQueueFull when the pending reservations queue is full
 */
void BookReservationManagementSystem::enqueueReservation(const Patron &patron, const Book &book) {
    if (pendingReservations.isFull()) throw LibraryReservationQueueFull();

    const ReservationRecord reservation(patron, book);

    pendingReservations.enqueue(reservation);
}

/**
 * Processes the first available book in the pending reservations queue.
 * @return the ReservationRecord that was successfully fulfilled
 * @throws ReservationRecordUnavailable if:
 *  - the pending reservations queue is empty
 *  - none of the books in the pending reservations queue are available
 */
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

/**
 * Adds the given reservation record to the end of the pending reservations queue.
 * @param reservation the reservation record to add to the end of the pending reservations queue
 * @throws LibraryReservationQueueFull when the pending reservations queue is full
 */
void BookReservationManagementSystem::enqueueReservation(const ReservationRecord &reservation) {
    if (pendingReservations.isFull()) throw LibraryReservationQueueFull();

    pendingReservations.enqueue(reservation);
}
