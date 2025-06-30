#include <iostream>
#include "WCpp.h"
#include  <sstream>


namespace stlmou001{

struct CharInfo{char character;  long count=0;};    //data type to count the frequency of characters 

int lineCount(std::vector<std::string>& wordsH)  //returns the number of lines
{
    return wordsH.size();
}


std::string wordCharCount(std::vector<std::string>& wordsH) //returns the number of words , characters, and character frequency
{

    int charCounts =0;
    int wordCounts=0;
    std::ostringstream sout;
    
    //struct CharInfo{char character;  long count=0;};
    std::vector<CharInfo> vecLetter; //conatiner to hold letter and letter frequency
    std::vector<CharInfo> vecNumber; //conatiner to hold number and number frequency

    





for(int i=0 ; i<wordsH.size() ; i++)
    {
        std::istringstream iss(wordsH[i]);
        std::string wordSearch;
        
        
        while(!iss.eof())  // string delimited by spaces until end of file
        {
            int flag = 0;  //used to determine if word contained a letter or num
            

            iss >> wordSearch;  

            for (int j = 0; j < wordSearch.length() ; j++)
            {
                if(wordSearch[j] >='0' && wordSearch[j] <='9'  ) //determies if character is digit
                {


                    charCounts++;
                    flag++;

                    if(vecNumber.size() == 0)
                    {
                        

                        vecNumber.push_back( {wordSearch[j],1});
                    }
                    else
                    {
                        bool found = false;
                       for (int k = 0; k< vecNumber.size(); k++)
                       {
                            if(vecNumber[k].character == wordSearch[j])
                            {
                                vecNumber[k].count++;
                                found = true;
                            }

                       
                        }
                        if(!found)
                        {
                            vecNumber.push_back( {wordSearch[j],1});
                        }
                        

                    }

                }

                else if(wordSearch[j] >='a' && wordSearch[j] <='z') //determies if character is alphabetic
                {


                    charCounts++;
                    flag++;

                    if(vecLetter.size() == 0)
                    {
                        

                        vecLetter.push_back( {wordSearch[j],1});
                    }
                    else
                    {
                        bool found = false;
                       for (int k = 0; k< vecLetter.size(); k++)
                       {
                            if(vecLetter[k].character == wordSearch[j])
                            {
                                vecLetter[k].count++;
                                found = true;
                            }

                       
                        }
                        if(!found)
                        {
                            vecLetter.push_back( {wordSearch[j],1});
                        }
                        

                    }



                    


                }
                else if (wordSearch[j] >='A' && wordSearch[j] <='Z' ) //determies if character is alphabetic
                {

                    int charOutNum;
                    char charOut;
                    charCounts++;
                    flag++;

                    if(vecLetter.size() == 0)
                    {
                        
                        charOutNum= int(wordSearch[j]) +32; //converts uppercase letters to lowercase for easy frequency count
                        charOut = char(charOutNum);
                        vecLetter.push_back( {charOut,1});
                    }
                    else
                    {

                        bool found = false;
                       for (int k = 0; k< vecLetter.size(); k++)
                       {
                        charOutNum= int(wordSearch[j]) +32;
                        charOut = char(charOutNum);
                            if(vecLetter[k].character == charOut)
                            {
                                vecLetter[k].count++;
                                found = true;
                            }

                       
                        }

                        if(!found)
                        {
                        charOutNum= int(wordSearch[j]) +32;
                        charOut = char(charOutNum);
                        vecLetter.push_back( {charOut,1});
                        }
                        

                    }


                }

            
            }

            if(flag>0)
            {
                wordCounts++;
            }




            
           
        }
        

    }
    
    if(!vecLetter.empty() || !vecNumber.empty())
    {
        quickSort(vecLetter , 0 , vecLetter.size()-1);
        quickSort(vecNumber , 0 , vecNumber.size()-1);

    }

    
    

    sout << wordCounts << " " << charCounts << " [";  

    for(int l=0 ; l<vecNumber.size() ; l++)
    {
        sout << vecNumber[l].character << ":" << vecNumber[l].count << " ";
    }

    for(int l=0 ; l<vecLetter.size() ; l++)
    {
        sout << vecLetter[l].character << ":" << vecLetter[l].count << " ";
    }

    sout <<"]" <<std::endl;

    return sout.str();   
}


void quickSort(std::vector<CharInfo>& wordsDL , int start , int end) //sorts a vector by reference in order of ASCII
{
    // std::cout<<wordsDL.size()<< wordsDL[end-1].character << std::endl;

    if(end<=start) return;

    int pivot = partition(wordsDL , start , end);
    quickSort(wordsDL , start , pivot-1);
    quickSort(wordsDL , pivot+1 , end);
    
} 

int partition(std::vector<CharInfo>& wordsDL, int start , int end) //used for quicksort to keep track of pivot location
{
    int pivot = int(wordsDL[end].character);
    int i = start-1;
    
    for(int j=start; j<=end-1 ; j++)
    {
        if(int(wordsDL[j].character) < pivot )
        {
        i++;
        CharInfo temp = wordsDL[i];
        wordsDL[i]= wordsDL[j];
        wordsDL[j] = temp;
        }

    }
    i++;
    CharInfo temp = wordsDL[i];
    wordsDL[i] = wordsDL[end];
    wordsDL[end] = temp;

    return i;
} 

} 


