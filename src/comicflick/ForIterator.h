#pragma once
/**
 * C++11 range-for loop with iterators
 *
 * Usage:
 *
 *   for(auto i : ForIterator(some_list)) {
 *     // i is the iterator, which was returned by some_list.begin()
 *     // might be useful for whatever reason
 *   }
 */
template <typename T> struct Iterator {
    T& list;
    typedef decltype(list.begin()) I;

    struct InnerIterator {
        I i;
        InnerIterator(I i) : i(i) {}
        I operator * () { return i; }
        I operator ++ () { return ++i; }
        bool operator != (const InnerIterator& o) { return i != o.i; }
    };

    Iterator(T& list) : list(list) {}
    InnerIterator begin() { return InnerIterator(list.begin()); }
    InnerIterator end() { return InnerIterator(list.end()); }
};
template <typename T> Iterator<T> ForIterator(T& list) {
    return Iterator<T>(list);
}
