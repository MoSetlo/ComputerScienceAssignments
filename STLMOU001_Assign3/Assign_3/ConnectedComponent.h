#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H

#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <sstream>

class ConnectedComponent {
private:
    int numPixels; //no. of pixels within the component
    int id;  //ID of distinct components
    std::vector<std::pair<int, int>> pixels; // Coordinates of pixels in the component

public:
    // Constructor
    ConnectedComponent(int id);

    // Destructor
    ~ConnectedComponent();

    // Copy constructor
    ConnectedComponent(const ConnectedComponent& other);

    // Move constructor
    ConnectedComponent(ConnectedComponent&& other) ;

    // Copy assignment operator
    ConnectedComponent& operator=(const ConnectedComponent& other);

    // Move assignment operator
    ConnectedComponent& operator=(ConnectedComponent&& other) ;

    // Method to add a pixel to the component
    void addPixel(int x, int y);

    //Setter method to change the ID of a component
    void setID(const int & paramID);

    // Getter methods
    int getNumPixels() const;
    int getId() const;
    const std::vector<std::pair<int, int>>& getPixels() const;

    // Method of check whether a pixel is within another component given coordinates
    bool containsPixel(int x, int y) const ;

    // Merges component (NumPixels and Pixels) with another component.
    void mergeWith(const ConnectedComponent& other) ;
};

#endif // CONNECTEDCOMPONENT_H