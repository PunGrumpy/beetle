#include <iostream>
#include <fstream>
#include <string>

void createOutputFile(const std::string& inputFile, const std::string& outputFile) {
    std::ofstream ofs(outputFile);

    if (!ofs) {
        throw std::runtime_error("Failed to create output file: " + outputFile);
    }

    std::ifstream ifs(inputFile);
    if (!ifs) {
        throw std::runtime_error("Failed to open input file: " + inputFile);
    }

    std::string line;
    int delay = 500;
    int wait = 0; // You can assign a default value or set it as a user input

    while (std::getline(ifs, line)) {
        std::string waitStr;
        if (wait > 0) {
            waitStr = "DELAY " + std::to_string(wait);
        } else {
            waitStr = "WAIT_FOR_BUTTON_PRESS";
        }
        
        std::string command = "STRING " + line + "\n"
                              "DELAY " + std::to_string(delay) + "\n"
                              "ENTER\n" + waitStr + "\n";

        ofs << command;
    }

    std::cout << "Conversion complete." << std::endl;
}

int main() {
    std::string inputFile = "input.txt"; // Replace with the actual input file path
    std::string outputFile = "Dict_Attack.txt"; // Replace with the desired output file path

    try {
        createOutputFile(inputFile, outputFile);
        std::cout << "Output file created successfully: " << outputFile << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
