#include "ConnectedComponent.h"

// Constructor
ConnectedComponent::ConnectedComponent(int id) : numPixels(0), id(id) {}

// Destructor - This class uses automatic variables
ConnectedComponent::~ConnectedComponent() {}

// Copy constructor
ConnectedComponent::ConnectedComponent(const ConnectedComponent& other) {
    numPixels = other.numPixels;
    id = other.id;
    pixels = other.pixels;
}

// Move constructor
ConnectedComponent::ConnectedComponent(ConnectedComponent&& other)  {
    numPixels = other.numPixels;
    id = other.id;
    pixels = std::move(other.pixels);
}

// Copy assignment operator
ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent& other) {
    if (this != &other) {
        numPixels = other.numPixels;
        id = other.id;
        pixels = other.pixels;
    }
    return *this;
}

// Move assignment operator
ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent&& other)  {
    if (this != &other) {
        numPixels = other.numPixels;
        id = other.id;
        pixels = std::move(other.pixels);
    }
    return *this;
}

// Method to add a pixel to the component
void ConnectedComponent::addPixel(int x, int y) {
    pixels.emplace_back(x, y);
    numPixels++;
}

// Change the ID of a component
void ConnectedComponent::setID(const int & paramID)
{

        id = paramID;
    
}

// Getter methods
int ConnectedComponent::getNumPixels() const {
    return numPixels;
}

int ConnectedComponent::getId() const {
    return id;
}

const std::vector<std::pair<int, int>>& ConnectedComponent::getPixels() const {
    return pixels;
}

// header description
bool ConnectedComponent::containsPixel(int x, int y) const {
        return std::find(pixels.begin(), pixels.end(), std::make_pair(x, y)) != pixels.end();
    }
//header description
void ConnectedComponent::mergeWith(const ConnectedComponent& other) {
        for (const std::pair<int, int>& pixel : other.getPixels()) {
            pixels.push_back(pixel);
        }
        numPixels += other.getNumPixels();
    }   