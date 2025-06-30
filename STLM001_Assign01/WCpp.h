#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#ifndef WCPP_H
#define WCPP_H

namespace stlmou001{

struct CharInfo;    

int lineCount(std::vector<std::string>& wordsH);

std::string wordCharCount(std::vector<std::string>& wordsH);

void quickSort(std::vector<CharInfo>& wordsDL, int start , int end);

int partition(std::vector<CharInfo>& wordsDL, int start , int end);


}


#endif