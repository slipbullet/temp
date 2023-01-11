#include <vector>
#include <string>
#include "request_queue.h"

RequestQueue::RequestQueue(SearchServer &search_server) {
    server = &search_server;
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string &raw_query, DocumentStatus status) {
    ++cur_mins;
    DeleteOldResults();
    auto results = server->FindTopDocuments(raw_query, status);
    if (results.empty()) {
        return results;
    }

    requests_.push_back({cur_mins});
    return {};
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string &raw_query) {
    ++cur_mins;
    DeleteOldResults();
    auto results = server->FindTopDocuments(raw_query);
    if (!results.empty()) {
        return results;
    }

    requests_.push_back({cur_mins});
    return {};
}

int RequestQueue::GetNoResultRequests() const {
    return static_cast<int>(requests_.size());
}

void RequestQueue::DeleteOldResults(){
    while(!requests_.empty()){
        auto temp = *requests_.begin();
        if(cur_mins - temp.time >= min_in_day_){
            requests_.pop_front();
        } else {
            break;
        }
    }
}


