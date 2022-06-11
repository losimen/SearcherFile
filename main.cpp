#include <iostream>
#include <thread>

#include "Searcher.h"


void DeepSearch(Searcher &searcher, const std::string &originPath, const std::string toFind) {
    std::string searchResult = originPath;

    while (not searcher.getIsFound()) {
        if (searchResult != "none")
        {
            searcher.removeFromQueue(searchResult);

            searcher.tryToSearch(searchResult, toFind);
        } else
        {
            if (searcher.isQueueEmpty())
                break;

            searchResult = searcher.getFirstQueueElement();
            searcher.removeFromQueue(searchResult);

            searcher.tryToSearch(searchResult, toFind);
        }
    }
}


int main() {
    const std::string originPath = "/Users/lamens";
    const std::string toFind = "README2.md";

    Searcher searcher;

//    std::thread threadFinder(DeepSearch, std::ref(searcher), std::ref(originPath), std::ref(toFind));
//    threadFinder.join();

    while (searcher.getIsFound())
    {
        ;
    }

    std::cout << searcher.getResult() << std::endl;
    return 0;
}