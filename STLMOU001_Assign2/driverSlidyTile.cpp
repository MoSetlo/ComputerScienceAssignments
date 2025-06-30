#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "TileManager.h"


using namespace std;

 int main(int argc , char* argv[])
{

    string filename;
    vector <string> fileStrLines;
    string strLine;
    int gridSize, numMoves;

    //Test for minimum number of command line arguments
    if(argc <7)
    {
        cout<<"Not enough arguments were given"<<endl;
        return 0;
    }
    else
    {
        gridSize = stoi(argv[2]);
        numMoves = stoi(argv[6]);
        filename = argv[4];
    }

    //Input file existence check
    ifstream in(filename, ios::binary);
    if(!in)
    {
        std::cerr << "Couldn't open file " << filename << std::endl;
        return 1; 
    }

    //File reading until we hit the character '255', we switch to char byte read there after
    bool flag = false;
    while(!in.eof() && !flag)
    {
        getline(in,strLine);

     fileStrLines.push_back(strLine);

     if(strLine == "255")  
     {
        flag = true;
        //cout<<"We detected that sonova bish"<<endl;
     }

    }
    

    istringstream iss(fileStrLines.at(fileStrLines.size()-2));
    int rows,columns;

    iss>>columns>>rows;

    char array[rows*columns];

    //char byte read into array;
    while(!in.eof())
    {
        in.read(array,rows*columns);
    }

    in.close();

    //Part 2==========================================================================================

    stlmou001::TileManager tileManager;

    tileManager.UpdateDetails(rows,columns,gridSize, fileStrLines, array ,filename , numMoves);

    return 0;
}
