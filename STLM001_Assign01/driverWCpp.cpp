#include <iostream>
#include "WCpp.h"
#include <vector>
#include <string>

using namespace std;

int main() 
{
    vector<string> words; //container for console strings
    string word;
    vector<string> wordse;

    while(getline(cin , word)) //loops until end of file 
    {
    words.push_back(word);
    if(cin.eof()) break;
    }
    if(cin.eof() && cin.fail()) // allows for trailing empty lines to be counted as a line
    {
        words.push_back("");
    }



    cout<< stlmou001::lineCount(words) << " " << stlmou001::wordCharCount(words) <<endl;
    //cout<< wordse.size() <<endl;

}


