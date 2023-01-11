#pragma once

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include "search_server.h"


class RequestQueue {
public:
    explicit RequestQueue(SearchServer &search_server);

    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template<typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string &raw_query, DocumentPredicate document_predicate);

    std::vector<Document> AddFindRequest(const std::string &raw_query, DocumentStatus status);

    std::vector<Document> AddFindRequest(const std::string &raw_query);

    int GetNoResultRequests() const;

    void DeleteOldResults();

private:
    struct QueryResult {
        int time;
        // определите, что должно быть в структуре
    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    int cur_mins = 0;
    SearchServer* server;
};

template<typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string &raw_query, DocumentPredicate document_predicate) {
    ++cur_mins;
    DeleteOldResults();
    std::vector<Document> results = server->FindTopDocuments(raw_query, document_predicate);
    // напишите реализацию
    if (!results.empty()) {
        return results;
    }

    requests_.push_back({cur_mins});
    return {};
}