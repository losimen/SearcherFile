#include <iostream>
#include <thread>

#include "Searcher.h"


void searchWithThreads(Searcher &searcher, const std::string &toFind) {
    while (not searcher.getIsFound())
        searcher.tryToSearch(toFind);

}

int main() {
    const int amountOfThreads = 9;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    const std::string originPath = "C://";
#elif __APPLE__
    const std::string originPath = "/";

#elif __linux__
    const std::string originPath = "/";
#endif

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