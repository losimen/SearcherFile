//
// Created by Павло Коваль on 11.06.2022.
//

#ifndef SEARCHFILE_SEARCHER_H
#define SEARCHFILE_SEARCHER_H

#include <string>
#include <set>
#include <fstream>
#include <mutex>


class Searcher {
private:
    std::mutex mutexQueueLocker;
    std::set<std::string> queueToSearch;
    std::string result;
    bool isFound;

    std::string searchForFile(const std::string &searchIn, const std::string &toFind);
public:
    Searcher() {
        isFound = false;
        result = "none";
    }

    void tryToSearch(std::string& searchResult, const std::string& toFind);
    void tryToSearch(const std::string& toFind);

    void insertIntoQueue(const std::string &path_to_add);
    void removeFromQueue(const std::string &path_to_remove);
    std::string getFirstQueueElement();
    bool isQueueEmpty();

    const std::string &getResult() const;
    bool getIsFound() const;
};



#endif //SEARCHFILE_SEARCHER_H
