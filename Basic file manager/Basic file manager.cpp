// Basic file manager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void listFiles(const fs::path& path) {
    if (fs::exists(path) && fs::is_directory(path)) {
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << entry.path().filename().string() << (fs::is_directory(entry) ? " [DIR]" : "") << std::endl;
        }
    }
    else {
        std::cout << "Invalid directory path!" << std::endl;
    }
}

void viewFile(const fs::path& path) {
    if (fs::exists(path) && fs::is_regular_file(path)) {
        std::ifstream file(path);
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cout << "File does not exist or is not accessible." << std::endl;
    }
}

void createDirectory(const fs::path& path) {
    if (fs::create_directory(path)) {
        std::cout << "Directory created successfully." << std::endl;
    }
    else {
        std::cout << "Failed to create directory." << std::endl;
    }
}

void copyFile(const fs::path& source, const fs::path& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "File copied successfully." << std::endl;
    }
    catch (fs::filesystem_error& e) {
        std::cerr << "Copy failed: " << e.what() << std::endl;
    }
}

void moveFile(const fs::path& source, const fs::path& destination) {
    try {
        fs::rename(source, destination);
        std::cout << "File moved successfully." << std::endl;
    }
    catch (fs::filesystem_error& e) {
        std::cerr << "Move failed: " << e.what() << std::endl;
    }
}

int main() {
    std::string command;
    std::string path1, path2;

    std::cout << "Simple File Manager\nCommands:\n";
    std::cout << "LIST <directory> - List files\n";
    std::cout << "VIEW <file> - View file content\n";
    std::cout << "MKDIR <directory> - Create directory\n";
    std::cout << "COPY <source> <destination> - Copy file\n";
    std::cout << "MOVE <source> <destination> - Move file\n";
    std::cout << "EXIT - Exit program\n";

    while (true) {
        std::cout << "\nEnter command: ";
        std::cin >> command;

        if (command == "LIST") {
            std::cin >> path1;
            listFiles(path1);
        }
        else if (command == "VIEW") {
            std::cin >> path1;
            viewFile(path1);
        }
        else if (command == "MKDIR") {
            std::cin >> path1;
            createDirectory(path1);
        }
        else if (command == "COPY") {
            std::cin >> path1 >> path2;
            copyFile(path1, path2);
        }
        else if (command == "MOVE") {
            std::cin >> path1 >> path2;
            moveFile(path1, path2);
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
