#pragma once
#include "includes.h"

class Wheel {
public:
    Wheel();
    Wheel(std::string name, std::string category, std::vector<std::string> values, std::vector<int> probabilities);

    std::string name;
    std::string category;
    std::vector<std::string> values;
    std::vector<int> probabilities;
};
void createWheel();
void removeWheel(std::string name);
void loadWheels();
void displayWheels();

extern std::vector<Wheel> wheels;
