//
// Created by Павло Коваль on 11.06.2022.
//

#include "Searcher.h"

std::string Searcher::searchForFile(const std::string &searchIn, const std::string &toFind) {
    std::string pathStr;
    for (const auto& entry : std::__fs::filesystem::directory_iterator(searchIn))
    {
        if (entry.is_directory())
            insertIntoQueue(entry.path());

        pathStr = entry.path().string();
        if (toFind == pathStr.substr(pathStr.rfind('/')+1))
        {
            result = entry.path();
            isFound = true;
        }
    }

    return "none";
}

void Searcher::tryToSearch(std::string &searchResult, const std::string &toFind) {
    try {
        searchResult = searchForFile(searchResult, toFind);
    }
    catch (std::filesystem::filesystem_error const& ex) {
        queueToSearch.erase(searchResult);
        searchResult = *queueToSearch.begin();
    }
}

void Searcher::tryToSearch(const std::string &toFind) {
    if (not queueToSearch.empty()) {
        std::string searchResult = getFirstQueueElement();
        removeFromQueue(searchResult);
    }

    std::string searchResult = "/Users/lamens";

    try {
        searchResult = searchForFile(searchResult, toFind);
    }
    catch (std::filesystem::filesystem_error const& ex) {
        queueToSearch.erase(searchResult);
        searchResult = *queueToSearch.begin();
    }
}

void Searcher::insertIntoQueue(const std::string &path_to_add) {
    mutexQueueLocker.lock();
    queueToSearch.insert(path_to_add);
    mutexQueueLocker.unlock();
}

void Searcher::removeFromQueue(const std::string &path_to_remove) {
    mutexQueueLocker.lock();
    queueToSearch.erase(path_to_remove);
    mutexQueueLocker.unlock();
}

bool Searcher::isQueueEmpty() {
    return queueToSearch.empty();
}

std::string Searcher::getFirstQueueElement() {
    return *queueToSearch.begin();
}

const std::string &Searcher::getResult() const {
    return result;
}

bool Searcher::getIsFound() const {
    return isFound;
}
