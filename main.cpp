#include <iostream>
#include <thread>

#include "Searcher.h"


void searchWithThreads(Searcher &searcher, const std::string &toFind) {
    while (not searcher.getIsFound())
        searcher.tryToSearch(toFind);

}

int main() {
    const int amountOfThreads = 9;
    const std::string originPath = "/Users/lamens";
    const std::string toFind = "README2.md";

    std::thread threads[amountOfThreads];
    Searcher searcher(originPath);

    for (auto & thread : threads)
        thread = std::thread(searchWithThreads, std::ref(searcher), std::ref(toFind));

    for (auto & thread : threads)
        thread.join();

    std::cout << searcher.getResult() << std::endl;
    return 0;
}