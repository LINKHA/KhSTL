#pragma once

#include "Iterator.h"
#include "Swap.h"

namespace KhSTL
{

static const int QUICKSORT_THRESHOLD = 16;

// Based on Comparison of several sorting algorithms by Juha Nieminen
// http://warp.povusers.org/SortComparison/

/// Perform insertion sort on an array.
template <typename _Ty1> void InsertionSort(RandomAccessIterator<_Ty1> begin, RandomAccessIterator<_Ty1> end)
{
    for (RandomAccessIterator<_Ty1> i = begin + 1; i < end; ++i)
    {
        _Ty1 temp = *i;
        RandomAccessIterator<_Ty1> j = i;
        while (j > begin && temp < *(j - 1))
        {
            *j = *(j - 1);
            --j;
        }
        *j = temp;
    }
}

/// Perform insertion sort on an array using a compare function.
template <typename _Ty, class _Ty2> void InsertionSort(RandomAccessIterator<_Ty> begin, RandomAccessIterator<_Ty> end, _Ty2 compare)
{
    for (RandomAccessIterator<_Ty1> i = begin + 1; i < end; ++i)
    {
        _Ty1 temp = *i;
        RandomAccessIterator<_Ty1> j = i;
        while (j > begin && compare(temp, *(j - 1)))
        {
            *j = *(j - 1);
            --j;
        }
        *j = temp;
    }
}

/// Perform quick sort initial pass on an array. Does not sort fully.
template <typename _Ty> void InitialQuickSort(RandomAccessIterator<_Ty> begin, RandomAccessIterator<_Ty> end)
{
    while (end - begin > QUICKSORT_THRESHOLD)
    {
        // Choose the pivot by median
        RandomAccessIterator<_Ty1> pivot = begin + ((end - begin) / 2);
        if (*begin < *pivot && *(end - 1) < *begin)
            pivot = begin;
        else if (*(end - 1) < *pivot && *begin < *(end - 1))
            pivot = end - 1;
        
        // Partition and sort recursively
        RandomAccessIterator<_Ty1> i = begin - 1;
        RandomAccessIterator<_Ty1> j = end;
        _Ty1 pivotValue = *pivot;
        for (;;)
        {
            while (pivotValue < *(--j));
            while (*(++i) < pivotValue);
            if (i < j)
                Swap(*i, *j);
            else
                break;
        }
        
        InitialQuickSort(begin, j + 1);
        begin = j + 1;
    }
}

/// Perform quick sort initial pass on an array using a compare function. Does not sort fully.
template <typename _Ty, class _Ty2> void InitialQuickSort(RandomAccessIterator<_Ty> begin, RandomAccessIterator<_Ty> end, _Ty2 compare)
{
    while (end - begin > QUICKSORT_THRESHOLD)
    {
        // Choose the pivot by median
        RandomAccessIterator<_Ty1> pivot = begin + ((end - begin) / 2);
        if (compare(*begin, *pivot) && compare(*(end - 1), *begin))
            pivot = begin;
        else if (compare(*(end - 1), *pivot) && compare(*begin, *(end - 1)))
            pivot = end - 1;
        
        // Partition and sort recursively
        RandomAccessIterator<_Ty1> i = begin - 1;
        RandomAccessIterator<_Ty1> j = end;
        _Ty1 pivotValue = *pivot;
        for (;;)
        {
            while (compare(pivotValue, *(--j)));
            while (compare(*(++i), pivotValue));
            if (i < j)
                Swap(*i, *j);
            else
                break;
        }
        
        InitialQuickSort(begin, j + 1, compare);
        begin = j + 1;
    }
}

/// Sort in ascending order using quicksort for initial passes, then an insertion sort to finalize.
template <typename _Ty> void Sort(RandomAccessIterator<_Ty> begin, RandomAccessIterator<_Ty> end)
{
    InitialQuickSort(begin, end);
    InsertionSort(begin, end);
}

/// Sort in ascending order using quicksort for initial passes, then an insertion sort to finalize, using a compare function.
template <typename _Ty, class _Ty2> void Sort(RandomAccessIterator<_Ty> begin, RandomAccessIterator<_Ty> end, _Ty2 compare)
{
    InitialQuickSort(begin, end, compare);
    InsertionSort(begin, end, compare);
}

}
