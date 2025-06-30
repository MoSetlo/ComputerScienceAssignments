#ifndef PGMIMAGEPROCESSOR_H
#define PGMIMAGEPROCESSOR_H

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include "ConnectedComponent.h"
#include <fstream>
#include <queue>
#include <cstring>

namespace stlmou001{
class PGMimageProcessor {
private:
    std::vector<std::shared_ptr<ConnectedComponent>> components;

    //declaration of class private variables
        int fileRows,fileCols;
        std::vector<std::string> fileHeader;
        std::string fileName;
        unsigned char **fileChars;
        bool ** visited;
        bool printData;
        std::string outputImage;
        int threadshold;
        int min,max;



public:
    
    // Constructor
    PGMimageProcessor(const std::string& inputFile);

    // Destructor
    ~PGMimageProcessor();

    // Copy constructor
    PGMimageProcessor(const PGMimageProcessor& other);

    // Move constructor
    PGMimageProcessor(PGMimageProcessor&& other) ;

    // Copy assignment operator
    PGMimageProcessor& operator=(const PGMimageProcessor& other);

    // Move assignment operator
    PGMimageProcessor& operator=(PGMimageProcessor&& other) ;

    // Method to extract connected components given threshold limit and minimum compoonent size
    int extractComponents(const int& threshold, const int& minValidSize);

    // Method to filter components by size given minimum and maximum size
    int filterComponentsBySize(const int & minSize, const int & maxSize);

    // Method to write components to a PGM file - 'outfileName'.pgm
    bool writeComponents(const std::string& outFileName);

    // Getter methods for component information
    int getComponentCount() const;
    int getLargestSize() const;
    int getSmallestSize() const;

    // Method to print component data
    void printComponentData(const ConnectedComponent& theComponent) const;

    //Method to  print all component data
    void printFullData(void);

    //Method to create 2D array from 1D image * array
    void convertTo2D(const char * paramfileChar);

    //Method to convert to threshold the 2D images to fully black before write given threshold limit
    void convertToBlack(const int & thresh);

    //Sorts the components vector from smallest to largest
    void sortComponentsLow(void);

    
    //Sorts the components vector from largest to smallest
    void sortComponentsHigh(void);


    //Method receive input arguments from driver.cpp and reads in the image
   int readPGM(const int & argcParam , char * argvParam[]);

    //Method to check if print argument -p was given
   bool printStatus(void);

    //Method to return output image string
   std::string outputStatus(void);

    //Method to write 2D array to file
    void writeToFile(const std::string& outFileName);
};
}
#endif // PGMIMAGEPROCESSOR_H
