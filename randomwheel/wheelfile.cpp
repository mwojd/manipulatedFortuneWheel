#include "includes.h"

Wheel::Wheel() {}

Wheel::Wheel(std::string name, std::string category, std::vector<std::string> values, std::vector<int> probabilities) : name(name), category(category), values(values), probabilities(probabilities) {}

std::vector<Wheel> wheels;
void createWheel() {
    std::string name, category;
    std::vector<std::string> values;
    std::vector<int> probabilities;
    std::cout << "Enter the name of the wheel: ";
    std::cin >> name;
    std::cout << "Enter the category of the wheel: ";
    std::cin.ignore();
    std::getline(std::cin, category);
    std::cout << "Enter the values of the wheel (type 'done' when finished):\n";
    std::string value, probStr;
    int probability;
    int probSum{ 0 };
    while (true) {
        std::getline(std::cin, value);
        if (value == "done") 
            break;  
        std::cout << "Enter the probability for this value: ";
        std::getline(std::cin, probStr);
        probability = std::stoi(probStr);
        values.push_back(value);
        probabilities.push_back(probability);
        probSum += std::stoi(probStr);
        if (probSum > 100) {
            std::cout << "the summed probabilities equal to more than a 100, deleting this wheel..." << std::endl;
            removeWheel(name);
            break;
        }
    }
    std::ofstream file("wheels.txt", std::ios_base::app);
    file << name << "," << category << ",";
    for (int i = 0; i < values.size(); i++) {
        file << values[i] << ":" << probabilities[i];
        if (i < values.size() - 1) {
            file << ";";
        }
    }
    file << "\n";
    file.close();
}
void removeWheel(std::string name) {
    std::ifstream file("wheels.txt");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    std::ofstream outfile("wheels.txt");
    for (std::string line : lines) {
        std::string wheelName = line.substr(0, line.find(","));
        if (wheelName != name) {
            outfile << line << "\n";
        }
    }
    outfile.close();
}
void loadWheels() {
    wheels.clear();
    std::ifstream file("wheels.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::string name = line.substr(0, line.find(","));
        size_t categoryStart = line.find(",") + 1;
        size_t categoryEnd = line.find(",", categoryStart);
        std::string category = line.substr(categoryStart, categoryEnd - categoryStart);
        std::string valuesString = line.substr(categoryEnd + 1);
        std::vector<std::string> values;
        std::vector<int> probabilities;
        size_t pos = 0;
        while ((pos = valuesString.find(";")) != std::string::npos) {
            std::string valueProbString = valuesString.substr(0, pos);
            valuesString.erase(0, pos + 1);
            values.push_back(valueProbString.substr(0, valueProbString.find(":")));
            probabilities.push_back(std::stoi(valueProbString.substr(valueProbString.find(":") + 1)));
        }
        values.push_back(valuesString.substr(0, valuesString.find(":")));
        probabilities.push_back(std::stoi(valuesString.substr(valuesString.find(":") + 1)));

        Wheel wheel(name, category, values, probabilities);
        wheels.push_back(wheel);
    }
    file.close();
}
void displayWheels() {
    std::string tmpStr{ ' ' };
    for (const auto& wheel : wheels) {
        std::cout << wheel.name << std::endl;
        std::cout << "---category|" << wheel.category << std::endl;
    }
    std::cout << "do you want to filter by category? y/n" << std::endl;
    std::cin >> tmpStr;
    if (tmpStr == "y") {
        std::cout << "what category?" << std::endl;
        std::cin >> tmpStr;
        std::cout << "\n\n";
        for (const auto& wheel : wheels) {
            if (wheel.category == tmpStr) {
                std::cout << wheel.name << std::endl;
                std::cout << "---category|" << wheel.category << std::endl;
            }
        }
    }
}
