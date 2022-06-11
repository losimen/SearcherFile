#include <iostream>
#include <thread>

#include "Searcher.h"


int main() {
    const std::string originPath = "/Users/lamens";
    const std::string toFind = "README2.md";

    Searcher searcher(originPath);

//    std::thread threadFinder(DeepSearch, std::ref(searcher), std::ref(originPath), std::ref(toFind));
//    threadFinder.join();

    while (not searcher.getIsFound())
    {
        searcher.tryToSearch(toFind);
    }

    std::cout << searcher.getResult() << std::endl;
    return 0;
}