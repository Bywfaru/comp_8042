#include "../include/LibraryRestructuring.h"

/**
 * Constructor. Calculates a book's total borrowing time from the unordered set of records and saves the book collection
 * into a hash table. Then, creates a graph representation using an adjacency list.
 * @param records Borrow records
 * @param bookCollection Book collection
 */
LibraryRestructuring::LibraryRestructuring(
    const UnorderedSet<BorrowRecord> &records,
    const UnorderedSet<Book> &bookCollection
) : graph(bookCollection.size() * 2),
    bookBorrowingTime(bookCollection.size() * 2),
    allBooks(bookCollection.size() * 2) {
    auto bookCollectionIter = bookCollection.begin();

    // Store the book collection, initialize the graph with the books' ISBN as the key, and initialize each book's borrowing
    // time
    while (bookCollectionIter != bookCollection.end()) {
        const Book book = *bookCollectionIter;
        const UnorderedSet<std::string> bookAdjacencyList{};

        allBooks.insert(book.ISBN, book);
        graph.insert(book.ISBN, bookAdjacencyList);
        bookBorrowingTime[book.ISBN] = 0;

        ++bookCollectionIter;
    }

    auto recordsIter = records.begin();

    // Calculate each book's borrowing time
    while (recordsIter != records.end()) {
        const BorrowRecord &record = *recordsIter;
        const auto *borrowingTime = bookBorrowingTime.search(record.bookISBN);

        if (borrowingTime == nullptr) {
            bookBorrowingTime[record.bookISBN] = Date::diffDuration(record.returnDate, record.checkoutDate);
        } else {
            bookBorrowingTime[record.bookISBN] += Date::diffDuration(record.returnDate, record.checkoutDate);
        }

        auto iter = recordsIter;

        ++iter;

        while (iter != records.end()) {
            const BorrowRecord &newRecord = *iter;

            // Each pair of books gets a connecting edge if they are borrowed with the same patron.
            if (
                record.bookISBN != newRecord.bookISBN &&
                record.patronId == newRecord.patronId
            ) {
                graph[record.bookISBN].insert(newRecord.bookISBN);
                graph[newRecord.bookISBN].insert(record.bookISBN);
            }

            ++iter;
        }

        ++recordsIter;
    }
}

bool strCompare(const std::string &a, const std::string &b) {
    return a < b;
}

/**
 * Cluster the graph nodes and sort clusters by average borrowing time; within each cluster, the nodes must be internally
 * sorted based on "sortBy" type which can be one of "title", "author", and "yearPublished"
 * @param sortBy Sort by
 * @return The sorted cluster
 */
std::vector<std::vector<std::string> > LibraryRestructuring::clusterAndSort(const std::string &sortBy) {
    std::vector<std::vector<std::string> > clusters;
    HashTable<std::string, bool> visited(allBooks.size() * 2);

    for (const auto &book: allBooks) {
        if (book->occupied) visited[book->key] = false;
    }

    auto visitedIter = visited.begin();

    while (visitedIter != visited.end()) {
        const auto current = *visitedIter;

        if (!visited[current->key]) {
            std::vector<std::string> cluster;
            dfs(current->key, cluster, visited);

            if (cluster.size() > 1) {
                if (sortBy == "title") {
                    MergeSort<std::string> titleSort([this](const std::string &a, const std::string &b) {
                        const Book *bookA = allBooks.search(a);
                        const Book *bookB = allBooks.search(b);

                        return bookA->title < bookB->title;
                    });

                    titleSort.sort(cluster);
                } else if (sortBy == "author") {
                    MergeSort<std::string> authorSort([this](const std::string &a, const std::string &b) {
                        const Book *bookA = allBooks.search(a);
                        const Book *bookB = allBooks.search(b);

                        return bookA->author < bookB->author;
                    });
                } else if (sortBy == "yearPublished") {
                    RadixSort<std::string> yearPublishedSort(cluster, [this](const std::string &bookIsbn) {
                        const Book *book = allBooks.search(bookIsbn);

                        return std::stoi(book->yearPublished);
                    });
                }

                clusters.push_back(cluster);
            };
        }

        ++visitedIter;
    }

    // The list of clusters must be sorted based on the average duration of the borrowed time of the books in each cluster
    // so that the frequently borrowed books are placed closer to the library counter
    MergeSort<std::vector<std::string> > averageBorrowTimeSort(
        [this](const std::vector<std::string> &a, const std::vector<std::string> &b) {
            return getAverageBorrowingTime(a) > getAverageBorrowingTime(b);
        });


    return clusters;
}

/**
 * Perform a DFS search to find all the nodes connected to the pointed current ISBN.
 * @param current Current pointer
 * @param cluster Cluster to search
 * @param visited Table of visited nodes
 */
void LibraryRestructuring::dfs(const std::string &current, std::vector<std::string> &cluster,
                               HashTable<std::string, bool> &visited) {
    if (visited[current]) return;

    visited[current] = true;
    cluster.push_back(current);

    for (const std::string &neighbor: graph[current]) {
        dfs(neighbor, cluster, visited);
    }
}

/**
 * Calculate the average number of days that the books in this cluster have been borrowed.
 * @param cluster Cluster to perform the operation on
 * @return The average borrowing time
 */
double LibraryRestructuring::getAverageBorrowingTime(const std::vector<std::string> &cluster) {
    double sum = 0;

    for (const std::string &isbn: cluster) {
        sum += bookBorrowingTime[isbn];
    }

    return sum / cluster.size();
}


