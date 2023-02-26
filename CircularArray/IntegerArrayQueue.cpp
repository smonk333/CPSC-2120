#include "IntegerArrayQueue.h"

bool IntegerArrayQueue::enqueue(int value) {
    // Check if the queue is already full
    if (front == (back + 2) % size) {
        return false; // Queue is full
    }
    else {
        // Add the value to the back of the queue
        back = (back + 1) % size;
        array[back] = value;
        return true; // Value enqueued successfully
    }
}

int IntegerArrayQueue::dequeue() {
    // Check if the queue is empty
    if (front == (back + 1) % size) {
        return 0; // Queue is empty
    }
    else {
        // Retrieve the value at the front of the queue
        int value = array[front];
        // Increment the front index in a circular manner
        front = (front + 1) % size;
        return value; // Return dequeued value
    }
}