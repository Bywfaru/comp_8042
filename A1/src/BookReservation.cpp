#include "../include/BookReservation.h"

ReservationRecord::ReservationRecord(std::string &patronID, std::string &bookISBN) : patronID(patronID),
    bookISBN(bookISBN) {
}

ReservationRecord::ReservationRecord(const Patron &patron, const Book &book) : patronID(patron.ID),
                                                                               bookISBN(book.ISBN) {
}

BookReservationManagementSystem::BookReservationManagementSystem(int maxPendingReservations) : maxPendingReservations(
    maxPendingReservations) {
}

void BookReservationManagementSystem::indexBookToDB(const Book &book) {
}

void BookReservationManagementSystem::enqueueReservation(const Patron &patron, const Book &book) {
}

ReservationRecord BookReservationManagementSystem::processReservation() {
}

void BookReservationManagementSystem::enqueueReservation(const ReservationRecord &reservation) {
}




