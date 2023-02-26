/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#pragma once

#include <vector>

template <class T>
int linearSearch(std::vector<T> data, T target){
    int count = 0;
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == target) {
            count = i;
            return count;
        }

        else {
            count++;
        }
    }

    if (count == data.size() && data[count] != target) {
        return -1;
    }
}


template <class T>
int binarySearch(std::vector<T> data, T target){
    int bottom = 0, top = data.size() - 1;
    int center;

    while (top - bottom > 1) {
        center = (top + bottom) / 2;
        if (data[center] < target) {
            bottom = center + 1;
        }
        else {
            top = center;
        }
    }
    if (data[bottom] == target) {
        return bottom;
    }
    else if (data[top] == target) {
        return top;
    }
    else {
        return -1;
    }
}
