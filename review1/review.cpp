//
// Created by gboling on 1/24/2023.
//
#include "review.h"
#include <iostream>

void ReadStdIn() {
    int i;
    double d;
    std::string s;
    std::cin >> i >> d >> s;
    std::cout << i << std::endl << d << std::endl << s << std::endl;
}

int WriteOut(std::string output) {
    std::cout << output << std::endl;
    return 1;
}

int WriteOut(int output) {
    std::cout << output << std::endl;
    return 2;
}

int WriteOut(double output) {
    std::cout << output << std::endl;
    return 3;
}

void ReadStdIn2() {
    int count = 0;
    std::string in;
    while (std::cin >> in && in != "q"){
        count++;
    }
    std::cout << count << std::endl;
}

void ReadWrite() {
    std::string in;
    while (std::cin >> in && in != "q") {
        std::cout << in << " ";
    }
    std::cout << std::endl;
}

std::vector<int> InitializeArray(int size) {
    std::vector<int> newVector;
    for(int i = 0; i < size; i++){
        newVector.push_back(0);
    }
    return newVector;
}

void LoopThrough(double *data, int size) {
    for (int i = 0; i < size; i++){
        data[i]++;
    }
}

int Fibonacci(int a) {
    if (a == 0) {
        return 0;
    }
    else if (a == 1) {
        return 1;
    }
    else {
        return Fibonacci(a - 1) + Fibonacci(a - 2);
    }
}


