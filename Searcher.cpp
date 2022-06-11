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
    mutexQueueLocker.lock();

    std::string searchResult;

    if (not queueToSearch.empty()) {
        searchResult = getFirstQueueElement();
        removeFromQueue(searchResult);
    }
    else {
        searchResult = originPath;
    }

    try {
        searchResult = searchForFile(searchResult, toFind);
    }
    catch (std::filesystem::filesystem_error const& ex) {
        queueToSearch.erase(searchResult);
    }

    mutexQueueLocker.unlock();
}

void Searcher::insertIntoQueue(const std::string &path_to_add) {
    queueToSearch.insert(path_to_add);
}

void Searcher::removeFromQueue(const std::string &path_to_remove) {
    queueToSearch.erase(path_to_remove);
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
