/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 
 void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);
 
 /*int main()
 {
     Stringset wordlist;
     testStringset(wordlist);
     return 0;
 }*/
 
 void testStringset(Stringset& words)
 {
     string choice;
     string word;
     do
     {
         cout << "I: insert word" << endl;
         cout << "F: find word" << endl;
         cout << "R: remove word" << endl;
         cout << "P: print words in stringset" << endl;
         cout << "Q: quit" << endl;
         cin >> choice;
         switch (choice[0])
         {
             case 'I':
             case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
             case 'F':
             case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
             case 'R':
             case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
             case 'P':
             case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
         }
     } while (choice[0] != 'Q' && choice[0] != 'q');
 }
 
 void loadStringset(Stringset& words, string filename) {
     ifstream fileIn(filename); //making a filestream object to pull in words form the file specified
     string word;

     if (!fileIn.is_open()) {
         cout << "file not found. Exiting." << endl;
     }

     while (getline(fileIn, word)) {
        words.insert(word);
     }
     fileIn.close();
 }
 
 vector<string> spellcheck(const Stringset& words, string word) {
     vector<string> alts;
     hash<string> stringHash;

     for (int i = 0; i < word.length(); i++) {
         for (int j = 97; j < 122; j++) {
             string search = word;
             string replace(1, char(j));

             search = search.replace(i, 1, replace);

             if (search != word && words.find(search)) {
                 alts.push_back(search);
             }
         }
     }
     return alts;
 }