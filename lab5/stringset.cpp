/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include "stringset.h"

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

void Stringset::insert(string word) {
    if (!this->find(word)) {
        hash<string> hashed;
        if (size != num_elems) {
            table[hashed(word) % size].push_back(word);
            ++num_elems;
        }

        else {
            vector<list<string>> big;
            int sizeTmp = size * 2;
            big.resize(sizeTmp);

            for (int i = 0; i < size; i++) {
                if (!table[i].empty()) {
                    for(string const &j : table[i]) {
                        big[hashed(j) % sizeTmp].push_back(j);
                    }
                }
            }
            table = big;
            size = sizeTmp;
            insert(word);
        }
    }
}

bool Stringset::find(string word) const {
    hash<string> hashed;
        if (!table[hashed(word) % size].empty()) {
            for (string const& j : table[hashed(word) % size]) {
                if (j == word) {
                    return true;
                }
            }
        }
    return false;
}

void Stringset::remove(string word) {
    hash<string> hashed;
    if (find(word)) {
        table[hashed(word) % size].remove(word);
        --num_elems;
    }
}