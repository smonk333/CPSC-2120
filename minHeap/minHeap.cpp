//
// Created by gboling on 4/18/2023.
//
#include "minHeap.h"

// Private helper functions

void minHeap::siftUp(int pos) {
    int parent = (pos - 1) / 2;
    if (pos > 0 && heap[pos] < heap[parent]) {
        swap(heap[pos], heap[parent]);
        siftUp(parent);
    }
}

void minHeap::siftDown(int pos) {
    int leftChild = 2 * pos + 1;
    int rightChild = 2 * pos + 2;
    int minIndex = pos;
    if (leftChild < heap.size() && heap[leftChild] < heap[minIndex]) {
        minIndex = leftChild;
    }
    if (rightChild < heap.size() && heap[rightChild] < heap[minIndex]) {
        minIndex = rightChild;
    }
    if (minIndex != pos) {
        swap(heap[pos], heap[minIndex]);
        siftDown(minIndex);
    }
}

// Public functions

minHeap::minHeap(vector<int> data) {
    heap = data;
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        siftDown(i);
    }
}

void minHeap::insert(int value) {
    heap.push_back(value);
    siftUp(heap.size() - 1);
}

int minHeap::removeMin() {
    if (heap.empty()) {
        return -1; // Heap is empty, return -1 or throw an exception
    }
    int minValue = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    siftDown(0);
    return minValue;
}