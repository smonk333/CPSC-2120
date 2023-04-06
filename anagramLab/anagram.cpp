/*
 * Name:
 * Date Submitted:
 * Assignment Name:
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);

/*int main()
{
    vector<string> words;
    vector<string> anagrams;
    string inputWord;
    words=loadWordlist("wordlist.txt");
    cout << "Find single-word anagrams for the following word: ";
    cin >> inputWord;
    anagrams = anagram(inputWord, words);
    for (int i=0; i<anagrams.size(); i++) {
        cout << anagrams[i] << endl;
    }
    return 0;
}*/

vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

//Implement this function
vector<string> anagram(string word, vector<string> wordlist)
{
    vector<string> result;

    // Build a map where the key is a string representing the sorted letters in a word
    // and the value is a vector of words with the same sorted letters
    unordered_map<string, vector<string>> anagramMap;
    for (const string& w : wordlist)
    {
        // Count the occurrences of each letter in the word
        int charCounts[26] = {0};
        for (char c : w)
        {
            charCounts[c - 'a']++;
        }
        // Build a string representing the sorted letters in the word
        string sortedChars;
        for (int i = 0; i < 26; i++)
        {
            sortedChars += string(charCounts[i], 'a' + i);
        }
        // Add the word to the vector associated with the key representing its sorted letters
        anagramMap[sortedChars].push_back(w);
    }

    // Count the occurrences of each letter in the input word
    int charCounts[26] = {0};
    for (char c : word)
    {
        charCounts[c - 'a']++;
    }
    // Build a string representing the sorted letters in the input word
    string sortedChars;
    for (int i = 0; i < 26; i++)
    {
        sortedChars += string(charCounts[i], 'a' + i);
    }

    // Get the vector of words associated with the key representing the sorted letters in the input word
    vector<string>& anagrams = anagramMap[sortedChars];
    for (const string& w : anagrams)
    {
        result.push_back(w);
    }

    return result;
}
