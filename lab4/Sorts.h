/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#pragma once

#include <vector>

template <class T>
void merge(std::vector<T>& left, std::vector<T>& right, std::vector<T>& result) {
    result.clear();
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }
}
template <class T>
std::vector<T> mergeSort(std::vector<T> lst) {
    if (lst.size() <= 1) {
        return lst;
    }
    std::vector<T> left, right, result;
    size_t middle = lst.size() / 2;
    left.reserve(middle);
    right.reserve(lst.size() - middle);
    for (size_t i = 0; i < middle; i++) {
        left.push_back(lst[i]);
    }
    for (size_t i = middle; i < lst.size(); i++) {
        right.push_back(lst[i]);
    }
    left = mergeSort(left);
    right = mergeSort(right);
    merge(left, right, result);
    return result;
}



template <class T>
void quickSortRecursive(std::vector<T>& lst, int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot = (left + right) / 2;
    T pivotValue = lst[pivot];
    int i = left, j = right;
    while (i <= j) {
        while (lst[i] < pivotValue) {
            i++;
        }
        while (lst[j] > pivotValue) {
            j--;
        }
        if (i <= j) {
            std::swap(lst[i], lst[j]);
            i++;
            j--;
        }
    }
    quickSortRecursive(lst, left, j);
    quickSortRecursive(lst, i, right);
}

template <class T>
std::vector<T> quickSort(std::vector<T> lst) {
    quickSortRecursive(lst, 0, lst.size() - 1);
    return lst;
}

