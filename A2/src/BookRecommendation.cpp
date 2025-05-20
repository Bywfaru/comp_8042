#include "../include/BookRecommendation.h"

void BookRecommendation::addUserBorrowedBook(Patron &userID, Book &book) {
    // If a list of borrowed books exists for the user
    if (userBorrowedBooks.search(userID.ID)) {
        // Update the user's list of borrowed books
        UnorderedSet<Book> borrowedBooks = userBorrowedBooks[userID.ID];

        borrowedBooks.insert(book);
    } else {
        // Create a new list of borrowed books for the user
        UnorderedSet<Book> borrowedBooks{};

        borrowedBooks.insert(book);
        userBorrowedBooks.insert(userID.ID, borrowedBooks);
    }
}

std::vector<Book> BookRecommendation::getBookRecommendations(
    const std::string &targetUserID,
    int numRecommendations,
    int neighborhoodSize
) {
    const auto neighborhood = getNeighborhood(targetUserID, neighborhoodSize);
    const auto recommendedBooks = getRecommendedBooks(neighborhood, targetUserID);

    std::vector<Book> recommendations;
    recommendations.reserve(numRecommendations);

    for (const auto &book: recommendedBooks) {
        if (recommendations.size() < numRecommendations) {
            recommendations.push_back(book);
        } else {
            // If the number of recommendations is already at the maximum,
            // check if the current book is more similar to the target patron ID than the last recommended book
            double similarity = calculateSimilarity(targetUserID, book.ISBN);
            double lastSimilarity = calculateSimilarity(targetUserID, recommendations.back().ISBN);

            if (similarity > lastSimilarity) {
                // If the current book is more similar to the target patron ID, replace the last recommended book
                recommendations.back() = book;
            }
            // If the current book is not more similar to the target patron ID, do nothing
            // (the last recommended book will remain the same)
            // This is to ensure that the recommendations are always in descending order of similarity
            // to the target patron ID
        }
    }

    return recommendations;
}

double BookRecommendation::calculateSimilarity(const std::string &userID1, const std::string &userID2) {
    const auto user1BorrowedBooks = userBorrowedBooks.search(userID1);
    const auto user2BorrowedBooks = userBorrowedBooks.search(userID2);

    if (user1BorrowedBooks == nullptr || user2BorrowedBooks == nullptr) return 0;

    auto it1 = user1BorrowedBooks->begin();
    double numCommonBooks = 0;

    while (it1 != user1BorrowedBooks->end()) {
        const auto book = *it1;

        if (user2BorrowedBooks->search(book)) numCommonBooks += 1;

        ++it1;
    }

    const auto totalUniqueItems = user1BorrowedBooks->size() + user2BorrowedBooks->size() - numCommonBooks;

    return numCommonBooks / totalUniqueItems;
}

UnorderedSet<std::string> BookRecommendation::getNeighborhood(const std::string &targetUserID, int neighborhoodSize) {
    // 1. Get the set of all patron IDs (excluding the target patron ID)
    std::vector<std::string> patronIDs;
    for (auto it = userBorrowedBooks.begin(); it != userBorrowedBooks.end(); ++it) {
        const std::string &userID = (*it)->key;
        if (userID != targetUserID) {
            patronIDs.push_back(userID);
        }
    }

    // 2. Use a Stack to keep track of most similar users and calculate similarity scores
    struct UserSimilarity {
        std::string userID;
        double similarity;

        UserSimilarity(const std::string &id, double sim) : userID(id), similarity(sim) {
        }

        bool operator<(const UserSimilarity &other) const {
            return similarity < other.similarity;
        }
    };

    Stack<UserSimilarity> similarUsers;
    // Calculate similarities and keep top K users
    for (const auto &userID: patronIDs) {
        double similarity = calculateSimilarity(targetUserID, userID);

        if (similarity > 0) {
            // Only consider users with some similarity
            UserSimilarity current(userID, similarity);

            // If stack is not full, just push
            if (similarUsers.size() < neighborhoodSize) {
                similarUsers.push(current);
            } else if (similarity > similarUsers.top().similarity) {
                // If new similarity is higher than lowest in stack
                similarUsers.pop();
                similarUsers.push(current);
            }
        }
    }

    // 4. Convert Stack to UnorderedSet
    UnorderedSet<std::string> neighborhood;
    while (!similarUsers.isEmpty()) {
        neighborhood.insert(similarUsers.top().userID);
        similarUsers.pop();
    }

    return neighborhood;
}


UnorderedSet<Book> BookRecommendation::getRecommendedBooks(const UnorderedSet<std::string> &neighborhood,
                                                           const std::string &targetUserID) {
    // 1. Create a HashTable to store the frequency of each book borrowed by users in the neighbourhood

    HashTable<std::string, int> frequencyMap;

    for (const auto &userID: neighborhood) {
        const auto borrowedBooks = userBorrowedBooks.search(userID);

        for (const auto &book: *borrowedBooks) {
            if (frequencyMap.search(book.ISBN)) {
                frequencyMap.updateValueForKey(book.ISBN, frequencyMap[book.ISBN] + 1);
            } else {
                frequencyMap.insert(book.ISBN, 1);
            }
        }
    }

    UnorderedSet<Book> recommendedBooks;
    const auto borrowedBooks = userBorrowedBooks.search(targetUserID);

    // 2. Iterate through the frequency map and add books that haven't been borrowed by the target patron ID to the recommendedBooks
    //    UnorderedSet
    for (const auto &book: frequencyMap) {
        auto it = borrowedBooks->begin();

        while (it != borrowedBooks->end()) {
            const auto borrowedBook = *it;
            if (borrowedBook.ISBN == book->key) {
                recommendedBooks.insert(borrowedBook);
                break;
            }

            ++it;
        }
    }

    // 3. Return the recommendedBooks UnorderedSet
    return recommendedBooks;
}

