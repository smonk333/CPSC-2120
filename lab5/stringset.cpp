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
    if (!find(word)) {
        hash<string> stringHash;
        if (size != num_elems) {
            table[stringHash(word) % size].push_back(word);
            ++num_elems;
        }

        else {
            vector<list<string>> tmp;
            int sizeTmp = size * 2;
            tmp.resize(sizeTmp);

            for (int i = 0; i < size; i++) {
                if (!table[i].empty()) {
                    for(string const &j : table[i]) {
                        tmp[stringHash(j) % sizeTmp].push_back(j);
                    }
                }
            }
            table = tmp;
            size = sizeTmp;
            insert(word);
        }
    }
}

bool Stringset::find(string word) const {
    hash<string> hashString;
        if (table[hashString(word) % size].empty()) {
            for (string const& j : table[hashString(word) % size]) {
                if (j == word) {
                    return true;
                }
            }
        }
    return false;
}

void Stringset::remove(string word) {
    hash<string> stringHash;
    if (find(word)) {
        table[stringHash(word) % size].remove(word);
        --num_elems;
    }
}