#if !defined(CPP_SORTER_H_)
#define CPP_SORTER_H_

#include <algorithm>
#include <iostream>

void hello();

// simple sorter for arrays
template <typename T>
void array_sort(T * arr, size_t len)
{
    std::sort(arr, arr+len);
    hello();
}

#endif

