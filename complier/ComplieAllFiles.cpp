#include <iostream>
#include <filesystem>

#define OUTPUT_DIR "output"
#define SCRIPT_DIR "scripts"

int main() {
    std::filesystem::path scriptDir = std::filesystem::current_path() / SCRIPT_DIR;
    std::filesystem::path outputDir = std::filesystem::current_path() / OUTPUT_DIR;

    if (!std::filesystem::exists(outputDir)) {
        std::filesystem::create_directory(outputDir);
    }

    for (const auto& entry : std::filesystem::directory_iterator(scriptDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
            std::string command = "g++ " + entry.path().string() + " -o " + outputDir.string() + "/" + entry.path().stem().string() + ".exe";
            int result = std::system(command.c_str());
            if (result == 0) {
                std::cout << "Compilation successful: " << outputDir.string() << "/" << entry.path().stem().string() << ".exe" << std::endl;
            } else {
                std::cout << "Compilation failed: " << entry.path().stem().string() << ".cpp" << std::endl;
            }
        }
    }

    return 0;
}
