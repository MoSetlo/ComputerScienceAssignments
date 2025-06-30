#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "PGMimageProcessor.h"


using namespace std;

 int main(int argc , char* argv[])
{
        //Part 1==========================================================================================

    stlmou001::PGMimageProcessor pgmProcessor(argv[argc-1]); //Create instance of PGMimageProcessor, parsing the file name

    
    int readSuccess = pgmProcessor.readPGM(argc, argv); //Reads the image contents and extracts the console arguments 

    if(readSuccess>0) //program terminates on unsucessful read
    {

        if(pgmProcessor.outputStatus()!="")
        {
            pgmProcessor.writeComponents(pgmProcessor.outputStatus()); //write components to output image
        }

        if(pgmProcessor.printStatus())
        {
            pgmProcessor.printFullData();  //print components data to console
        }



    }
    else
    {
        return 0;
    }

    

    return 0;
}
