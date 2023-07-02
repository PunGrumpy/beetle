#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <sstream>

std::vector<std::string> generateVeryEasyNumbers() {
    std::vector<std::string> veryEasyNumbers;
    for (int i = 0; i <= 9; i++) {
        std::string number = std::to_string(i);
        veryEasyNumbers.push_back(number + number + number + number);
    }
    veryEasyNumbers.push_back("1234");
    return veryEasyNumbers;
}

std::vector<std::string> generateAdjacentEasyNumbers() {
    std::vector<std::string> adjacentEasyNumbers;
    for (int i = 0; i <= 9; i++) {
        std::string number = std::to_string(i);
        std::string adjacentNumber = std::to_string((i + 1) % 10);
        adjacentEasyNumbers.push_back(number + number + adjacentNumber + adjacentNumber);
    }
    return adjacentEasyNumbers;
}

std::vector<std::string> generateEasyNumbers() {
    std::vector<std::string> easyNumbers;
    for (int i = 0; i <= 9; i++) {
        std::string firstDuo = std::to_string(i) + std::to_string(i);
        for (int j = 0; j <= 9; j++) {
            std::string secondDuo = std::to_string(j) + std::to_string(j);
            std::string number = firstDuo + secondDuo;
            if (std::find(easyNumbers.begin(), easyNumbers.end(), number) == easyNumbers.end()) {
                easyNumbers.push_back(number);
            }
        }
    }
    return easyNumbers;
}

std::vector<int> generateYearNumbers(int startYear, int endYear) {
    std::vector<int> yearNumbers;
    for (int year = startYear; year <= endYear; year++) {
        yearNumbers.push_back(year);
    }
    return yearNumbers;
}

std::vector<std::string> generateDoubleUnder100() {
    std::vector<std::string> doubleUnder100;
    for (int i = 0; i <= 99; i++) {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << i;
        std::string number = ss.str();
        doubleUnder100.push_back(number + number);
    }
    return doubleUnder100;
}

std::vector<std::string> generateCombinations() {
    std::vector<std::string> combinations;
    for (int i = 0; i <= 9999; i++) {
        std::stringstream ss;
        ss << std::setw(4) << std::setfill('0') << i;
        std::string number = ss.str();
        combinations.push_back(number);
    }
    return combinations;
}

std::vector<std::string> randomizeNonEasyNumbers(const std::vector<std::string>& nonEasyNumbers) {
    std::vector<std::string> randomizedNonEasyNumbers = nonEasyNumbers;
    unsigned seed = std::time(0);
    std::shuffle(randomizedNonEasyNumbers.begin(), randomizedNonEasyNumbers.end(), std::default_random_engine(seed));
    return randomizedNonEasyNumbers;
}

std::vector<std::string> combineNumbers(const std::vector<std::vector<std::string>>& numberLists) {
    std::vector<std::string> combinedNumbers;
    for (const auto& numberList : numberLists) {
        for (const auto& number : numberList) {
            if (std::find(combinedNumbers.begin(), combinedNumbers.end(), number) == combinedNumbers.end()) {
                combinedNumbers.push_back(number);
            }
        }
    }
    return combinedNumbers;
}

void writeToFile(const std::string& filePath, const std::vector<std::string>& numbers) {
    std::ofstream file(filePath);
    if (file.is_open()) {
        for (const auto& number : numbers) {
            file << number << std::endl;
        }
        file.close();
    }
}

int main() {
    std::vector<std::string> veryEasyNumbers = generateVeryEasyNumbers();
    std::vector<std::string> adjacentEasyNumbers = generateAdjacentEasyNumbers();
    std::vector<std::string> easyNumbers = generateEasyNumbers();
    std::vector<int> yearNumbers = generateYearNumbers(1901, std::tm().tm_year + 1900);
    std::vector<std::string> doubleUnder100 = generateDoubleUnder100();
    std::vector<std::string> combinations = generateCombinations();
    std::vector<std::string> nonEasyNumbers = combineNumbers({ veryEasyNumbers, adjacentEasyNumbers, easyNumbers });
    std::vector<std::string> randomizedNonEasyNumbers = randomizeNonEasyNumbers(nonEasyNumbers);
    std::vector<std::string> allNumbers = combineNumbers({ veryEasyNumbers, adjacentEasyNumbers, yearNumbers, easyNumbers, doubleUnder100 });
    std::vector<std::string> randomizedNumbers = combineNumbers({ allNumbers, randomizedNonEasyNumbers });

    std::string scriptDir = "path/to/your/script/directory";
    std::string filePath = scriptDir + "/pin_codes.txt";

    writeToFile(filePath, randomizedNumbers);

    return 0;
}
