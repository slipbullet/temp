#pragma once

#include <vector>
#include <iostream>
#include "document.h"

template <class Iterator>
class IteratorRange{
public:
    explicit IteratorRange(Iterator first_it, Iterator last_it):range_begin(first_it), range_end(last_it),
                                                                page_size(static_cast<size_t>(distance(first_it, last_it))){
    }

    Iterator begin(){
        return range_begin;
    }

    Iterator end(){
        return range_end;
    }

    int size(){
        return distance(range_begin, range_end);
    }

private:
    Iterator range_begin;
    Iterator range_end;
    size_t page_size;
};

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        std::cout << *it;
    }
}

std::ostream& operator<<(std::ostream& out, const Document& document){
    out << "{ document_id = " << document.id << ", relevance = " << document.relevance << ", rating = "
        << document.rating << " }";
    return out;
}

template<class Iterator>
std::ostream& operator<<(std::ostream& out, IteratorRange<Iterator> range){
    PrintRange(range.begin(), range.end());
    return out;
}


template <typename Iterator>
class Paginator {
public:
    explicit Paginator(Iterator range_begin, Iterator range_end, size_t page){
        if(page == 0){
            throw std::out_of_range("Недопустимое количество страниц");
        }
        if(range_end == range_begin){
            return;
        }
        while (distance(range_begin, range_end) > static_cast<int>(page)) {
            auto temp_iterator_begin = range_begin;
            advance(temp_iterator_begin, page);
            pages.push_back(IteratorRange<Iterator>(range_begin, temp_iterator_begin));
            range_begin = temp_iterator_begin;
        }
        pages.push_back(IteratorRange<Iterator>(range_begin, range_end));
    }

    auto begin() const{
        return pages.begin();
    }

    auto end() const{
        return pages.end();
    }

    int size(){
        return pages.size();
    }

private:
    std::vector<IteratorRange<Iterator>> pages;
};


template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator<Container>(begin(c), end(c), page_size);
}