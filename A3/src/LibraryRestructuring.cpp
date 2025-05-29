#include "../include/LibraryRestructuring.h"

/**
 * Constructor.
 * @param records Borrow records
 * @param bookCollection Book collection
 */
LibraryRestructuring::LibraryRestructuring(const UnorderedSet<BorrowRecord> &records,
                                           const UnorderedSet<Book> &bookCollection) {
}

/**
 * Cluster the graph nodes and sort clusters by average borrowing time; within each cluster, the nodes must be internally
 * sorted based on "sortBy" type which can be one of "title", "author", and "yearPublished"
 * @param sortBy Sort by
 * @return The sorted cluster
 */
std::vector<std::vector<std::string> > LibraryRestructuring::clusterAndSort(const std::string &sortBy) {
}

/**
 * Perform a DFS search to find all the nodes connected to the pointed current ISBN.
 * @param current Current pointer
 * @param cluster Cluster to search
 * @param visited Table of visited nodes
 */
void LibraryRestructuring::dfs(const std::string &current, std::vector<std::string> &cluster,
                               HashTable<std::string, bool> &visited) {
}

/**
 * Calculate the average number of days that the books in this cluster have been borrowed.
 * @param cluster Cluster to perform the operation on
 * @return The average borrowing time
 */
double LibraryRestructuring::getAverageBorrowingTime(const std::vector<std::string> &cluster) {
}


